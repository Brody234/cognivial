#ifndef ACTIVATIONSTEP_H
#define ACTIVATIONSTEP_H

class ActivationStep
{
    private:
        float** saved_inputs = nullptr;
        float bar;
    public:
        ActivationStep(){
            bar = 0.0f;
        }
        ActivationStep(float barVal){
            bar = barVal;
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
                    if(inputs[i][j] <= bar){
                        inputs[i][j] = 0;
                    }
                    else{
                        inputs[i][j] = 1;
                    }
                }
            }
            return inputs;
        }
        void backward(){

        }
};

#endif