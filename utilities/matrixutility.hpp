#ifndef MATRIXUTILITY_H
#define MATRIXUTILITY_H

void clearMatrix(float** matrix, int row){
    for(int i = 0; i < row; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
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

#endif