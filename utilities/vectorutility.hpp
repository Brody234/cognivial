#ifndef VECTORUTILITY_H
#define VECTORUTILITY_H
#include <cmath>

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
        vector[i] = -log(vector[i]);
    }
    return vector;
}

#endif