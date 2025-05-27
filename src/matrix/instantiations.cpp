#include "matrix.hpp"

// Types of arrays in lib, can be any N dimensions and numeric type within hardware limitations

template class Array<int, 1>;
template class Array<int, 2>;

template class Array<float, 1>;
template class Array<float, 2>;

template class Array<double, 1>;
template class Array<double, 2>;