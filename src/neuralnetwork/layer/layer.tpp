#ifndef LAYERTPP
#define LAYERTPP

#include "layer.hpp"

template <typename NumType>
Layer<NumType>::Layer(size_t prev_layer, size_t this_layer, bool momentumVal)
: 
dis(-sqrt(6.0f/(prev_layer+this_layer)), sqrt(6.0f/(prev_layer+this_layer)))
{
    gen.seed(rd());
    biases = Array<NumType, 1>(this_layer);
    weight_inner_size = this_layer;
    size_t weightShape[2] = {prev_layer, this_layer};
    weights = Array<NumType, 2>(weightShape);
    for(size_t i = 0; i < this_layer; i++){
        biases[i] = 0.0f;
    }
    for(size_t i = 0; i < prev_layer; i++){
        for(size_t j = 0; j < this_layer; j++){
            weights[i][j]= 0.5f*dis(gen);
        }
    }
    momentum = momentumVal;
}

template <typename NumType>
Array<NumType, 2> Layer<NumType>::forward(Array<NumType, 2> const& input){
    size_t outputsShape[2] = {input.shape[0], biases.len};
    outputs = Array<NumType, 2>(outputsShape);
    size_t arr[2] = {input.shape[0], weights.shape[0]};
    inputSave = Array<NumType, 2>(arr);
    for(size_t k = 0; k < input.shape[0]; k++){                
        for(size_t i = 0; i < biases.len; i++){
            outputs[k][i] = 0.0f;
            for(size_t j = 0; j < weights.shape[0]; j++){
                outputs[k][i] += input[k][j] * weights[j][i];
                inputSave[k][j] = input[k][j];
            }
            outputs[k][i] += biases[i];
        }
    }
    return outputs;
}

template <typename NumType>
Array<NumType, 1> Layer<NumType>::forwardRL(Array<NumType, 1> const& input){
    auto* in = new Array<NumType, 1>(weights.shape[0]);
    auto* out = new Array<NumType, 1>(biases.len);

    for(int i = 0; i < in->len; i++){
        (*in)[i] = input[i];
    }
    for(int i = 0; i < biases.len; i++){
        (*out)[i] = biases[i];
        for(int j = 0; j < weights.shape[0]; j++){
            (*out)[i] += (*in)[j] * weights[j][i];
        }
    }
    inputsRL.push_back(in);
    outputsRL.push_back(out);
    return (*out); // FIX WHEN MOVE CONSTRUCTOR IS ADDED TO ARRAY CLASS I KNOW IT SHOULD ALREADY EXIST DON'T JUDGE ME
}

template <typename NumType>
void Layer<NumType>::endEpisodeRL(){
    size_t epSize = inputsRL.size();
    size_t inArr[2] = {epSize, weights.shape[0]};
    inputSave = Array<NumType, 2>(inArr);
    size_t outArr[2] = {epSize, biases.len};
    outputs = Array<NumType, 2>(outArr);
    for(size_t i = 0; i < epSize; i++){
        for(size_t j = 0; j < weights.shape[0]; j++){
            inputSave[i][j] = (*inputsRL[i])[j];
        }
        for(size_t j = 0; j < biases.len; j++){
            outputs[i][j] = (*outputsRL[i])[j];
        }
        delete inputsRL[i];
        delete outputsRL[i];
    }
    inputsRL.clear();
    outputsRL.clear();
}

template <typename NumType>
Array<NumType, 2> Layer<NumType>::backward(Array<NumType, 2>& dvalues){
    dbiases = Array<NumType, 1>(biases.len);
    for(size_t j = 0; j < biases.len; j++){
            dbiases[j] = dvalues[0][j];
    }

    for(size_t i = 1; i < dvalues.shape[0]; i++){ // colARowB
        for(size_t j = 0; j < weight_inner_size; j++){ // colB
            dbiases[j] += dvalues[i][j];
        }
    }

    dweights = (inputSave.transpose()) * dvalues;
    dinputs = dvalues * (weights.transpose());
    return dinputs;

}

#endif