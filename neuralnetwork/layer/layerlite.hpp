#ifndef LAYERLITE_H
#define LAYERLITE_H

#include <random>
#include <exception>
#include <iostream>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

class LayerLite
{
    private:
        float** input_save;
        float** dinputs = nullptr;
        int saved_samples;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> dis;

    public:
        float* biases;
        float** weights;

        float** dweights = nullptr ;
        float* dbiases = nullptr;

        int bias_size;
        int weight_size;
        int weight_inner_size;

        LayerLite(int prev_layer, int this_layer)
        : 
        dis(-1.0f, 1.0f)
        {
            gen.seed(42);
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
                    weights[i][j]= 0.5f*dis(gen);
                }
            }
        }
        float** forwardTest(float** input, int samples){
            saved_samples = samples;
            //print_weights();
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
            if (dbiases != nullptr && dbiases != NULL) {
                delete [] dbiases;  // Free previously allocated dweights
                dbiases = nullptr;
            }

            dbiases = new float[bias_size];
            for(int j = 0; j < bias_size; j++){
                    dbiases[j] = dvalues[0][j];
            }
            for(int i = 1; i < saved_samples; i++){ // colARowB
                for(int j = 0; j < weight_inner_size; j++){ // colB
                    dbiases[j] += dvalues[i][j];
                }
            }

            if (dweights != nullptr) {
                clearMatrix(dweights, weight_size);  // Free previously allocated dweights
                dweights = nullptr;
            }

            dweights = matrixDotTransposeProduct(input_save, dvalues, saved_samples, weight_size, weight_inner_size);
            //std::cout << "Layer w/ weights" << std::endl;
            //matrixViewer(dweights, weight_size, weight_inner_size);

            if (dinputs != nullptr) {
                clearMatrix(dinputs, saved_samples);  // Free previously allocated dinputs
                dinputs = nullptr;
            }
            //std::cout << weight_inner_size << weight_size << std::endl;
            dinputs = matrixDotProductTranspose(dvalues, weights, saved_samples, weight_inner_size, weight_size);
            //matrixViewer(dinputs, saved_samples, weight_inner_size);
            return dinputs;

        }
        void print_weights(){
            matrixViewer(weights, weight_size, weight_inner_size);
        }
        void print_biases(){
            matrixViewer(biases, bias_size);
        }
        float** get_weights(){
            //std::cout << "COPYING" << std::endl;
            return copyMatrix(weights, weight_size, weight_inner_size);
        }
        float* get_biases(){
            return copyVector(biases, bias_size);
        }
};

#endif