#ifndef ARRAYTPP
#define ARRAYTPP

#include "array.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using std::size_t;
/*
 * This file implements the header of the same name.
 * It is likely loosely commented for my personal debugging. 
 * For thorough documentation, clear explanations, etc. use the associated header file. 
 */

// N Dimensions

//public constructor
template <typename ArrType, std::size_t dims>
Array<ArrType, dims>::Array(const std::size_t* s)
{
    owns = true;
    std::size_t total = 1;
    shape = new std::size_t[dims];
    for (std::size_t i = 0; i < dims; ++i) {
        shape[i] = s[i];
        total *= shape[i];
    }

    stride = new std::size_t[dims];
    stride[dims-1] = 1;
    
    for(int i = int(dims)-2; i >= 0; --i){
        stride[i] = stride[i+1] * shape[i+1];
    }

    data = new ArrType[total]();
}

//delete
template <typename ArrType, std::size_t dims>
Array<ArrType, dims>::~Array() {
    if(owns)
        delete[] data;
    delete[] stride;
    delete[] shape;
}

//should be private constructor
template <typename ArrType, std::size_t dims>
Array<ArrType, dims>::Array(ArrType* d, std::size_t* _stride, std::size_t* _shape)
: data(d), owns(false)
    {
        shape = new std::size_t[dims];
        stride = new std::size_t[dims];
        for(std::size_t i = 0; i < dims; i++){
            shape[i] = _shape[i];
            stride[i] = _stride[i];
        }
    }

//should be private constructor
template <typename ArrType, std::size_t dims>
Array<ArrType, dims>::Array(ArrType* d, std::size_t* _stride, std::size_t* _shape, bool owns)
: data(d), owns(owns)
    {
        shape = new std::size_t[dims];
        stride = new std::size_t[dims];
        for(std::size_t i = 0; i < dims; i++){
            shape[i] = _shape[i];
            stride[i] = _stride[i];
        }
    }

// [] operator override for arr[]
template <typename ArrType, std::size_t dims>
Array<ArrType, dims-1> Array<ArrType, dims>::operator[](std::size_t idx){
    if (idx >= shape[0]) throw std::out_of_range("Index out of bounds.");
    if constexpr(dims > 2){
        std::size_t newShape[dims-1];
        std::size_t newStride[dims-1];

        for(std::size_t i = 0; i < dims-1; i++){
            newShape[i] = shape[i+1];
            newStride[i] = stride[i+1];
        }

        ArrType* newData = data + idx * stride[0];
        return Array<ArrType, dims-1>(newData, newStride, newShape);
    }
    else{
        std::size_t len = shape[1];
        std::size_t s = stride[1];

        ArrType* newData = data + idx * stride[0];
        return Array<ArrType, 1>(len, s, newData);
    }
}

// same as previous, but const
template <typename ArrType, std::size_t dims>
Array<ArrType, dims-1> Array<ArrType, dims>::operator[](std::size_t idx) const{
    if (idx >= shape[0]) throw std::out_of_range("Index out of bounds.");
    if constexpr(dims > 2){
        std::size_t newShape[dims-1];
        std::size_t newStride[dims-1];

        for(std::size_t i = 0; i < dims-1; i++){
            newShape[i] = shape[i+1];
            newStride[i] = stride[i+1];
        }

        ArrType* newData = data + idx * stride[0];
        return Array<ArrType, dims-1>(newData, newStride, newShape);
    }
    else{
        std::size_t len = shape[1];
        std::size_t s = stride[1];

        ArrType* newData = data + idx * stride[0];
        return Array<ArrType, 1>(len, s, newData);
    }
}

// recursive function that returns the array visualized as a string.
template<typename ArrType, std::size_t dims>
std::string Array<ArrType, dims>::toString() const{
    if(shape[0] > 6){
        return "[\n " 
        + (*this)[0].toString() + "\n " 
        + (*this)[1].toString() + "\n " 
        + (*this)[2].toString() + "\n ... \n" 
        + (*this)[(shape[0]-3)].toString() + "\n " 
        + (*this)[(shape[0]-2)].toString() + "\n " 
        + (*this)[(shape[0]-1)].toString()+ "\n]";
    }
    else{
        std::string str = "[\n";
        for(size_t i = 0; i < shape[0]; i++){
            str += " " + (*this)[i].toString() + "\n";
        }
        str += "]";
        return str;
    }
}

// Returns a transposed VIEW of the same data.
template <typename ArrType, std::size_t dims>
Array<ArrType, dims> Array<ArrType, dims>::transpose() const{
    static_assert(dims==2, "Transpose is currently only implemented for 2D arrays.");

    std::size_t newShape[2] = { shape[1], shape[0] };
    std::size_t newStride[2] = { stride[1], stride[0] };

    return Array<ArrType, dims>(data, newStride, newShape);
}

// copies the array into a new block of memory
template <typename ArrType, std::size_t dims>
Array<ArrType, dims> Array<ArrType, dims>::copy(){
    // This section is an O(dims) time portion that checks if the Array was unchanged/shape is default.
    // If the array is unchanged, time complexity goes from O(dims*total) to O(total).
    size_t total = 1;
    size_t* newStrides = new std::size_t[dims];
    newStrides[dims-1] = 1;
    for(size_t i = 0; i < dims; i++){
        total *= shape[i];
    }
    bool unchanged = true;
    // i is a long here because size_t is unsigned so decrementing it results in an underflow (it's always geq 0).
    for(long i = dims-2; i >= 0; i--){
        newStrides[i] = shape[i+1]*newStrides[i+1];
        if(stride[i] != shape[i+1]*stride[i+1]){
            unchanged = false;
        }
    }

    if(stride[dims-1] == 1 && unchanged){
        // This is the function call that optimizes copying arrays whose strides are default.
        return copyTurbo(total);
    }

    ArrType* newData = new ArrType[total];
    for(size_t i = 0; i < total; i++){
        size_t* idx = new size_t[dims];
        size_t newI = i;
        size_t loc = 0;
        for (int k = dims - 1; k >= 0; --k) {
            loc   += stride[k] * (newI % shape[k]);
            newI  /= shape[k];
        }

        newData[i] = data[loc];
    }
    return Array<ArrType, dims>(newData, newStrides, shape, true);
}

// copies data, shape and strides directly, with 0 checks for any edge cases.
template <typename ArrType, size_t dims>
Array<ArrType, dims> Array<ArrType, dims>::copyTurbo(std::size_t total){
    ArrType* newData = new ArrType[total];
    for(std::size_t i = 0; i < total; i++){
        newData[i] = data[i]; 
    }
    return Array<ArrType, dims>(newData, stride, shape);
}

// Scalar multiplication
template <typename ArrType, size_t dims>
void Array<ArrType, dims>::operator*=(ArrType num){
    static_assert(std::is_arithmetic_v<ArrType>,"Scalar multiplication is currently only available for numerical types.");

    size_t total = 1;
    for(size_t i = 0; i < dims; i++){
        total *= shape[i];
    }
    
    bool unchanged = true;
    // i is a long here because size_t is unsigned so decrementing it results in an underflow (it's always geq 0).
    for(long i = dims-2; i >= 0; i--){
        if(stride[i] != shape[i+1]*stride[i+1]){
            unchanged = false;
        }
    }

    if(stride[dims-1] == 1 && unchanged){
        // This is the function call that optimizes copying arrays whose strides are default.
        return scalarMultTurbo(num, total);
    }

    // Copied and pasted from copy()
    ArrType* newData = new ArrType[total];
    for(size_t i = 0; i < total; i++){
        size_t* idx = new size_t[dims];
        size_t newI = i;
        size_t loc = 0;
        for (int k = dims - 1; k >= 0; --k) {
            loc   += stride[k] * (newI % shape[k]);
            newI  /= shape[k];
        }

        data[loc] *= num;
    }
    return;

}

// Fast scalar mult for simple arrays
template <typename ArrType, size_t dims>
void Array<ArrType, dims>::scalarMultTurbo(ArrType num, size_t total){
    for(size_t i = 0; i < total; i++){
        data[i] *= num;
    }
    return;
}

// Scalar addition
template <typename ArrType, size_t dims>
void Array<ArrType, dims>::operator+=(ArrType num){
    static_assert(std::is_arithmetic_v<ArrType>,"Scalar multiplication is currently only available for numerical types.");

    size_t total = 1;
    for(size_t i = 0; i < dims; i++){
        total *= shape[i];
    }
    
    bool unchanged = true;
    // i is a long here because size_t is unsigned so decrementing it results in an underflow (it's always geq 0).
    for(long i = dims-2; i >= 0; i--){
        if(stride[i] != shape[i+1]*stride[i+1]){
            unchanged = false;
        }
    }

    if(stride[dims-1] == 1 && unchanged){
        // This is the function call that optimizes copying arrays whose strides are default.
        return scalarAddTurbo(num, total);
    }

    // Copied and pasted from copy()
    ArrType* newData = new ArrType[total];
    for(size_t i = 0; i < total; i++){
        size_t* idx = new size_t[dims];
        size_t newI = i;
        size_t loc = 0;
        for (int k = dims - 1; k >= 0; --k) {
            loc   += stride[k] * (newI % shape[k]);
            newI  /= shape[k];
        }

        data[loc] += num;
    }
    return;

}

// Fast scalar addition for simple arrays
template <typename ArrType, size_t dims>
void Array<ArrType, dims>::scalarAddTurbo(ArrType num, size_t total){
    for(size_t i = 0; i < total; i++){
        data[i] += num;
    }
    return;
}


// Dimension 1

// public constructor, uses an array for length, supposed to be length one but technically doesn't matter, len is first index.
template <typename ArrType>
Array<ArrType, 1>::Array(const std::size_t* s){
    owns = true;
    len = s[0];
    stride = 1;
    data = new ArrType[len];
}

// public constructor, uses a scalar for length.
template <typename ArrType>
Array<ArrType, 1>::Array(const std::size_t s){
    owns = true;
    len = s;
    stride = 1;
    data = new ArrType[len];
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
Array<ArrType, 1> Array<ArrType, 1>::copy() {
    Array<ArrType, 1> arr = new Array<ArrType, 1>(len);
    for(std::size_t i = 0; i < len; i++){
        arr[i] = (*this)[i]; // this pointer to access the correct datapoint regardless of stride values.
    }
    return arr;
}

template<typename ArrType>
void Array<ArrType, 1>::operator*=(ArrType num){
    for(size_t i = 0; i < len; i++){
        data[i]*=num;
    }
    return;
}

template<typename ArrType>
void Array<ArrType, 1>::operator+=(ArrType num){
    for(size_t i = 0; i < len; i++){
        data[i]+=num;
    }
    return;
}

#endif 
