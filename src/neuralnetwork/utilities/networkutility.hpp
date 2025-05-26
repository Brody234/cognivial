#ifndef NETWORKUTILITY_H
#define NETWORKUTILITY_H
#include <cmath>
#include <iostream>

template <typename NumType = float>
NumType accuracy(Array<NumType, 2> softmax_output, Array<int, 1> correct_predictions, int samples, int output_layer){
    int* predictions = new int[samples];
    int total = 0;
    for(int i = 0; i < samples; i++){
        predictions[i] = 0;
        for(int j = 1; j < output_layer; j++){
            if(softmax_output[i][j] > softmax_output[i][predictions[i]]){
                predictions[i] = j;
            }
        }
        if(predictions[i] == correct_predictions[i]){
            total++;
        }
    }
    delete[] predictions;
    return NumType(total)/samples;

}

template <typename NumType = float>
NumType percentError(NumType pred, NumType act){
    return abs((pred-act)/(act));
}

template <typename NumType = float>
NumType accuracyNp(NumType** y_pred, NumType** y_true, int samples, int output_layer, NumType n){
    int total = 0;
    for(int i = 0; i < samples; i++){
        for(int j = 0; j < output_layer; j++){
            if(n>= percentError(y_pred[i][j], y_true[i][j])){
                total++;
            }
        }
    }
    return NumType(total)/samples;

}

template <typename NumType = float>
NumType averagePercentError(NumType** y_pred, NumType** y_true, int samples, int output_layer){
    NumType total = 0.0f;
    for(int i = 0; i < samples; i++){
        for(int j = 0; j < output_layer; j++){
            total += percentError(y_pred[i][j], y_true[i][j]);            
        }
    }
    return total/(samples*output_layer);

}

template <typename NumType = float>
int* predictionIndices(NumType** softmax_output, int samples, int output_layer){
    int* predictions = new int[samples];
    for(int i = 0; i < samples; i++){
        predictions[i] = 0;
        for(int j = 1; j < output_layer; j++){
            if(softmax_output[i][j] > softmax_output[i][predictions[i]]){
                predictions[i] = j;
            }
        }
    }
    return predictions;
}

#endif