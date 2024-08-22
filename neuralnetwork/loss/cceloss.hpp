#ifndef LOSSCCE_H
#define LOSSCCE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LossCCE : public BaseLoss<NumType>
{
    private:
        NumType* vector;
        int vector_size = 0;
        int saved_samples;

    public:
        ~LossCCE() {
            if (vector != nullptr) {
                delete[] vector;
                vector = nullptr;  // Prevents double free
            }
        }

        
        NumType forwardTest(NumType** outputMatrix, int samples, int output_neurons, int* actualMatrix) override{
            saved_samples = samples;

            NumType** copiedMatrix = copyMatrix<NumType>(outputMatrix, samples, output_neurons);
            copiedMatrix = matrixClip<NumType>(copiedMatrix, samples, output_neurons, 1, 0);

            NumType* totals = new NumType[samples];
            // In this version, each actualMatrix value is the index of the neuron that is associated with the class.
            for(int i = 0; i < samples; i++){
                totals[i] = copiedMatrix[i][actualMatrix[i]];
                //std::cout << totals[i] << " : "<< actualMatrix[i] << std::endl;
            }
            //matrixViewer(totals, samples);
            //std::cout<< "TOTAL SUM" << std::endl;
            //std::cout << vectorSum(totals, samples) << std::endl;
            delete[] vector;
            //std::cout << "vector being made" << std::endl;
            //matrixViewer(totals, samples);
            vector = vectorLogNeg(totals, samples);
            //matrixViewer(vector, samples);
            //matrixViewer(vector, samples);
            NumType mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            delete[] totals;

            return mean;
        }

        // Each Output Neuron Identifies Classes
        NumType forwardTest(NumType** outputMatrix, int samples, int output_neurons, int** actualMatrix) override {
            saved_samples = samples;
            NumType** copiedMatrix = copyMatrix<NumType>(outputMatrix, samples, output_neurons);

            // For this overload 
            for(int i = 0; i < samples; i++){
                for(int j = 0; j < output_neurons; j++){
                    copiedMatrix[i][j] *= actualMatrix[i][j];
                }
            }

            matrixClip<NumType>(copiedMatrix, samples, output_neurons, 1, 0);

            delete[] vector;
            vector = matrixLogNegVectorSum(copiedMatrix, samples, output_neurons);

            NumType mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            return mean;
        }

        NumType** backward(int output_neurons, int* y_true, NumType** softouts) override{
            if(this->dvalues != nullptr){
                clearMatrix(this->dvalues, saved_samples);
                this->dvalues = nullptr;
            }
            // Allocate memory for the gradient values
            this->dvalues = new NumType*[saved_samples];

            for (int i = 0; i < saved_samples; i++) {
                this->dvalues[i] = new NumType[output_neurons];

                for (int j = 0; j < output_neurons; j++) {
                    // Initialize the gradient with the softmax outputs
                   //std::cout << i << " " << j << std::endl;
                    NumType r = softouts[i][j];
                    this->dvalues[i][j] = softouts[i][j];

                    // Subtract 1 from the softmax output at the index of the true class
                    if (j == y_true[i]) {
                        this->dvalues[i][j] -= 1.0f;
                    }

                    // Normalize by dividing by the number of samples
                    this->dvalues[i][j] /= saved_samples;
                }
            }

            return this->dvalues;
        }


        NumType** backwardOld(int output_neurons, int* y_true){
            //matrixViewer(vector, saved_samples);
            NumType** dvalues = new NumType*[saved_samples];

            for(int i = 0; i < saved_samples; i++){
                dvalues[i] = new NumType[output_neurons];
                //std::cout << "vector[" << i << "] = " << vector[i] << std::endl;

                for(int j = 0; j < output_neurons; j++){
                    if(j == y_true[i]){
                        //std::cout << i << j << std::endl;
                        dvalues[i][j] = (-1.0f / (vector[i] + 1e-7f))/saved_samples; // Clip to prevent division by zero
                        //std::cout<< dvalues[i][j] << std::endl;
                    }
                    else{
                        dvalues[i][j] = 0.0f;
                    }
                }
            }
            
            /*NumType clip_value = 1.0f; // Example clip value
            bool done = true;
            for(int i = 0; i < saved_samples; i++){
                for(int j = 0; j < output_neurons; j++){
                    if(dvalues[i][j] > clip_value){
                        //std::cout << dvalues[i][j] << std::endl;
                        //dvalues[i][j] = clip_value;
                    } else if(dvalues[i][j] < -clip_value){
                        //std::cout << dvalues[i][j] << std::endl;

                        //dvalues[i][j] = -clip_value;
                    }
                }
            }*/
            //matrixViewer(dvalues, saved_samples, 2);
            return dvalues;
        }
};

#endif
