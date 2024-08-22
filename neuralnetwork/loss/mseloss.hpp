#ifndef LOSSMSE_H
#define LOSSMSE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LossMSE
{
    private:
        int saved_samples;
        int saved_output_neurons;

    public:
        ~LossMSE() {
            
        }

        
        NumType forwardTest(NumType** outputMatrix, int samples, int output_neurons, NumType** actualMatrix){
            saved_samples = samples;
            saved_output_neurons = output_neurons;
            NumType sum = 0.0f;

            for(int i = 0; i < samples; i++){
                for(int j = 0; j < output_neurons; j++){
                    sum += (actualMatrix[i][j] - outputMatrix[i][j])*(actualMatrix[i][j] - outputMatrix[i][j]);
                }
            }
            NumType mean = sum/samples;

            return mean;
        }

        NumType** backward(NumType** dvalues, NumType** y_true){
            NumType** dinputs = new NumType*[saved_samples];

            for(int i = 0; i < saved_samples; i++){
                dinputs[i] = new NumType[saved_output_neurons];

                for(int j = 0; j < saved_output_neurons; j++){
                    dinputs[i][j] = -2*(y_true[i][j]-dvalues[i][j])/(saved_samples*saved_output_neurons);
                }
            }
            
            return dvalues;
        }
};

#endif
