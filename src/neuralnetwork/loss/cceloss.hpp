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
        Array<NumType, 1> vector;
        size_t vector_size = 0;
        size_t saved_samples;

    public:
        ~LossCCE() {
            /*if (vector != nullptr) {
                delete[] vector;
                vector = nullptr;  // Prevents double free
            }*/
        }

        
        NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 1>& actualMatrix) override{
            saved_samples = samples;

            Array<NumType, 2> copiedMatrix = outputMatrix.copy(); //copyMatrix<NumType>(outputMatrix, samples, output_neurons);
            copiedMatrix = matrixClip<NumType>(copiedMatrix, samples, output_neurons, 1, 0);

            Array<NumType, 1> totals(samples);
            for(size_t i = 0; i < samples; i++){
                totals[i] = copiedMatrix[i][actualMatrix[i]];
            }
            //delete[] vector;
            //std::cout << totals.toString() << std::endl;
            vector = vectorLogNeg(totals, samples);
            //std::cout << vector.toString() << std::endl;
            NumType mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            //delete[] totals;

            return mean;
        }

        // Each Output Neuron Identifies Classes
        NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 2>& actualMatrix) override {
            saved_samples = samples;
            Array<NumType, 2> copiedMatrix = copyMatrix<NumType>(outputMatrix, samples, output_neurons);

            for(size_t i = 0; i < samples; i++){
                for(size_t j = 0; j < output_neurons; j++){
                    copiedMatrix[i][j] *= actualMatrix[i][j];
                }
            }

            matrixClip<NumType>(copiedMatrix, samples, output_neurons, 1, 0);

            vector = matrixLogNegVectorSum(copiedMatrix, samples, output_neurons);

            NumType mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            return mean;
        }

        Array<NumType, 2> backwardClass(size_t output_neurons, Array<int, 1>& y_true, Array<NumType, 2>& softouts) override{
            /*if(this->dvalues != nullptr){
                clearMatrix(this->dvalues, saved_samples);
                this->dvalues = nullptr;
            }*/
            size_t shape[2] = {saved_samples, output_neurons};
            this->dvalues = Array<NumType, 2>(shape);

            for (size_t i = 0; i < saved_samples; i++) {

                for (size_t j = 0; j < output_neurons; j++) {
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

        NumType forwardRegress(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<NumType, 2>& actualMatrix) override{
            return 0.0;
        }

        Array<NumType, 2> backwardRegress(Array<NumType, 2>& y_pred, Array<NumType, 2>& y_true) override{
            return Array<NumType, 2>();
        }


};

#endif
