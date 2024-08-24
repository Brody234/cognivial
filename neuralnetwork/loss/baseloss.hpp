#ifndef BASELOSS_H
#define BASELOSS_H

template <typename NumType = float>
class BaseLoss {
public:
    virtual ~BaseLoss() = default;

    NumType** outputs = nullptr;

    NumType** dvalues = nullptr;

    virtual NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int** actualMatrix) = 0; // From cce primary

    virtual NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int* actualMatrix) = 0; // From cce secondary

    virtual NumType forwardRegress(NumType** outputMatrix, int samples, int output_neurons, NumType** actualMatrix) = 0;

    virtual NumType** backwardClass(int output_neurons, int* y_true, NumType** softouts) = 0; // From CCE back

    virtual NumType** backwardRegress(NumType** y_pred, NumType** y_true) = 0;
};

#endif
