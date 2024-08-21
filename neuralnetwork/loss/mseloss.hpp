#ifndef LOSSMSE_H
#define LOSSMSE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

class LossMSE
{
    private:
        int saved_samples;
        int saved_output_neurons;

    public:
        ~LossMSE() {
            
        }

        
        float forwardTest(float** outputMatrix, int samples, int output_neurons, float** actualMatrix){
            saved_samples = samples;
            saved_output_neurons = output_neurons;
            float sum = 0.0f;

            for(int i = 0; i < samples; i++){
                for(int j = 0; j < output_neurons; j++){
                    sum += (actualMatrix[i][j] - outputMatrix[i][j])*(actualMatrix[i][j] - outputMatrix[i][j]);
                }
            }
            float mean = sum/samples;

            return mean;
        }

        float** backward(float** dvalues, float** y_true){
            float** dinputs = new float*[saved_samples];

            for(int i = 0; i < saved_samples; i++){
                dinputs[i] = new float[saved_output_neurons];

                for(int j = 0; j < saved_output_neurons; j++){
                    dinputs[i][j] = -2*(y_true[i][j]-dvalues[i][j])/(saved_samples*saved_output_neurons);
                }
            }
            
            return dvalues;
        }
};

#endif
