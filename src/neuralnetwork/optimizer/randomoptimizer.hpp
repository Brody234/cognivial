#ifndef RANDOMOPTIMIZER_H
#define RANDOMOPTIMIZER_H

#include <iostream>

#include "../layer/layer.hpp"

template <typename NumType = float>
class OptimizerRandom
{
    private:
        NumType learning_rate;
        NumType best_acc;
        NumType** bestweights;
        NumType* bestbiases;
        NumType best_loss;

        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<NumType> dis;

    public:
        OptimizerRandom(NumType learning_rateVal, Layer<NumType>* layer)
        :
        gen(rd()),
        dis(-1.0f, 1.0f)
        {
            bestweights = layer->get_weights();
            bestbiases = layer->get_biases();

            learning_rate = learning_rateVal;
            best_acc = 0.0f;
            best_loss = 500.0f;
        }
        

        void optimize_layer(Layer<NumType>* layer, NumType acc){
        if(acc < best_loss){
            //std::cout << "New best" << std::endl;
            clearMatrix(bestweights, layer->weight_size);
            clearVector(bestbiases);
            
            //std::cout << acc << std::endl;
            bestweights = layer->get_weights();
            bestbiases = layer->get_biases();
            best_loss = acc;
        }
        else{
            clearMatrix(layer->weights, layer->weight_size);
            clearVector(layer->biases);
            
            layer->weights = copyMatrix(bestweights, layer->weight_size, layer->weight_inner_size);
            layer->biases = copyVector(bestbiases, layer->bias_size);
        }


            for(int i = 0; i < layer->weight_size; i++){
                for(int j = 0; j < layer->weight_inner_size; j++){
                    //std::cout << layer->dweights[i][j] << std::endl;
                    
                    layer->weights[i][j] += -learning_rate*dis(gen);
                }
            }
            for(int i = 0; i < layer->bias_size; i++){
                layer->biases[i] += -learning_rate*dis(gen);
            }
        }
};

#endif