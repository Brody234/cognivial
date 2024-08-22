#ifndef BASELOSS_H
#define BASELOSS_H

template <typename NumType = float>
class BaseLoss {
public:
    virtual ~BaseLoss() = default;

    NumType** outputs = nullptr;

    NumType** dvalues = nullptr;

    virtual NumType forwardTest(NumType** outputMatrix, int samples, int output_neurons, int** actualMatrix) = 0; // From cce primary

    virtual NumType forwardTest(NumType** outputMatrix, int samples, int output_neurons, int* actualMatrix) = 0; // From cce secondary

    virtual NumType** backward(int output_neurons, int* y_true, NumType** softouts) = 0; // From CCE back
};

#endif
