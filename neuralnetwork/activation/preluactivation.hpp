#ifndef ACTIVATIONPRELU_H
#define ACTIVATIONPRELU_H

template <typename NumType = float>
class ActivationPReLU : public BaseActivation<NumType>
{
    private:
        int saved_samples;
        NumType minimum;
    public:
        NumType** saved_inputs;
        int saved_prev_layer;
        NumType* alpha;
        NumType alphaSingle;
        bool isArray;
        NumType dalphaSingle;
        NumType* dalpha;


        ActivationPReLU(NumType alphaVal, int prev_layerVal, bool alphaArray){
            minimum = 0.0f;
            if(alphaArray){
                alpha = new NumType[prev_layerVal];
                for(int i = 0; i < prev_layerVal; i++){
                    alpha[i] = alphaVal;
                }
            }
            else{
                alphaSingle = alphaVal;
            }
            isArray = alphaArray;
        }
        ActivationPReLU(NumType alphaVal, int prev_layerVal, bool alphaArray, NumType minimumVal){
            minimum = minimumVal;
            if(alphaArray){
                alpha = new NumType[prev_layerVal];
                for(int i = 0; i < prev_layerVal; i++){
                    alpha[i] = alphaVal;
                }
            }
            else{
                alphaSingle = alphaVal;
            }
        }
        NumType** forwardTest(NumType** inputs, int samples, int prev_layer) override{
            if(samples <= 0){
                return new NumType*[0];
            }
            saved_samples = samples;
            saved_prev_layer = prev_layer;
            saved_inputs = new NumType*[samples];
            this->outputs = new NumType*[samples];
            if(isArray){
                for(int i = 0; i < samples; i++){
                    this->outputs[i] = new NumType[prev_layer];
                    saved_inputs[i] = new NumType[prev_layer];
                    for(int j = 0; j < prev_layer; j++){
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
                    this->outputs[i] = new NumType[prev_layer];
                    saved_inputs[i] = new NumType[prev_layer];
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
        NumType** backward(NumType** dvalues) override{
            if(this->dinputs != nullptr){
                clearMatrix(this->dinputs, saved_samples);
                this->dinputs = nullptr;
            }
            this->dinputs = new NumType*[saved_samples];
            if(isArray){
                
                dalpha = new NumType[saved_prev_layer];
                for(int j = 0; j < saved_prev_layer; j++){
                    dalpha[j] = 0.0f;
                }

                for(int i = 0; i < saved_samples; i++){
                    this->dinputs[i] = new NumType[saved_prev_layer];
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
                    this->dinputs[i] = new NumType[saved_prev_layer];
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
};


#endif