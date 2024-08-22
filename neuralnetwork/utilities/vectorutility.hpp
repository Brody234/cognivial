#ifndef VECTORUTILITY_H
#define VECTORUTILITY_H
#include <cmath>
#include <iostream>

template <typename NumType = float>
NumType vectorSum(NumType* vector, int components){
    NumType sum = 0.0f;
    for(int i = 0; i < components; i++){
        sum += vector[i];
    }
    return sum;
}

template <typename NumType = float>
NumType vectorMean(NumType* vector, int components){
    return vectorSum(vector, components)/components;
}

template <typename NumType = float>
NumType* vectorClip(NumType* vector, int components, NumType maxClip, NumType minClip){
    NumType clipper = exp(-7);
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

template <typename NumType = float>
NumType* vectorLog(NumType* vector, int components){
    for(int i = 0; i < components; i++){
        vector[i] = log(vector[i]);
    }
    return vector;
}

// Creates an identical matrix with copied values on a different address.
template <typename NumType = float>
NumType* copyVector(NumType* vector, int components){
    NumType* copied = new NumType[components];
    for(int i = 0; i < components; i++){
        copied[i] = vector[i];
    }
    return copied;
}

template <typename NumType = float>
NumType* vectorLogNeg(NumType* vector, int components){
    NumType* newVect = copyVector(vector, components);
    for(int i = 0; i < components; i++){
        //std::cout << vector[i] << std::endl;
        newVect[i] = -log(vector[i]);
        //std::cout << vector[i] << std::endl;
    }
    return newVect;
}

template <typename NumType = float>
void clearVector(NumType* vector){
    if (vector != nullptr) {
        delete[] vector;
        vector = nullptr;
    }    
}

#endif