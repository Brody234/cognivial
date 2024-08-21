#ifndef ACTIVATIONRELU_H
#define ACTIVATIONRELU_H

class ActivationReLU
{
    private:
        float** saved_inputs;
        int saved_samples;
        int saved_prev_layer;
        float minimum;
        float** dinputs = nullptr;
    public:
        ActivationReLU(){
            minimum = 0.0f;
        }
        ActivationReLU(float minimumVal){
            minimum = minimumVal;
        }
        float** forwardTest(float** inputs, int samples, int prev_layer){
            if(samples <= 0){
                return new float*[0];
            }
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            saved_inputs = new float*[samples];
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new float[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    if(inputs[i][j] < minimum){
                        saved_inputs[i][j] = minimum;
                    }
                }
            }
            //matrixViewer(saved_inputs, samples, prev_layer);
            return saved_inputs;
        }
        float** backward(float** dvalues){
            if(dinputs != nullptr){
                clearMatrix(dinputs, saved_samples);
                dinputs = nullptr;
            }
            dinputs = new float*[saved_samples];
            for(int i = 0; i < saved_samples; i++){
                dinputs[i] = new float[saved_prev_layer];
                for(int j = 0; j < saved_prev_layer; j++){
                    if(saved_inputs[i][j] <= 0){
                        dinputs[i][j] = 0;
                    }
                    else{
                        dinputs[i][j] = dvalues[i][j];
                    }
                }
            }
            return dinputs;
        }
};

#endif