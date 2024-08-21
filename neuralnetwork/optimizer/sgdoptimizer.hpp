#ifndef SGDOPTIMIZER_H
#define SGDOPTIMIZER_H

#include <iostream>

#include "../layer/layerlite.hpp"

class OptimizerSGD
{
    private:
        float learning_rate;
        bool momentum;
        float decay;
        int iterations;
        float original_learning_rate;
    public:
        OptimizerSGD(float learning_rateVal, bool momentumVal){
            learning_rate = learning_rateVal;
            momentum = momentumVal;
            decay = 1.0f;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        OptimizerSGD(float learning_rateVal){
            learning_rate = learning_rateVal;
            momentum = false;
            decay = 1.0f;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        OptimizerSGD(float learning_rateVal, bool momentumVal, float decayVal){
            learning_rate = learning_rateVal;
            momentum = momentumVal;
            decay = decayVal;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }
        /*OptimizerSGD(float learning_rateVal, float decayVal){
            learning_rate = learning_rateVal;
            momentum = false;
            decay = decayVal;
            iterations = 0;
            original_learning_rate = learning_rateVal;
        }*/
        void preupdate(){
            learning_rate = original_learning_rate*(1.0f/(1.0f + decay * iterations));
            iterations++;
        }
        void optimize_layer(LayerLite* layer){
            if(momentum){

            }
            else{
                for(int i = 0; i < layer->weight_size; i++){
                    for(int j = 0; j < layer->weight_inner_size; j++){
                        //std::cout << layer->dweights[i][j] << std::endl;
                        float prevWeight = layer->weights[i][j];

                        /*if((i+j) %2 == 0){
                            layer->weights[i][j] += .001f;
                        }
                        if((i+j) %2 == 1){
                            layer->weights[i][j] += -0.001f;
                        }*/
                        //std::cout << i << " " << j << " : " << layer->dweights[i][j] << std::endl;
                        layer->weights[i][j] += -learning_rate*layer->dweights[i][j];
                        float percentchange = prevWeight-layer->weights[i][j];
                        //std::cout << learning_rate*layer->dweights[i][j] << std::endl;

                            //std::cout << i << j << " : " << -learning_rate*layer->dweights[i][j] << std::endl;
                        
                    }
                }
                for(int i = 0; i < layer->bias_size; i++){
                    if(i < 3){
                        //std::cout << layer->dbiases[i] << std::endl;
                    }
                    layer->biases[i] += -learning_rate*layer->dbiases[i];
                }
                //learning_rate*= .98;
            }
        }
};

#endif