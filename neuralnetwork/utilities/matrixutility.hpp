#ifndef MATRIXUTILITY_H
#define MATRIXUTILITY_H

#include <cmath>
#include <iostream>

// Deletes a matrix from memory.
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

// Creates an identical matrix with copied values on a different address.
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

// Calculates the sum of elements in a matrix.
float matrixSum(float** matrix, int row, int col){
    float sum = 0.0f;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Calculates the mean of the elements in a matrix.
float matrixMean(float** matrix, int row, int col){
    int total = row*col;
    return matrixSum(matrix, row, col)/total;
}

// Takes every value in a matrix and clips it between maxClip - e^-50 and minClip + e^-50.
float** matrixClip(float** matrix, int row, int col, float maxClip, float minClip){
    float clipper = 1e-7;
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

// Directly modifies matrix passed. Sets every value to the ln of said value.
float** matrixLog(float** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = log(matrix[i][j]);
        }
    }
    return matrix;
}

// Directly modifies the passed matrix. Sets every value to the negative ln of said value.
float** matrixLogNeg(float** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = -log(matrix[i][j]);
        }
    }
    return matrix;
}

// Returns a vector of length rows, each component is the inverse log of it's respective row.
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

// A+B
float** matrixAdd(float** matrixA, float** matrixB, int row, int col){
    float** matrixC = new float*[row];
    for(int i = 0; i < row; i++){
        matrixC[i] = new float[col];
        for(int j = 0; j < col; j++){
            matrixC[i][j] =matrixA[i][j] + matrixB[i][j];
        }
    }
    return matrixC;
}

// A-B
float** matrixSubtract(float** matrixA, float** matrixB, int row, int col){
    float** matrixC = new float*[row];
    for(int i = 0; i < row; i++){
        matrixC[i] = new float[col];
        for(int j = 0; j < col; j++){
            matrixC[i][j] =matrixA[i][j] - matrixB[i][j];
        }
    }
    return matrixC;
}

/* A         *  B
 *[ x11 x12 ] [ y11 ] -> [ (x11y11+x12y21) ]
 * [ x21 x22 ] [ y21 ]    [ (x21y11+x22y21) ]
 * [ x31 x32 ]            [ (x31y11+x32y21) ]
 * 
*/

// A dot B
float** matrixDotProduct(float** matrixA, float** matrixB, int colArowB, int rowA, int colB){
    float** matrixC = new float*[rowA];
    for(int i = 0; i < rowA; i++){
        matrixC[i] = new float[colB];
        for(int k = 0; k < colB; k++){
            matrixC[i][k] = 0.0f;
        }
        for(int j = 0; j < colArowB; j++){
            for(int k = 0; k < colB; k++){
                matrixC[i][k] += matrixA[i][j] * matrixB[i][k];
            }
        }
    }
    return matrixC;
}

// AT*B
float** matrixDotTransposeProduct(float** matrixA, float** matrixB, int rowArowB, int colA, int colB){
    float** matrixC = new float*[colA];
    for(int i = 0; i < colA; i++){
        matrixC[i] = new float[colB];
        for(int k = 0; k < colB; k++){
            matrixC[i][k] = 0.0f;
            for(int j = 0; j < rowArowB; j++){
                matrixC[i][k] += matrixA[j][i] * matrixB[j][k];
            }
        }
    }
    return matrixC;
}

// A*BT
float** matrixDotProductTranspose(float** matrixA, float** matrixB, int rowA, int colAcolB, int rowB) {    
    float** matrixC = new float*[rowA];
    for(int i = 0; i < rowA; i++) {
        matrixC[i] = new float[rowB];
        for(int k = 0; k < rowB; k++) { // k iterates over columns of matrixC and rows of matrixB
            matrixC[i][k] = 0.0f;
            for(int j = 0; j < colAcolB; j++) { // j iterates over the shared dimension
                matrixC[i][k] += matrixA[i][j] * matrixB[k][j]; // Accessing B as if it's transposed
            }
        }
    }
    //matrixViewer(matrixC, rowA, colB);
    return matrixC;
}



float** diagonalize(float* vector, int components){
    float** matrix = new float*[components];
    for(int i = 0; i < components; i++){
        matrix[i] = new float[components];
        for(int j = 0; j < components; j++){
            if(i==j){
                matrix[i][j] = vector[i];
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

float** jacobian(float* vector, int components){
    float** matrix = new float*[components];
    for(int i = 0; i < components; i++){
        matrix[i] = new float[components];
        for(int j = 0; j < components; j++){
            if(i == j){
                matrix[i][j] = vector[i] - vector[i]*vector[j];
            }
            else{
                matrix[i][j] = -vector[i]*vector[j];
            }
        }
    }
    return matrix;
}

// Takes vector, the saved inputs for a particular sample and that samples dvalues, creates the jacobian matrix of the vector and multiplies it by the dvalues for chain rule.
float* dvalsXJacobian(float* vector, int components, float* dvalues) {
    float* newvector = new float[components];

    for(int i = 0; i < components; i++) {
        newvector[i] = 0.0f;
        for(int j = 0; j < components; j++) {
            if (i == j) {
                newvector[i] += (vector[i] * (1 - vector[i])) * dvalues[j];
            } else {
                newvector[i] += (-vector[i] * vector[j]) * dvalues[j];
            }
        }
    }
    
    return newvector;
}

float matrixAbsMean(float** matrix, int rows, int cols){
    float sum = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <  cols; j++){
            if(matrix[i][j] > 0){
                sum += matrix[i][j];
            }
            else{
                sum -= matrix[i][j];
            }
        }
   }
   return sum/(rows*cols);
}

#endif