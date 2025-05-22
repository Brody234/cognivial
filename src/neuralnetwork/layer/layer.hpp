#ifndef LAYER_H
#define LAYER_H

#include <random>
#include <exception>
#include <iostream>
#include <cmath>

using std::size_t;

#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class Layer
{
    private:
        Array<NumType, 2> input_save;
        int saved_samples;
        bool momentum;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<NumType> dis;

    public:
        Array<NumType, 2> dinputs;

        Array<NumType, 1> biases;
        Array<NumType, 2> weights;

        Array<NumType, 2> outputs;

        Array<NumType, 2> dweights;
        Array<NumType, 1> dbiases;
        
        size_t bias_size;
        size_t weight_size;
        size_t weight_inner_size;

        Layer(size_t prev_layer, size_t this_layer, bool momentumVal)
        : 
        dis(-sqrt(6.0f/(prev_layer+this_layer)), sqrt(6.0f/(prev_layer+this_layer)))
        {
            gen.seed(rd());
            biases = Array<NumType, 1>(this_layer);
            bias_size = this_layer;
            weight_size = prev_layer;
            weight_inner_size = this_layer;
            size_t* weightShape = {prev_layer, this_layer};
            weights = Array<NumType, 2>(weightShape);
            for(int i = 0; i < this_layer; i++){
                biases[i] = 0.0f;
            }
            for(int i = 0; i < prev_layer; i++){
                for(int j = 0; j < this_layer; j++){
                    weights[i][j]= 0.5f*dis(gen);
                }
            }
            momentum = momentumVal;
        }
        Array<NumType, 2> forward(NumType** input, int samples){
            saved_samples = samples;
            size_t* outputsShape = {samples, bias_size};
            outputs = Array<NumType, 2>(outputsShape);
            size_t* arr = {samples, weight_size};
            input_save = Array<NumType, 2>(arr);
            for(int k = 0; k < samples; k++){                
                for(int i = 0; i < bias_size; i++){
                    outputs[k][i] = 0.0f;
                    for(int j = 0; j < weight_size; j++){
                        outputs[k][i] += input[k][j] * weights[j][i];
                        input_save[k][j] = input[k][j];
                    }
                    outputs[k][i] += biases[i];
                }
            }
            return outputs;
        }
        Array<NumType, 2> backward(Array<NumType, 2> dvalues){
            /*if (dbiases != nullptr && dbiases != NULL) {
                delete [] dbiases; 
                dbiases = nullptr;
            }*/

            dbiases = Array<NumType, 1>(bias_size);
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
            dweights = input_save * (dvalues.transpose());
            //dweights = matrixDotTransposeProduct(input_save, dvalues, saved_samples, weight_size, weight_inner_size);

            //std::cout << "Layer w/ weights" << std::endl;
            //matrixViewer(dweights, weight_size, weight_inner_size);
            /*
            if (dinputs != nullptr) {
                clearMatrix(dinputs, saved_samples);  // Free previously allocated dinputs
                dinputs = nullptr;
            }*/
            //std::cout << weight_inner_size << weight_size << std::endl;
            dinputs = dvalues * (weights.transpose());
            //dinputs = matrixDotProductTranspose(dvalues, weights, saved_samples, weight_inner_size, weight_size);
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