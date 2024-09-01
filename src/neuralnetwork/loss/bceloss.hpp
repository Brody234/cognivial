#ifndef LOSSBCE_H
#define LOSSBCE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LossBCE : public BaseLoss<NumType>
{
    private:
        NumType* vector;
        int vector_size = 0;
        int saved_samples;

    public:
        ~LossBCE() {
            if (vector != nullptr) {
                delete[] vector;
                vector = nullptr;  // Prevents double free
            }
        }

        
        NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int* actualMatrix) override{
            saved_samples = samples;

            NumType** copiedMatrix = copyMatrix<NumType>(outputMatrix, samples, output_neurons);
            copiedMatrix = matrixClip<NumType>(copiedMatrix, samples, output_neurons, 1, 0);

            NumType* totals = new NumType[samples];
            for(int i = 0; i < samples; i++){
                totals[i] = copiedMatrix[i][actualMatrix[i]];
            }
            delete[] vector;
            vector = vectorLogNeg(totals, samples);
            NumType mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            delete[] totals;

            return mean;
        }

        // Each Output Neuron Identifies Classes
        NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int** actualMatrix) override {
            saved_samples = samples;
            NumType** copiedMatrix = copyMatrix<NumType>(outputMatrix, samples, output_neurons);

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

        NumType** backwardClass(int output_neurons, int* y_true, NumType** softouts) override{
            if(this->dvalues != nullptr){
                clearMatrix(this->dvalues, saved_samples);
                this->dvalues = nullptr;
            }
            this->dvalues = new NumType*[saved_samples];

            for (int i = 0; i < saved_samples; i++) {
                this->dvalues[i] = new NumType[output_neurons];

                for (int j = 0; j < output_neurons; j++) {
                    NumType r = softouts[i][j];
                    this->dvalues[i][j] = softouts[i][j];

                    if (j == y_true[i]) {
                        this->dvalues[i][j] -= 1.0f;
                    }

                    this->dvalues[i][j] /= saved_samples;
                }
            }

            return this->dvalues;
        }

        // Just to keep this from being abstract/let managers easily switch from regression to classification without an object. Never called in manager and will break your code if you call directly.

        NumType forwardRegress(NumType** outputMatrix, int samples, int output_neurons, NumType** actualMatrix) override{
            return 0.0;
        }

        NumType** backwardRegress(NumType** y_pred, NumType** y_true) override{
            return new NumType*[0];
        }


};

#endif
