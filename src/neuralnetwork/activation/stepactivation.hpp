#ifndef ACTIVATIONSTEP_H
#define ACTIVATIONSTEP_H

template <typename NumType = float>
class ActivationStep : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs = nullptr;
        NumType bar;
        int saved_samples;
        int saved_prev_layer;
        NumType min;
        NumType max;
    public:
        ActivationStep(){
            bar = 0.0f;
            min = 0.0f;
            max = 1.0f;
        }
        ActivationStep(NumType barVal){
            bar = barVal;
            min = 0.0f;
            max = 1.0f;
        }
        ActivationStep(NumType barVal, NumType minVal, NumType maxVal){
            min = minVal;
            max = maxVal;
            bar = barVal;
        }

        NumType** forward(NumType** inputs, int samples, int prev_layer) override{
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            if(samples <= 0){
                return new NumType*[0];
            }
            this->outputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                this->outputs[i] = new NumType[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    if(inputs[i][j] <= bar){
                        this->outputs[i][j] = min;
                    }
                    else{
                        this->outputs[i][j] = max;
                    }
                }
            }
            return this->outputs;
        }
        NumType** backward(NumType** dvalues) override{
            if(this->dinputs != nullptr){
                clearMatrix(this->dinputs, saved_samples);
                this->dinputs = nullptr;
            }

            this->dinputs = new NumType*[saved_samples];

            for(int i = 0; i < saved_samples; i++){
                this->dinputs[i] = new NumType[saved_prev_layer];
                for(int j = 0; j < saved_prev_layer; j++){
                    this->dinputs[i][j] = 0;
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " Step " << std::endl;
        }
};

#endif