#ifndef ACTIVATIONLEAKYRELU_H
#define ACTIVATIONLEAKYRELU_H

template <typename NumType = float>
class ActivationLeakyReLU : public BaseActivation<NumType>
{
    private:
        NumType** saved_inputs;
        int saved_samples;
        int saved_prev_layer;
        NumType minimum;
        NumType alpha;
    public:
        ActivationLeakyReLU(NumType alphaVal){
            minimum = 0.0f;
            alpha = alphaVal;
        }
        ActivationLeakyReLU(NumType alphaVal, NumType minimumVal){
            minimum = minimumVal;
            alpha = alphaVal;
        }
        NumType** forwardTest(NumType** inputs, int samples, int prev_layer) override{
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            saved_inputs = new NumType*[samples];
            this->outputs = new NumType*[samples];
            for(int i = 0; i < samples; i++){
                this->outputs[i] = new NumType[prev_layer];
                saved_inputs[i] = new NumType[prev_layer];
                for(int j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    if(inputs[i][j] < minimum){
                        this->outputs[i][j] = inputs[i][j]*alpha;
                    }
                    else{
                        this->outputs[i][j] = inputs[i][j];
                    }
                }
            }
            //matrixViewer(saved_inputs, samples, prev_layer);
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
                    if(saved_inputs[i][j] <= 0){
                        this->dinputs[i][j] = dvalues[i][j]*alpha;
                    }
                    else{
                        this->dinputs[i][j] = dvalues[i][j];
                    }
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " Leaky ReLU " << std::endl;
        }
};

#endif