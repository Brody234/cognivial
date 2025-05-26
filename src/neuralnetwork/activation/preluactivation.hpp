#ifndef ACTIVATIONPRELU_H
#define ACTIVATIONPRELU_H

template <typename NumType = float>
class ActivationPReLU : public BaseActivation<NumType>
{
    private:
        size_t saved_samples;
        NumType minimum;
    public:
        Array<NumType, 2> saved_inputs;
        size_t saved_prev_layer;
        Array<NumType, 1> alpha;
        NumType alphaSingle;
        bool isArray;
        NumType dalphaSingle;
        Array<NumType, 1> dalpha;


        ActivationPReLU(NumType alphaVal, size_t prev_layerVal, bool alphaArray){
            minimum = 0.0f;
            if(alphaArray){
                alpha = Array<NumType, 1>(prev_layerVal);
                for(size_t i = 0; i < prev_layerVal; i++){
                    alpha[i] = alphaVal;
                }
            }
            else{
                alphaSingle = alphaVal;
            }
            isArray = alphaArray;
        }
        ActivationPReLU(NumType alphaVal, size_t prev_layerVal, bool alphaArray, NumType minimumVal){
            minimum = minimumVal;
            if(alphaArray){
                alpha = Array<NumType, 1>(prev_layerVal);
                for(int i = 0; i < prev_layerVal; i++){
                    alpha[i] = alphaVal;
                }
            }
            else{
                alphaSingle = alphaVal;
            }
        }
        Array<NumType, 2> forward(Array<NumType, 2>& inputs, size_t samples, size_t prev_layer) override{
            if(samples <= 0){
                return Array<NumType, 2>();
            }
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            size_t shape[2] = {samples, prev_layer};
            saved_inputs = Array<NumType, 2>(shape);
            this->outputs = Array<NumType, 2>(shape);
            if(isArray){
                for(size_t i = 0; i < samples; i++){
                    for(size_t j = 0; j < prev_layer; j++){
                        saved_inputs[i][j] = inputs[i][j];
                        if(inputs[i][j] < minimum){
                            this->outputs[i][j] = inputs[i][j]*alpha[j];
                        }
                        else{
                            this->outputs[i][j] = inputs[i][j];
                        }
                    }
                }
            }
            else{
                for(int i = 0; i < samples; i++){
                    for(int j = 0; j < prev_layer; j++){
                        saved_inputs[i][j] = inputs[i][j];
                        if(inputs[i][j] < minimum){
                            this->outputs[i][j] = inputs[i][j]*alphaSingle;
                        }
                        else{
                            this->outputs[i][j] = inputs[i][j];
                        }
                    }
                }

            }
                //matrixViewer(saved_inputs, samples, prev_layer);
            return this->outputs;
        }
        Array<NumType, 2> backward(Array<NumType, 2>& dvalues) override{
            if(this->dinputs != nullptr){
                clearMatrix(this->dinputs, saved_samples);
                this->dinputs = nullptr;
            }
            size_t shape[2] = {saved_samples, saved_prev_layer};
            this->dinputs = Array<NumType, 2>(shape);
            if(isArray){
                
                dalpha = Array<NumType, 1>(saved_prev_layer);
                for(int j = 0; j < saved_prev_layer; j++){
                    dalpha[j] = 0.0f;
                }

                for(int i = 0; i < saved_samples; i++){
                    for(int j = 0; j < saved_prev_layer; j++){
                        if(saved_inputs[i][j] <= 0){
                            this->dinputs[i][j] = dvalues[i][j]*alpha[j];
                            dalpha[j] += dvalues[i][j]*saved_inputs[i][j];
                        }
                        else{
                            this->dinputs[i][j] = dvalues[i][j];
                        }
                    }
                }
            }
            else{
                dalphaSingle = 0.0f;
                for(int i = 0; i < saved_samples; i++){
                    for(int j = 0; j < saved_prev_layer; j++){
                        if(saved_inputs[i][j] < 0){
                            this->dinputs[i][j] = dvalues[i][j]*alphaSingle;
                            dalphaSingle += dvalues[i][j]*saved_inputs[i][j];
                        }
                        else{
                            this->dinputs[i][j] = dvalues[i][j];
                        }
                    }
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " PReLU" << std::endl;
        }
};


#endif