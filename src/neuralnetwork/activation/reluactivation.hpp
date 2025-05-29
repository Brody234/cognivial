#ifndef ACTIVATIONRELU_H
#define ACTIVATIONRELU_H

template <typename NumType = float>
class ActivationReLU : public BaseActivation<NumType>
{
    private:
        Array<NumType, 2> saved_inputs;
        size_t saved_samples;
        size_t saved_prev_layer;
        NumType minimum;
        std::vector<Array<NumType, 1>*> inputsRL;
        std::vector<Array<NumType, 1>*> outputsRL;
    public:
        ActivationReLU(){
            minimum = 0.0f;
        }
        ActivationReLU(NumType minimumVal){
            minimum = minimumVal;
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
            for(size_t i = 0; i < samples; i++){
                for(size_t j = 0; j < prev_layer; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    if(inputs[i][j] < minimum){
                        this->outputs[i][j] = minimum;
                    }
                    else{
                        this->outputs[i][j] = inputs[i][j];
                    }
                }
            }
            return this->outputs;
        }

        Array<NumType, 1> forwardRL(Array<NumType, 1>& input) override{
            auto* saved = new Array<NumType, 1>(input.len);
            this->saved_prev_layer = input.len;
            auto* out = new Array<NumType, 1>(input.len);
            for (size_t i = 0; i < input.len; i++) {
                (*saved)[i] = input[i];
                (*out)[i] = input[i] < minimum ? minimum : input[i];
            }
            inputsRL.push_back(saved);
            outputsRL.push_back(out); 
            return (*out); 
        }

        void endEpisodeRL() override{
            size_t epSize = inputsRL.size();
            size_t inArr[2] = {epSize, this->saved_prev_layer};
            saved_inputs = Array<NumType, 2>(inArr);  
            size_t outArr[2] =  {epSize, this->saved_prev_layer};
            this->outputs = Array<NumType, 2>(outArr);

            for(int i = 0; i < saved_prev_layer; i++){
                for(int j = 0; j < epSize; j++){
                    saved_inputs[i][j] = (*inputsRL[i])[j];
                    this->outputs[i][j] = (*outputsRL[i])[j];
                }
                delete inputsRL[i];
                delete outputsRL[i];
            }
            inputsRL.clear();
            outputsRL.clear();
        }

        Array<NumType, 2> backward(Array<NumType, 2>& dvalues) override{

            size_t dinputsShape[2] = {saved_samples, saved_prev_layer};
            this->dinputs = Array<NumType, 2>(dinputsShape);

            
            for(size_t i = 0; i < saved_samples; i++){
                for(size_t j = 0; j < saved_prev_layer; j++){
                    if(saved_inputs[i][j] <= 0){
                        this->dinputs[i][j] = 0;
                    }
                    else{
                        this->dinputs[i][j] = dvalues[i][j];
                    }
                }
            }
            return this->dinputs;
        }
        void print() override{
            std::cout << " ReLU " << std::endl;
        }

};

#endif