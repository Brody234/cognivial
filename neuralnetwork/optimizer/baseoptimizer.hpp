#ifndef BASEOPTIMIZER_H
#define BASEOPTIMIZER_H

template <typename NumType = float>
class BaseOptimizer {
public:
    virtual ~BaseOptimizer() = default;

    virtual void optimize_layer(LayerLite<NumType>* layer) = 0;
    
    virtual void optimize_prelu(ActivationPReLU<NumType>* prelu) = 0;

    virtual void preupdate() = 0;
};

#endif
