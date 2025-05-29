#include "neuralnetwork.hpp"

// Layers

template class Layer<float>;
template class Layer<double>;

// Activations

template class ActivationReLU<float>;
template class ActivationReLU<double>;

//template class ActivationLeakyReLU<float>;
//template class ActivationLeakyReLU<double>;

//template class ActivationSoftMax<float>;
//template class ActivationSoftMax<double>;

// Losses

template class LossMAE<float>;
template class LossMAE<double>;

template class LossMSE<float>; //untested
template class LossMSE<double>; //untested

template class LossCCE<float>;
template class LossCCE<double>;

// Optimizers

template class OptimizerSGD<float>;
template class OptimizerSGD<double>;