#ifndef SGDOPTIMIZER_H
#define SGDOPTIMIZER_H

#include <iostream>

#include "../layer/layerlite.hpp"

template <typename NumType = float>
class OptimizerSGD : public BaseOptimizer<NumType>
{
    private:
        NumType learning_rate;
        bool momentum;
        NumType decay;
        int iterations;
        NumType original_learning_rate;
    public:
        OptimizerSGD(NumType learning_rateVal, bool momentumVal){
            learning_rate = learning_rateVal;
            momentum = momentumVal;
            decay = 1.0f;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        OptimizerSGD(NumType learning_rateVal){
            learning_rate = learning_rateVal;
            momentum = false;
            decay = 1.0f;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        OptimizerSGD(NumType learning_rateVal, bool momentumVal, NumType decayVal){
            learning_rate = learning_rateVal;
            momentum = momentumVal;
            decay = decayVal;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        /*OptimizerSGD(NumType learning_rateVal, NumType decayVal){
            learning_rate = learning_rateVal;
            momentum = false;
            decay = decayVal;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }*/
        void preupdate() override{
            learning_rate = original_learning_rate*(1.0f/(1.0f + decay * iterations));
            iterations++;
        }
        void optimize_layer(LayerLite<NumType>* layer) override{
            if(momentum){

            }
            else{
                //NumType clip_value = 0.1f;
                for(int i = 0; i < layer->weight_size; i++){
                    for(int j = 0; j < layer->weight_inner_size; j++){
                       /* if (layer->dweights[i][j] > clip_value) {
                            layer->dweights[i][j] = clip_value;
                        } else if (layer->dweights[i][j] < -clip_value) {
                            layer->dweights[i][j] = -clip_value;
                        }*/

                        layer->weights[i][j] += -learning_rate*layer->dweights[i][j];
                        
                    }
                }
                for(int i = 0; i < layer->bias_size; i++){
                    /*if (layer->dbiases[i] > clip_value) {
                        layer->dbiases[i] = clip_value;
                    } else if (layer->dbiases[i] < -clip_value) {
                        layer->dbiases[i] = -clip_value;
                    }*/
                    layer->biases[i] += -learning_rate*layer->dbiases[i];
                }
            }
        }
        void optimize_prelu(ActivationPReLU<NumType>* prelu) override{
            if(momentum){

            }
            else{
                if(prelu->isArray){
                    for(int i = 0; i < prelu->saved_prev_layer; i++){
                        prelu->alpha[i] -= learning_rate*prelu->dalpha[i];
                    }
                }
                else{
                    prelu->alphaSingle -= learning_rate*prelu->dalphaSingle;
                }
            }
        }
};

#endif