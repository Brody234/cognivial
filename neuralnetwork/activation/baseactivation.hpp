#ifndef BASEACTIVATION_H
#define BASEACTIVATION_H

template <typename NumType = float>
class BaseActivation {
public:
    virtual ~BaseActivation() = default;

    NumType** outputs = nullptr;

    NumType** dinputs = nullptr;

    virtual NumType** forwardTest(NumType** inputs, int samples, int prev_layer) = 0;

    virtual NumType** backward(NumType** dvalues) = 0;
};

#endif
