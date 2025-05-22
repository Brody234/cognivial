#ifndef DATASET_H
#define DATASET_H

template <typename NumType = float>
struct DataSetMultiClassNeurons{
    Array<NumType, 2> x_values;
    Array<int, 1> y_values;
};

template <typename NumType = float>
struct DataSetSingleClassNeurons{
    Array<NumType, 2> x_values;
    Array<int, 1> y_values;
};
template <typename NumType = float>
struct DataSetNoClassNeurons{
    Array<NumType, 2> x_values;
    Array<NumType, 2> y_values;
};

#endif