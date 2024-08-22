#ifndef NETWORKUTILITY_H
#define NETWORKUTILITY_H
#include <cmath>

template <typename NumType = float>
NumType accuracy(NumType** softmax_output, int* correct_predictions, int samples, int output_layer){
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
    return NumType(total)/samples;

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