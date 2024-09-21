#ifndef ACTIVATIONSOFTMAX_H
#define ACTIVATIONSOFTMAX_H
#include <cmath>
#include <iostream>
#include "../utilities/matrixutility.hpp"

template <typename NumType = float>
class ActivationSoftMax : public BaseActivation<NumType>
{
    private:
        int saved_samples;
        int saved_prev_layer;
    public:
        NumType** forwardTest(NumType** inputs, int samples, int prev_layer) override{
            //matrixViewer(inputs, samples, prev_layer);
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            if(samples <= 0){
                return new NumType*[0];
            }
            if(this->outputs != nullptr){
                clearMatrix(this->outputs, samples);
                this->outputs = nullptr;
            }
            this->outputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                this->outputs[i] = new NumType[prev_layer];
                NumType sum = 0.0f;
                NumType max = inputs[i][0];
                for(int j = 1; j < prev_layer; j++){
                    if(max < inputs[i][j]){
                        max = inputs[i][j];
                    }
                }
                for(int j = 0; j < prev_layer; j++){
                    this->outputs[i][j] = exp(inputs[i][j]-max);
                    sum += this->outputs[i][j];
                }
                for(int j = 0; j < prev_layer; j++){
                    if(i== 0 && j == 0){
                        //std::cout << sum << std::endl;
                    }
                    this->outputs[i][j] = this->outputs[i][j]/(sum+1e-7);
                }
            }
            return this->outputs;
        }
        NumType** backward(NumType** dvalues) override{
            this->dinputs = new NumType*[saved_samples];
            for(int i = 0; i < saved_samples; i++){
                this->dinputs[i] = dvalsXJacobian(this->outputs[i], saved_prev_layer, dvalues[i]); 
                //std::cout << "DINPUT OF SOFTMAX" << std::endl;
                //std::cout << dinputs[i][0] << std::endl;
            }
            //matrixViewer(dinputs, samples, 2);
            return this->dinputs;
        }
        void print() override{
            std::cout << " Softmax " << std::endl;
        }
};

#endif