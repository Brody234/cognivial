#ifndef ACTIVATIONSOFTMAX_H
#define ACTIVATIONSOFTMAX_H
#include <cmath>
#include <iostream>

class ActivationSoftMax
{
    private:
        float** saved_inputs;
    public:
        float** forwardTest(float** inputs, int samples, int prev_layer){
            if(samples <= 0){
                return new float*[0];
            }
            saved_inputs = new float*[samples];
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new float[prev_layer];
                float sum = 0.0f;
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    inputs[i][j] = exp(inputs[i][j]);
                    sum += inputs[i][j];
                    //std::cout << j << inputs[i][j] << sum << std::endl;
                }
                //std::cout << sum << std::endl;
                for(int j = 0; j < prev_layer; j++){
                    inputs[i][j] = inputs[i][j]/sum;
                }
            }
            return inputs;
        }
        void backward(){

        }
};

#endif