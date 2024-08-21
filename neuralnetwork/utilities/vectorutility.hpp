#ifndef VECTORUTILITY_H
#define VECTORUTILITY_H
#include <cmath>
#include <iostream>

float vectorSum(float* vector, int components){
    float sum = 0.0f;
    for(int i = 0; i < components; i++){
        sum += vector[i];
    }
    return sum;
}

float vectorMean(float* vector, int components){
    return vectorSum(vector, components)/components;
}

float* vectorClip(float* vector, int components, float maxClip, float minClip){
    float clipper = exp(-7);
    maxClip -= clipper;
    minClip += clipper;
    for(int i = 0; i < components; i++){
        if(vector[i] < minClip){
            vector[i] = minClip;
        }
        else if(vector[i] > maxClip){
            vector[i] = maxClip;
        }
    }
    return vector;
}

float* vectorLog(float* vector, int components){
    for(int i = 0; i < components; i++){
        vector[i] = log(vector[i]);
    }
    return vector;
}

float* vectorLogNeg(float* vector, int components){
    for(int i = 0; i < components; i++){
        //std::cout << vector[i] << std::endl;
        vector[i] = -log(vector[i]);
        //std::cout << vector[i] << std::endl;
    }
    return vector;
}

// Creates an identical matrix with copied values on a different address.
float* copyVector(float* vector, int components){
    float* copied = new float[components];
    for(int i = 0; i < components; i++){
        copied[i] = vector[i];
    }
    return copied;
}

void clearVector(float* vector){
    if (vector != nullptr) {
        delete[] vector;
        vector = nullptr;
    }    
}

#endif