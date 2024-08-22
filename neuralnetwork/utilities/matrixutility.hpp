#ifndef MATRIXUTILITY_H
#define MATRIXUTILITY_H

#include <cmath>
#include <iostream>
#include "../testdata/viewer.hpp"

// Deletes a matrix from memory.
template <typename NumType = float>
void clearMatrix(NumType** matrix, int row){
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
template <typename NumType = float>
NumType** copyMatrix(NumType** matrix, int row, int col){
    NumType** copied = new NumType*[row];
    for(int i = 0; i < row; i++){
        copied[i] = new NumType[col];
        for(int j = 0; j < col; j++){
            copied[i][j] = matrix[i][j];
        }
    }
    return copied;
}

// Calculates the sum of elements in a matrix.
template <typename NumType = float>
NumType matrixSum(NumType** matrix, int row, int col){
    NumType sum = 0.0f;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Calculates the mean of the elements in a matrix.
template <typename NumType = float>
NumType matrixMean(NumType** matrix, int row, int col){
    int total = row*col;
    return matrixSum(matrix, row, col)/total;
}

// Takes every value in a matrix and clips it between maxClip - e^-50 and minClip + e^-50.
template <typename NumType = float>
NumType** matrixClip(NumType** matrix, int row, int col, NumType maxClip, NumType minClip){
    NumType clipper = 1e-7;
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
template <typename NumType = float>
NumType** matrixLog(NumType** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = log(matrix[i][j]);
        }
    }
    return matrix;
}

// Directly modifies the passed matrix. Sets every value to the negative ln of said value.
template <typename NumType = float>
NumType** matrixLogNeg(NumType** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            matrix[i][j] = -log(matrix[i][j]);
        }
    }
    return matrix;
}

// Returns a vector of length rows, each component is the inverse log of it's respective row.
template <typename NumType = float>
NumType* matrixLogNegVectorSum(NumType** matrix, int row, int col){
    NumType* vectorSum = new NumType[row];
    //std::cout << "row " << row << " col " << col << std::endl;
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
template <typename NumType = float>
NumType** matrixAdd(NumType** matrixA, NumType** matrixB, int row, int col){
    NumType** matrixC = new NumType*[row];
    for(int i = 0; i < row; i++){
        matrixC[i] = new NumType[col];
        for(int j = 0; j < col; j++){
            matrixC[i][j] =matrixA[i][j] + matrixB[i][j];
        }
    }
    return matrixC;
}

// A-B
template <typename NumType = float>
NumType** matrixSubtract(NumType** matrixA, NumType** matrixB, int row, int col){
    NumType** matrixC = new NumType*[row];
    for(int i = 0; i < row; i++){
        matrixC[i] = new NumType[col];
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
template <typename NumType = float>
NumType** matrixDotProduct(NumType** matrixA, NumType** matrixB, int colArowB, int rowA, int colB){
    NumType** matrixC = new NumType*[rowA];
    for(int i = 0; i < rowA; i++){
        matrixC[i] = new NumType[colB];
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
template <typename NumType = float>
NumType** matrixDotTransposeProduct(NumType** matrixA, NumType** matrixB, int rowArowB, int colA, int colB){
    NumType** matrixC = new NumType*[colA];
    for(int i = 0; i < colA; i++){
        matrixC[i] = new NumType[colB];
        for(int k = 0; k < colB; k++){
            matrixC[i][k] = 0.0f;
            for(int j = 0; j < rowArowB; j++){
                if(matrixB[j][k] < 0){
                    //std::cout<< "j " << j << " k "<< k << std::endl;

                }
                matrixC[i][k] += matrixA[j][i] * matrixB[j][k];
                //std::cout << "C += " << matrixA[j][i] << " * " << matrixB[j][k] << " = " << matrixA[j][i] * matrixB[j][k] << std::endl;
            }
            //std::cout << "C: " << matrixC[i][k] << std::endl;
        }
    }
    return matrixC;
}

// A*BT
template <typename NumType = float>
NumType** matrixDotProductTranspose(NumType** matrixA, NumType** matrixB, int rowA, int colAcolB, int rowB) {    
    NumType** matrixC = new NumType*[rowA];
    for(int i = 0; i < rowA; i++) {
        matrixC[i] = new NumType[rowB];
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


template <typename NumType = float>
NumType** diagonalize(NumType* vector, int components){
    NumType** matrix = new NumType*[components];
    for(int i = 0; i < components; i++){
        matrix[i] = new NumType[components];
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

template <typename NumType = float>
NumType** jacobian(NumType* vector, int components){
    NumType** matrix = new NumType*[components];
    for(int i = 0; i < components; i++){
        matrix[i] = new NumType[components];
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

template <typename NumType = float>
NumType* dvalsXJacobian(NumType* vector, int components, NumType* dvalues) {
    NumType* newvector = new NumType[components];
    //NumType** jacob = new NumType*[components];
    for(int i = 0; i < components; i++) {
        newvector[i] = 0.0f;
        //jacob[i] = new NumType[components];
        for(int j = 0; j < components; j++) {
            if (i == j) {
                //jacob[i][j] = vector[i] * (1-vector[i]);
                newvector[i] += (vector[i] * (1-vector[i])) * dvalues[j];
            } else {
                //jacob[i][j] = (-vector[i] * vector[j]);

                newvector[i] += (-vector[i] * vector[j]) * dvalues[j];
            }
        }
    }
    //matrixViewer(jacob, 2, 2);
    return newvector;
}

template <typename NumType = float>
NumType matrixAbsMean(NumType** matrix, int rows, int cols){
    NumType sum = 0;
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