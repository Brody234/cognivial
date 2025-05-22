#include "../structures/array.hpp"
using std::size_t;
template <typename ArrType>
Array<ArrType, 2> copyMatrix(ArrType** mat, size_t rows, size_t cols){
    size_t* shape = {rows, cols};
    Array<ArrType, 2> arr(shape);
    for(size_t i = 0; i<rows; i++){
        for(size_t j = 0; j<cols; j++){
            arr[i][j] = mat[i][j];
        }
    }
    return arr;
}