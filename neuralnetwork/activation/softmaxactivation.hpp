#ifndef ACTIVATIONSOFTMAX_H
#define ACTIVATIONSOFTMAX_H
#include <cmath>
#include <iostream>
#include "../utilities/matrixutility.hpp"

class ActivationSoftMax
{
    private:
        float** outputs = nullptr;
    public:
        float** forwardTest(float** inputs, int samples, int prev_layer){
            //matrixViewer(inputs, samples, prev_layer);

            if(samples <= 0){
                return new float*[0];
            }
            if(outputs != nullptr){
                clearMatrix(outputs, samples);
                outputs = nullptr;
            }
            outputs = new float*[samples];
            for(int i = 0; i < samples; i++){
                outputs[i] = new float[prev_layer];
                float sum = 0.0f;
                float max = inputs[i][0];
                for(int j = 1; j < prev_layer; j++){
                    max = inputs[i][j];
                }
                for(int j = 0; j < prev_layer; j++){
                    outputs[i][j] = exp(inputs[i][j] - max);
                    sum += outputs[i][j];
                }
                for(int j = 0; j < prev_layer; j++){
                    outputs[i][j] = outputs[i][j]/(sum+1e-7);
                }
            }
            return outputs;
        }
        float** backward(float** dvalues, int samples, int prev_layer){
            float** dinputs = new float*[samples];
            for(int i = 0; i < samples; i++){
                dinputs[i] = dvalsXJacobian(outputs[i], prev_layer, dvalues[i]); 
                //std::cout << "DINPUT OF SOFTMAX" << std::endl;
                //std::cout << dinputs[i][0] << std::endl;
            }
            matrixViewer(dinputs, 3, prev_layer);
            return dinputs;
        }
};

#endif