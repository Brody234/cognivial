#ifndef VIEWER_H
#define VIEWER_H
#include <iostream>


void matrixViewer(float** matrix, int row, int col){
    std::cout << "[" << std::endl;
    for(int i = 0; i < row; i++){
        std::cout << "[ ";
        for(int j = 0; j < col; j++){
            std::cout << " " << matrix[i][j] << " ";
        }
        std::cout << " ]"<<std::endl;
    }
    std::cout << "]"<<std::endl;
    
}

#endif