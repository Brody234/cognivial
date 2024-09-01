#ifndef LOSSMAE_H
#define LOSSMAE_H
#include <random>
#include <iostream>
#include <memory>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

template <typename NumType = float>
class LossMAE : public BaseLoss<NumType>
{
    private:
        int saved_samples;
        int saved_prev_layer;

    public:
        ~LossMAE() {
            
        }

        
        NumType forwardRegress(NumType** outputMatrix, int samples, int prev_layer, NumType** actualMatrix) override{
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            NumType sum = 0.0f;

            for(int i = 0; i < samples; i++){
                for(int j = 0; j < prev_layer; j++){
                    NumType dif = actualMatrix[i][j] - outputMatrix[i][j];
                    if(dif > 0){
                        sum += dif;
                    }
                    else{
                        sum -= dif;
                    }
                }
            }
            NumType mean = sum/(samples*prev_layer);

            return mean;
        }

        NumType** backwardRegress(NumType** y_pred, NumType** y_true) override{
            this->dvalues = new NumType*[saved_samples];

            for(int i = 0; i < saved_samples; i++){
                this->dvalues[i] = new NumType[saved_prev_layer];

                for(int j = 0; j < saved_prev_layer; j++){
                    NumType dif = y_pred[i][j] - y_true[i][j];
                    if(dif > 0){
                        this->dvalues[i][j] = 1;
                    }
                    if(dif < 0){
                        this->dvalues[i][j] = -1;
                    }
                    if(dif==0){
                        this->dvalues[i][j] = 0;
                    }

                }
            }
            
            return this->dvalues;
        }




        // Just to keep this from being abstract/let managers easily switch from regression to classification without an object.
        NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int** actualMatrix) override{
            return 0.0;
        }

        NumType forwardClass(NumType** outputMatrix, int samples, int output_neurons, int* actualMatrix) override{
            return 0.0;
        }
                
        NumType** backwardClass(int output_neurons, int* y_true, NumType** softouts) override{
            return new NumType*[0];
        }

};

#endif