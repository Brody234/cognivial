#ifndef LOSSCCE_H
#define LOSSCCE_H
#include <random>
#include <iostream>
#include "../utilities/matrixutility.hpp"
#include "../utilities/vectorutility.hpp"
#include "../testdata/viewer.hpp"

class LossCCE
{
    private:
        float* vector;
    public:
        LossCCE(){

        }

        // Each Output Neuron Is A Class
        float forwardTest(float** outputMatrix, int samples, int output_neurons, int* actualMatrix){
            float** copiedMatrix = copyMatrix(outputMatrix, samples, output_neurons);
            matrixClip(copiedMatrix, samples, output_neurons, 1, 0);

            float* totals = new float[samples];
            // In this version, each actualMatrix value is the index of the neuron that is associated with the class.
            for(int i = 0; i < samples; i++){
                totals[i] = copiedMatrix[i][actualMatrix[i]];
            }


            vector = vectorLogNeg(totals, samples);

            float mean = vectorMean(totals, samples);
            
            delete[] totals;
            clearMatrix(copiedMatrix, samples);
            return mean;
        }
        
        // Each Output Neuron Identifies Classes
        float forwardTest(float** outputMatrix, int samples, int output_neurons, int** actualMatrix){
            float** copiedMatrix = copyMatrix(outputMatrix, samples, output_neurons);
            // For this overload 
            for(int i = 0; i < samples; i++){
                for(int j = 0; j < output_neurons; j++){
                    copiedMatrix[i][j] *=  actualMatrix[i][j];
                }
            }

            matrixClip(copiedMatrix, samples, output_neurons, 1, 0);

            vector = matrixLogNegVectorSum(copiedMatrix, samples, output_neurons);
            float mean = vectorMean(vector, samples);

            clearMatrix(copiedMatrix, samples);
            return mean;
        }
        float** backward(int samples, int output_neurons, int* y_true){
            float** dvalues = new float*[samples];
            for(int i = 0; i < samples; i++){
                dvalues[i] = new float[output_neurons];
                for(int j = 0; j < output_neurons; j++){
                    if(j == y_true[i]){
                        dvalues[i][j] = -1/vector[i]; // if you get a divide by 0 error just clip this. also i ignored derivative of the clip, probably shouldn't matter as it should very rarely mean anything and only do anything when the model is perfect or very bad. maybe im insane, at the time of this comment, not even sure what I'm doing with the output of this function.
                    }
                    else{
                        dvalues[i][j] = 0;
                    }
                }
            }
            return dvalues;
        }
};

#endif