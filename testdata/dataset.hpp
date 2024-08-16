#ifndef DATASET_H
#define DATASET_H

struct DataSetMultiClassNeurons{
    float** x_values;
    int** y_values;
};

struct DataSetSingleClassNeurons{
    float** x_values;
    int* y_values;
};

struct DataSetNoClassNeurons{
    float** x_values;
    float** y_values;
};

#endif