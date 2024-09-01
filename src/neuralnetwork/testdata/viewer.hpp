#ifndef VIEWER_H
#define VIEWER_H
#include <iostream>


template <typename NumType = float>
void matrixViewer(NumType** matrix, int row, int col){
    std::cout << "[" << std::endl;
    //std::cout << row << std::endl;
    //std::cout << col << std::endl;
    //std::cout << matrix[0][0] << std::endl;
    for(int i = 0; i < row; i++){
        std::cout << "[ ";
        for(int j = 0; j < col; j++){
            std::cout << " " << matrix[i][j] << " ";
        }
        std::cout << " ]"<<std::endl;
    }
    std::cout << "]"<<std::endl;
    
}

template <typename NumType = float>
void matrixViewer(int** matrix, int row, int col){
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

template <typename NumType = float>
void matrixViewer(NumType* vector, int components){
    std::cout << "[ ";
    for(int i = 0; i < components; i++){
        std::cout << " " << vector[i] << " ";
    }
    std::cout << " ]"<<std::endl;
    
}

template <typename NumType = float>
void matrixViewer(int* vector, int components){
    std::cout << "[ ";
    for(int i = 0; i < components; i++){
        std::cout << " " << vector[i] << " ";
    }
    std::cout << " ]"<<std::endl;
    
}

template <typename NumType = float>
void parallelVectorizer(NumType* vector1, NumType* vector2, int components){
    std::cout << "[ ";
    for(int i = 0; i < components; i++){
        std::cout << " " << vector1[i] << " : " << vector2[i] << " ";
    }
    std::cout << " ]"<<std::endl;

}

#endif