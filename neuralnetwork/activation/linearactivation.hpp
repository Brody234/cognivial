#ifndef ACTIVATIONLINEAR_H
#define ACTIVATIONLINEAR_H

class ActivationLinear
{
    private:
        float** saved_inputs = nullptr;
        float m;
        float b;
    public:
        ActivationLinear(){
            m = 1;
            b = 0;
        }
        ActivationLinear(float mVal){
            m = mVal;
            b = 0;
        }
        ActivationLinear(float mVal, float bVal){
            m = mVal;
            b = bVal;
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
                    inputs[i][j] = (m*inputs[i][j])+b;
                }
            }
            return inputs;
        }
        void backward(){

        }
};

#endif