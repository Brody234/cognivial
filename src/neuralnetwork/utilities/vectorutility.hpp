#ifndef VECTORUTILITY_H
#define VECTORUTILITY_H
#include <cmath>
#include <iostream>

template <typename NumType = float>
NumType vectorSum(Array<NumType, 1> vector, size_t components){
    NumType sum = 0.0f;
    for(size_t i = 0; i < components; i++){
        sum += vector[i];
    }
    return sum;
}

template <typename NumType = float>
NumType vectorMean(Array<NumType, 1> vector, size_t components){
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
Array<NumType, 1> copyVector(Array<NumType, 1> vector, size_t components){
    Array<NumType, 1> copied = vector.copy();
    return copied;
}

template <typename NumType = float>
Array<NumType, 1> vectorLogNeg(Array<NumType, 1> vector, size_t components){
    Array<NumType, 1> newVect = vector.copy();
    
    for(size_t i = 0; i < components; i++){
        newVect[i] = -log(vector[i]);
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