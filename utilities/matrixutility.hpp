#ifndef MATRIXUTILITY_H
#define MATRIXUTILITY_H

#include <cmath>

void clearMatrix(float** matrix, int row){
    if (matrix != nullptr) {
        for(int i = 0; i < row; i++) {
            if (matrix[i] != nullptr) {
                delete[] matrix[i];
                matrix[i] = nullptr;
            }
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

float** copyMatrix(float** matrix, int row, int col){
    float** copied = new float*[row];
    for(int i = 0; i < row; i++){
        copied[i] = new float[col];
        for(int j = 0; j < col; j++){
            copied[i][j] = matrix[i][j];
        }
    }
    return copied;
}

float matrixSum(float** matrix, int row, int col){
    float sum = 0.0f;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sum += matrix[i][j];
        }
    }
    return sum;
}

float matrixMean(float** matrix, int row, int col){
    int total = row*col;
    return matrixSum(matrix, row, col)/total;
}

float** matrixClip(float** matrix, int row, int col, float maxClip, float minClip){
    float clipper = exp(-100);
    maxClip -= clipper;
    minClip += clipper;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(matrix[i][j] < minClip){
                matrix[i][j] = minClip;
            }
            else if(matrix[i][j] > maxClip){
                matrix[i][j] = maxClip;
            }
        }
    }
    return matrix;
}

float** matrixLog(float** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = log(matrix[i][j]);
        }
    }
    return matrix;
}

float** matrixLogNeg(float** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = -log(matrix[i][j]);
        }
    }
    return matrix;
}

float* matrixLogNegVectorSum(float** matrix, int row, int col){
    float* vectorSum = new float[row];
    for(int i = 0; i < row; i++){
        vectorSum[i] = 0.0f;
        for(int j = 0; j < col; j++){
            vectorSum[i] += matrix[i][j];
        }
        vectorSum[i] = -log(vectorSum[i]);
    }
    return vectorSum;
}


#endif