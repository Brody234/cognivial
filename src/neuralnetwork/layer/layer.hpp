#pragma once

#ifndef LAYERHPP
#define LAYERHPP

#include <random>
#include <exception>
#include <iostream>
#include <cmath>

using std::size_t;
#include "../../matrix/matrix.hpp"

#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class Layer
{
    private:
        Array<NumType, 2> input_save;
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
        
        size_t weight_inner_size;

        Layer(size_t prev_layer, size_t this_layer, bool momentumVal);

        Array<NumType, 2> forward(Array<NumType, 2> const& input);
        
        Array<NumType, 2> backward(Array<NumType, 2>& dvalues);
        /*
        void print_weights(){
            matrixViewer(weights, weights.shape[0], weight_inner_size);
        }
        void print_biases(){
            matrixViewer(biases, biases.len);
        }
        NumType** get_weights(){
            //std::cout << "COPYING" << std::endl;
            return copyMatrix(weights, weights.shape[0], weight_inner_size);
        }
        NumType* get_biases(){
            return copyVector(biases, biases.len);
        }
        void print(){
            std::cout << "Layer "<< weight_inner_size << " neurons and " << weights.shape[0] << " previous layer neurons" << std::endl;
        }
        int getPrevLayer(){
            return weights.shape[0];
        }
        int getNeurons(){
            return weight_inner_size;
        }*/
};

#include "layer.tpp"

#endif