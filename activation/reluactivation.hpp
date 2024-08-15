#ifndef ACTIVATIONRELU_H
#define ACTIVATIONRELU_H

class ActivationReLU
{
    private:
        float** saved_inputs = nullptr;
        float minimum;
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
            saved_inputs = new float*[samples];
            int inMax = sizeof(inputs[0]);
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new float[inMax];
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    if(inputs[i][j] < minimum){
                        inputs[i][j] = minimum;
                    }
                }
            }
            return inputs;
        }
        void backward(){

        }
};

#endif