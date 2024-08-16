#ifndef ACTIVATIONSIGMOID_H
#define ACTIVATIONSIGMOID_H
#include <cmath>
#include <iostream>

class ActivationSigmoid
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
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    inputs[i][j] = 1/(1+exp(-inputs[i][j]));
                }
            }
            return inputs;
        }
        void backward(){

        }
};

#endif