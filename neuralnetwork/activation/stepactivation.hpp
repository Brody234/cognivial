#ifndef ACTIVATIONSTEP_H
#define ACTIVATIONSTEP_H

template <typename NumType = float>
class ActivationStep : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs = nullptr;
        NumType bar;
    public:
        ActivationStep(){
            bar = 0.0f;
        }
        ActivationStep(NumType barVal) override{
            bar = barVal;
        }
        NumType** forwardTest(NumType** inputs, int samples, int prev_layer){
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_inputs = new NumType*[samples];
            int inMax = sizeof(inputs[0]);
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new NumType[inMax];
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
        void backward() override{

        }
};

#endif