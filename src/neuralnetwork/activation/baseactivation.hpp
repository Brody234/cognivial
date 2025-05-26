#ifndef BASEACTIVATION_H
#define BASEACTIVATION_H

template <typename NumType = float>
class BaseActivation {
public:
    virtual ~BaseActivation() = default;

    Array<NumType, 2> outputs;

    Array<NumType, 2> dinputs;

    virtual Array<NumType, 2> forward(Array<NumType, 2>& inputs, size_t samples, size_t prev_layer) = 0;

    virtual Array<NumType, 2> backward(Array<NumType, 2>& dvalues) = 0;
    
    virtual void print() = 0;
};

#endif
