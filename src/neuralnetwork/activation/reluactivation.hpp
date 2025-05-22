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
    public:
        ActivationReLU(){
            minimum = 0.0f;
        }
        ActivationReLU(NumType minimumVal){
            minimum = minimumVal;
        }
        Array<NumType, 2> forward(Array<NumType, 2> inputs, size_t samples, size_t prev_layer) override{
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
            //matrixViewer(saved_inputs, samples, prev_layer);
            return this->outputs;
        }
        Array<NumType, 2> backward(Array<NumType, 2> dvalues) override{
            /*if(this->dinputs != nullptr){
                clearMatrix(this->dinputs, saved_samples);
                this->dinputs = nullptr;
            }*/
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