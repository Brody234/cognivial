#ifndef LAYERLITE_H
#define LAYERLITE_H

#include <random>
#include <exception>
#include <iostream>
#include <cmath>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LayerLite
{
    private:
        NumType** input_save;
        int saved_samples;
        bool momentum;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<NumType> dis;

    public:
        NumType** dinputs = nullptr;

        NumType* biases;
        NumType** weights;

        NumType** outputs;

        NumType** dweights = nullptr;
        NumType* dbiases = nullptr;
        
        int bias_size;
        int weight_size;
        int weight_inner_size;

        LayerLite(int prev_layer, int this_layer, bool momentumVal)
        : 
        dis(-sqrt(6.0f/(prev_layer+this_layer)), sqrt(6.0f/(prev_layer+this_layer)))
        {
            gen.seed(rd());
            biases = new NumType[this_layer];
            bias_size = this_layer;
            weight_size = prev_layer;
            weight_inner_size = this_layer;
            weights = new NumType*[prev_layer];
            for(int i = 0; i < this_layer; i++){
                biases[i] = 0.0f;
            }
            for(int i = 0; i < prev_layer; i++){
                weights[i] = new NumType[this_layer];
                for(int j = 0; j < this_layer; j++){
                    weights[i][j]= 0.5f*dis(gen);
                }
            }
            momentum = momentumVal;
        }
        NumType** forwardTest(NumType** input, int samples){
            saved_samples = samples;
            //print_weights();
            outputs = new NumType*[samples];
            input_save = new NumType*[samples];
            for(int k = 0; k < samples; k++){
                outputs[k] = new NumType[bias_size];
                input_save[k] = new NumType[weight_size];
                
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
        NumType** backward(NumType** dvalues){
            if (dbiases != nullptr && dbiases != NULL) {
                delete [] dbiases;  // Free previously allocated dweights
                dbiases = nullptr;
            }

            dbiases = new NumType[bias_size];
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
        NumType** get_weights(){
            //std::cout << "COPYING" << std::endl;
            return copyMatrix(weights, weight_size, weight_inner_size);
        }
        NumType* get_biases(){
            return copyVector(biases, bias_size);
        }
        void print(){
            std::cout << "Layer "<< weight_inner_size << " neurons and " << weight_size << " previous layer neurons" << std::endl;
        }
        int getPrevLayer(){
            return weight_size;
        }
        int getNeurons(){
            return weight_inner_size;
        }
};

#endif