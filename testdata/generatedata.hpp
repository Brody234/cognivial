#ifndef GENERATEDATA_H
#define GENERATEDATA_H
#include <random>
#include "../testdata/dataset.hpp"

DataSetSingleClassNeurons createLinearSamples(int num_samples){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rand(-100.0f, 100.0f);
    DataSetSingleClassNeurons dataset;
    dataset.x_values = new float*[num_samples];
    dataset.y_values = new int[num_samples];
    for(int i = 0; i < num_samples; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        dataset.x_values[i][1] = rand(gen);
        if(dataset.x_values[i][0]<=dataset.x_values[i][1]){
            dataset.y_values[i] = 1; // assign 1 to the class of data above and on the line y = x
        }
        else{
            dataset.y_values[i] = 0; // assign 0 to the class of data below line y = x
        }
    }
    return dataset;
}

#endif