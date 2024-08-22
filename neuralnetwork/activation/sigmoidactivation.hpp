#ifndef ACTIVATIONSIGMOID_H
#define ACTIVATIONSIGMOID_H
#include <cmath>
#include <iostream>

template <typename NumType = float>
class ActivationSigmoid : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs;
    public:
        NumType** forwardTest(NumType** inputs, int samples, int prev_layer) override{
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_inputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new NumType[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    inputs[i][j] = 1/(1+exp(-inputs[i][j]));
                }
            }
            return inputs;
        }
        void backward() override{

        }
};

#endif