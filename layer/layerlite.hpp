#ifndef LAYERLITE_H
#define LAYERLITE_H

#include <random>
#include <exception>
#include <iostream>

class LayerLite
{
    private:
        float* biases;
        int bias_size;
        float** weights;
        int weight_size;
        int weight_inner_size;
        float** input_save;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> dis;

    public:
        LayerLite(int prev_layer, int this_layer)
        : 
        gen(rd()),
        dis(0.0f, 1.0f)
        {
            biases = new float[this_layer];
            bias_size = this_layer;
            weight_size = prev_layer;
            weight_inner_size = this_layer;
            weights = new float*[prev_layer];
            for(int i = 0; i < this_layer; i++){
                biases[i] = 0.0f;
            }
            for(int i = 0; i < prev_layer; i++){
                weights[i] = new float[this_layer];
                for(int j = 0; j < this_layer; j++){
                    weights[i][j]= dis(gen);
                }
            }
        }
        float** forwardTest(float** input, int samples){
            float** outputs = new float*[samples];
            input_save = new float*[samples];
            for(int k = 0; k < samples; k++){
                outputs[k] = new float[bias_size];
                input_save[k] = new float[weight_size];
                
                for(int i = 0; i < bias_size; i++){
                    outputs[k][i] = 0.0f;
                    for(int j = 0; j < weight_size; j++){
                        outputs[k][i] += input[k][j] * weights[j][i];
                        //std::cout << input[k][j] << std::endl;
                        input_save[k][j] = input[k][j];
                    }
                    outputs[k][i] += biases[i];
                }
            }
            return outputs;
        }
        float** backward(float** dvalues){
            int max = sizeof(dvalues);
            float** output = new float*[1];
            output[0] = new float[1];
            return output;
        }
};

#endif