#ifndef ARRAY1DTPP
#define ARRAY1DTPP

#include "array.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using std::size_t;


// Dimension 1

// empty constructor
template <typename ArrType>
Array<ArrType, 1>::Array()
: data(nullptr), stride(0), len(0) {

}

// public constructor, uses an array for length, supposed to be length one but technically doesn't matter, len is first index.
template <typename ArrType>
Array<ArrType, 1>::Array(const std::size_t* s){
    owns = true;
    len = s[0];
    stride = 1;
    data = new ArrType[len]();
}

// public constructor, uses a scalar for length.
template <typename ArrType>
Array<ArrType, 1>::Array(const std::size_t s){
    owns = true;
    len = s;
    stride = 1;
    data = new ArrType[len]();
}

// copy constructor
template <typename ArrType>
Array<ArrType, 1>::Array(Array<ArrType, 1> const& other){
    owns = true;
    len = other.len;
    stride = 1;
    data = new ArrType[len];
    for(size_t i = 0; i < len; i++){
        data[i] = other[i];
    }
}

// deletes the array
template<typename ArrType>
Array<ArrType, 1>::~Array() {
    if(owns)
        delete[] data;
}

// lets arr[idx] work
template<typename ArrType>
ArrType& Array<ArrType,1>::operator[](std::size_t idx) {
    if (idx >= len) throw std::out_of_range("Index out of bounds.");
    return data[idx * stride];
}

// same but const
template<typename ArrType>
const ArrType& Array<ArrType, 1>::operator[](size_t idx) const {
    if (idx >= len) throw std::out_of_range("Index out of bounds.");
    return data[idx * stride];
}

// Prints a stringified version of the 1D array. Also recursive base case of nD toString().
template<typename ArrType>
std::string Array<ArrType, 1>::toString() const{
    if(len > 6){
        return "[ " + std::to_string(data[0]) + " " 
        + std::to_string((*this)[1]) + " " 
        + std::to_string((*this)[2]) + " ... " 
        + std::to_string((*this)[len-3]) + " " 
        + std::to_string((*this)[len-2]) + " " 
        + std::to_string((*this)[len-1]) + " ]";
    }
    else{
        std::string str = "[ ";
        for(size_t i = 0; i < len; i++){
            str += std::to_string((*this)[i]) + " ";
        }
        str += "]";
        return str;
    }
}

// Transposes the array.
template<typename ArrType>
Array<ArrType, 2> Array<ArrType, 1>::transpose() const{
    std::size_t* shape = new std::size_t[2];
    shape[0] = len;

    std::size_t* strides = new std::size_t[2];
    strides[0] = stride;

    shape[1] = 1;
    strides[1] = 1;

    return Array<ArrType, 2>(data, strides, shape);
}

// copies the data into a new block of memory
template<typename ArrType>
Array<ArrType, 1> Array<ArrType, 1>::copy() const{
    Array<ArrType, 1> arr = Array<ArrType, 1>(len);
    for(std::size_t i = 0; i < len; i++){
        arr[i] = (*this)[i]; // this pointer to access the correct datapoint regardless of stride values.
    }
    return arr;
}

// scales the vector.
template<typename ArrType>
void Array<ArrType, 1>::operator*=(ArrType num){
    for(size_t i = 0; i < len; i++){
        data[i]*=num;
    }
    return;
}

// adds a scalar to the vector
template<typename ArrType>
void Array<ArrType, 1>::operator+=(ArrType num){
    for(size_t i = 0; i < len; i++){
        data[i]+=num;
    }
    return;
}

// returns an array of the same shape but zeroed out
template <typename ArrType>
Array<ArrType, 1> Array<ArrType, 1>::zeros(){
    return Array<ArrType, 1>(len);
}

// dot product of vectors, A dot B^T
template <typename ArrType>
ArrType Array<ArrType, 1>::operator*(const Array<ArrType, 1>& B) const{
    if(len != B.len){
        throw std::length_error("Shape Error: Vectors have different lengths.");
    }
    size_t i = 0;
    size_t m = int(len/4) *4;
    ArrType acc = 0;
    for(; i < m; i+=4){
        // This is basically just politely asking the compiler to use mmx registers on 8 byte doubles.
        // I will drop a GPU and MMX update one day.
        acc += (*this)[i] * B[i] + (*this)[i+1]*B[i+1] + (*this)[i+2] * B[i+2] + (*this)[i+3]*B[i+3];
    }
    for(; i < len; i++){
        acc += (*this)[i] * B[i];
    }
    return acc;
}

template <typename ArrType>
Array<ArrType, 1> Array<ArrType, 1>::operator<=(const Array<ArrType, 1>& vector){
    if(vector.len != len){
        std::length_error("Shape Error: Vectors must have equal length");
    }
    for(size_t i = 0; i < len; i++){
        (*this)[i] = vector[i];
    }
    return *this;
}


template <typename ArrType>
Array<ArrType, 1>& Array<ArrType, 1>::operator=(const Array<ArrType, 1>& vector){
    if(this == &vector){
        return *this;
    }
    if(owns){
        delete[] data;
    }
    auto const copiedVector = vector.copy();
    len = copiedVector.len;
    stride = 1;
    data = new ArrType[len];

    for(size_t i = 0; i < len; i++){
        data[i] = copiedVector[i];
    }
    owns = true;
    return *this;
}

#endif 
