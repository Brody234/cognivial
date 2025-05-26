#ifndef ACTIVATIONSOFTMAX_H
#define ACTIVATIONSOFTMAX_H
#include <cmath>
#include <iostream>
#include "../utilities/matrixutility.hpp"

template <typename NumType = float>
class ActivationSoftMax : public BaseActivation<NumType>
{
    private:
        size_t saved_samples;
        size_t saved_prev_layer;
    public:
        Array<NumType, 2> forward(Array<NumType, 2>& inputs, size_t samples, size_t prev_layer) override{
            //matrixViewer(inputs, samples, prev_layer);
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            if(samples <= 0){
                return Array<NumType, 2>();
            }
            /*if(this->outputs != nullptr){
                clearMatrix(this->outputs, samples);
                this->outputs = nullptr;
            }*/
            size_t outputsShape[2] = {samples, prev_layer};
            this->outputs = Array<NumType, 2>(outputsShape);
            for(int i = 0; i < samples; i++){
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
        Array<NumType, 2> backward(Array<NumType, 2>& dvalues) override{
            size_t dinputsShape[2] = {saved_samples, saved_prev_layer};
            this->dinputs = Array<NumType, 2>(dinputsShape);
            for(int i = 0; i < saved_samples; i++){
                this->dinputs[i] << dvalsXJacobian(this->outputs[i], saved_prev_layer, dvalues[i]); 
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