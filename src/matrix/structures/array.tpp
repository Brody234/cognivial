#ifndef ARRAYTPP
#define ARRAYTPP

#include "array.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>

// N Dimensions

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

template <typename ArrType, std::size_t dims>
Array<ArrType, dims>::~Array() {
    if(owns)
        delete[] data;
    delete[] stride;
    delete[] shape;
}

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

template <typename ArrType, std::size_t dims>
Array<ArrType, dims> Array<ArrType, dims>::transpose() const{
    static_assert(dims==2, "Transpose is currently only implemented for 2D arrays.");

    std::size_t newShape[2] = { shape[1], shape[0] };
    std::size_t newStride[2] = { stride[1], stride[0] };

    return Array<ArrType, dims>(data, newStride, newShape);
}

// Dimension 1

template <typename ArrType>
Array<ArrType, 1>::Array(const std::size_t* s){
    owns = true;
    len = s[0];
    stride = 1;
    data = new ArrType[len];
}

template<typename ArrType>
Array<ArrType, 1>::~Array() {
    if(owns)
        delete[] data;
}

template<typename ArrType>
ArrType& Array<ArrType,1>::operator[](std::size_t idx) {
    if (idx >= len) throw std::out_of_range("Index out of bounds.");
    return data[idx * stride];
}

template<typename ArrType>
const ArrType& Array<ArrType, 1>::operator[](size_t idx) const {
    if (idx >= len) throw std::out_of_range("Index out of bounds.");
    return data[idx * stride];
}


template<typename ArrType>
std::string Array<ArrType, 1>::toString() const{
    if(len > 6){
        return "[ " + std::to_string(data[0]) + " " 
        + std::to_string(data[1]) + " " 
        + std::to_string(data[2]) + " ... " 
        + std::to_string(data[len-3]) + " " 
        + std::to_string(data[len-2]) + " " 
        + std::to_string(data[len-1]) + " ]";
    }
    else{
        std::string str = "[ ";
        for(size_t i = 0; i < len; i++){
            str += std::to_string(data[i*stride]) + " ";
        }
        str += "]";
        return str;
    }
}

#endif 
