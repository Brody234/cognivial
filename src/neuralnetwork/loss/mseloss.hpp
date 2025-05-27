#ifndef LOSSMSE_H
#define LOSSMSE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LossMSE : public BaseLoss<NumType>
{
    private:

    public:
        ~LossMSE() {
            
        }

        
        NumType forwardRegress(Array<NumType, 2>& outputMatrix, size_t samples, size_t prev_layer, Array<NumType, 2>& actualMatrix) override{
            NumType sum = 0.0f;

            for(int i = 0; i < samples; i++){
                for(int j = 0; j < prev_layer; j++){
                    NumType dif = actualMatrix[i][j] - outputMatrix[i][j];
                    sum += dif*dif;
                }
            }
            NumType mean = sum/(samples*prev_layer);

            return mean;
        }

        Array<NumType, 2> backwardRegress(Array<NumType, 2>& y_pred, Array<NumType, 2>& y_true) override{
            size_t shape[2] = {y_true.shape[0], y_true.shape[1]};
            this->dvalues = Array<NumType, 2>(shape);
            size_t elements = this->dvalues.shape[0]*this->dvalues.shape[1];
            for(int i = 0; i < this->dvalues.shape[0]; i++){

                for(int j = 0; j < this->dvalues.shape[1]; j++){
                    this->dvalues[i][j] = (2.0 / (elements)) * (y_pred[i][j] - y_true[i][j]);
                }
            }
            
            return this->dvalues;
        }




        // Just to keep this from being abstract/let managers easily switch from regression to classification without an object.
        NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 2>& actualMatrix) override{
            return 0.0;
        }

        NumType forwardClass(Array<NumType, 2>& outputMatrix, size_t samples, size_t output_neurons, Array<int, 1>& actualMatrix) override{
            return 0.0;
        }
                
        Array<NumType, 2> backwardClass(size_t output_neurons, Array<int, 1>& y_true, Array<NumType, 2>& softouts) override{
            return Array<NumType, 2>();
        }

};

#endif