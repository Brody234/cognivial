#ifndef BASELOSS_H
#define BASELOSS_H

template <typename NumType = float>
class BaseLoss {
public:
    virtual ~BaseLoss() = default;

    Array<NumType, 2> outputs;

    Array<NumType, 2> dvalues;

    virtual NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 2>& actualMatrix) = 0; // From cce primary

    virtual NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 1>& actualMatrix) = 0; // From cce secondary

    virtual NumType forwardRegress(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<NumType, 2>& actualMatrix) = 0;

    virtual Array<NumType, 2> backwardClass(size_t output_neurons, Array<int, 1>& y_true, Array<NumType, 2>& softouts) = 0; // From CCE back

    virtual Array<NumType, 2> backwardRegress(Array<NumType, 2>& y_pred, Array<NumType, 2>& y_true) = 0;
};

#endif
