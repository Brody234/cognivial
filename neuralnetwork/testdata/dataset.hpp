#ifndef DATASET_H
#define DATASET_H

template <typename NumType = float>
struct DataSetMultiClassNeurons{
    NumType** x_values;
    int** y_values;
};

template <typename NumType = float>
struct DataSetSingleClassNeurons{
    NumType** x_values;
    int* y_values;
};
template <typename NumType = float>
struct DataSetNoClassNeurons{
    NumType** x_values;
    NumType** y_values;
};

#endif