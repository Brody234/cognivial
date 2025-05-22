#ifndef ACTIVATIONSIGMOID_H
#define ACTIVATIONSIGMOID_H
#include <cmath>
#include <iostream>

template <typename NumType = float>
class ActivationSigmoid : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs;
        int saved_samples;
        int saved_prev_layer;
    public:
        NumType** forward(NumType** inputs, int samples, int prev_layer) override{
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_inputs = new NumType*[samples];
            this->outputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new NumType[prev_layer];
                this->outputs[i] = new NumType[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    this->outputs[i][j] = 1/(1+exp(-inputs[i][j]));
                }
            }
            return this->outputs;
        }
        NumType** backward(NumType** dvalues) override{
            this->dinputs = new NumType*[saved_samples];
            for(int i = 0; i < saved_samples; i++){
                this->dinputs[i] = new NumType[saved_prev_layer];
                for(int j = 0; j < saved_prev_layer; j++){
                    this->dinputs[i][j] = this->outputs[i][j]*(1-this->outputs[i][j])*dvalues[i][j];
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " Sigmoid " << std::endl;
        }
};

#endif