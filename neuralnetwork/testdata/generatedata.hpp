#ifndef GENERATEDATA_H
#define GENERATEDATA_H
#include <random>
#include "../testdata/dataset.hpp"

DataSetSingleClassNeurons createLinearSamples(int num_samples){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rand(-1.0f, 1.0f);
    DataSetSingleClassNeurons dataset;
    dataset.x_values = new float*[num_samples];
    dataset.y_values = new int[num_samples];
    int onecount = 0;
    int zerocount = 0;
    for(int i = 0; i < num_samples; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        dataset.x_values[i][1] = rand(gen);
        if(dataset.x_values[i][0]<=dataset.x_values[i][1]){
            dataset.y_values[i] = 1; // assign 1 to the class of data above and on the line y = x
            onecount++;
        }
        else{
            dataset.y_values[i] = 0; // assign 0 to the class of data below line y = x
        }
    }
    std::cout << onecount << std::endl;
    return dataset;
}

DataSetSingleClassNeurons createLinearSamplesEven(int num_samples){
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> rand(-1.0f, 1.0f);
    DataSetSingleClassNeurons dataset;
    dataset.x_values = new float*[num_samples];
    dataset.y_values = new int[num_samples];
    int onecount = 0;
    int zerocount = 0;
    gen.seed(42);
    for(int i = 0; i < num_samples/2; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        std::uniform_real_distribution<float> randy(dataset.x_values[i][0], 1.0f);
        dataset.x_values[i][1] = randy(gen);

        dataset.y_values[i] = 1; // assign 1 to the class of data above and on the line y = x
        
        
    }
    for(int i = num_samples/2; i < num_samples; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        std::uniform_real_distribution<float> randy(-1.0f, dataset.x_values[i][0]);
        dataset.x_values[i][1] = randy(gen);

        dataset.y_values[i] = 0; // assign 0 to the class of data below line y = x

    }
    std::cout << onecount << std::endl;
    return dataset;
}

DataSetSingleClassNeurons createQ1Q3SamplesEven(int num_samples){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rand(0.0f, 1.0f);
    DataSetSingleClassNeurons dataset;
    dataset.x_values = new float*[num_samples];
    dataset.y_values = new int[num_samples];
    int onecount = 0;
    int zerocount = 0;
    for(int i = 0; i < num_samples/2; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        dataset.x_values[i][1] = rand(gen);

        dataset.y_values[i] = 1; // assign 1 to the class of data above and on the line y = x
        
        
    }
    for(int i = num_samples/2; i < num_samples; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = -rand(gen);
        dataset.x_values[i][1] = -rand(gen);

        dataset.y_values[i] = 0; // assign 0 to the class of data below line y = x

    }
    std::cout << onecount << std::endl;
    return dataset;
}

DataSetNoClassNeurons createLinearSamplesEvenYTrue2xS(int num_samples){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> rand(-1.0f, 1.0f);
    DataSetNoClassNeurons dataset;
    dataset.x_values = new float*[num_samples];
    dataset.y_values = new float*[num_samples];
    int onecount = 0;
    int zerocount = 0;
    for(int i = 0; i < num_samples/2; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        std::uniform_real_distribution<float> randy(dataset.x_values[i][0], 1.0f);
        dataset.x_values[i][1] = randy(gen);

        dataset.y_values[i] = new float[2]; // assign 1 to the class of data above and on the line y = x
        dataset.y_values[i][0] = 0;
        dataset.y_values[i][1] = 1;
        
    }
    for(int i = num_samples/2; i < num_samples; i++){
        dataset.x_values[i] = new float[2];
        dataset.x_values[i][0] = rand(gen);
        std::uniform_real_distribution<float> randy(-1.0f, dataset.x_values[i][0]);
        dataset.x_values[i][1] = randy(gen);

        dataset.y_values[i] = new float[2]; // assign 0 to the class of data below line y = x
        dataset.y_values[i][0] = 1;
        dataset.y_values[i][1] = 0;

    }
    std::cout << onecount << std::endl;
    return dataset;
}

#endif