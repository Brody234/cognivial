#ifndef ACTIVATIONLINEAR_H
#define ACTIVATIONLINEAR_H

template <typename NumType = float>
class ActivationLinear : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs = nullptr;
        int saved_samples;
        int saved_prev_layer;
        NumType m;
        NumType b;
    public: 
        ActivationLinear(){
            m = 1;
            b = 0;
        }
        ActivationLinear(NumType mVal){
            m = mVal;
            b = 0;
        }
        ActivationLinear(NumType mVal, NumType bVal){
            m = mVal;
            b = bVal;
        }
        NumType** forward(NumType** inputs, int samples, int prev_layer) override{
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_prev_layer = prev_layer;
            saved_samples = samples;
            saved_inputs = new NumType*[samples];
            this->outputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                saved_inputs[i] = new NumType[prev_layer];
                this->outputs[i] = new NumType[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    this->outputs[i][j] = (m*inputs[i][j])+b;
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
                    this->dinputs[i][j] = dvalues[i][j];
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " Linear " << std::endl;
        }

};

#endif