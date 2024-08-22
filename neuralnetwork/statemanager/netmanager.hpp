#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <vector>

template <typename NumType = float>
class NetManager{
    private:
        std::vector<LayerLite<NumType>*> layers;
        std::vector<BaseActivation<NumType>*> activations;
        std::vector<ActivationPReLU<NumType>*> prelus;
        BaseLoss<NumType>* loss;
        BaseOptimizer<NumType>* optimizer;
        int input_size;
        int prev_layer_size;
    public:
        //Creates a new netmanager object
        NetManager(int input_size){
            this->input_size = input_size;
            prev_layer_size = input_size;
            loss = new LossCCE<NumType>();
            optimizer = new OptimizerSGD<NumType>(0.3f, false, 0.01f);
        }

        //Adds a layer of int size neurons to the end
        void addLayerToEnd(int size){
            LayerLite<NumType>* temp = new LayerLite<NumType>(prev_layer_size, size);
            layers.push_back(temp);
            ActivationLinear<NumType>* lin = new ActivationLinear<NumType>();
            activations.push_back(lin);
            prev_layer_size = size;
        }

    //Loss Section

        //Sets the managers loss function to be CCE
        void setLossCCE(){
            if(loss != nullptr){
                delete loss;
            }
            loss = new LossCCE<NumType>();
        }
    //Activation Section

        //PReLU Section
        
        //Sets the activation function after the most recently declared layer to be PReLU.
        void addPReLU(NumType alphaVal, bool alphaArray){
            addPReLUToIndex(-1, alphaVal, alphaArray);
        }

        //Sets the activation function after the most recently declared layer to be PReLU. Overload where minimumVal replaces 0 as the cutoff point.
        void addPReLU(NumType alphaVal, bool alphaArray, NumType minimumVal){
            addPReLUToIndex(-1, alphaVal, alphaArray, minimumVal);
        }

        //Sets the activation function of a layer at a certain index to be PReLU
        void addPReLUToIndex(int index, NumType alphaVal, bool alphaArray){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationPReLU<NumType>* prelu = new ActivationPReLU<NumType>(alphaVal, layers[index]->bias_size, alphaArray);
            activations[index] = prelu;
            prelus.push_back(prelu);
        }

        //Sets the activation function of a layer at a certain index to be PReLU. Overload where minimumVal replaces 0 as the cutoff point.
        void addPReLUToIndex(int index, NumType alphaVal, bool alphaArray, NumType minimumVal){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationPReLU<NumType>* prelu = new ActivationPReLU<NumType>(alphaVal, layers[index]->bias_size, alphaArray, minimumVal);
            activations[index] = prelu;
            prelus.push_back(prelu);
        }

        //Softmax Section
        
        void addSoftmax(){
            addSoftmaxToIndex(-1);
        }
        
        void addSoftmaxToIndex(int index){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            activations[index] = new ActivationSoftMax<NumType>();
        }


    //Passing Section

        void forwardPass(NumType** data, int samples){
            if(layers.size() > 0){
                layers[0]->forwardTest(data, samples);
                activations[0]->forwardTest(layers[0]->outputs, samples, layers[0]->bias_size);
            }
            for(int i = 1; i < layers.size(); i++){
                layers[i]->forwardTest(activations[i-1]->outputs, samples);
                activations[i]->forwardTest(layers[i]->outputs, samples, layers[i]->bias_size);
            }
        }
        void calculate(int samples, int* y_true){
            float mean = loss->forwardTest(activations[activations.size()-1]->outputs, samples, layers[layers.size()-1]->bias_size, y_true);
            std::cout << "Loss: " << mean << std::endl;
        }


        void forwardPassAndPrint(float** data, int samples){
            if(layers.size() > 0){
                layers[0]->forwardTest(data, samples);
                activations[0]->forwardTest(layers[0]->outputs, samples, layers[0]->bias_size);

            }
            for(int i = 1; i < layers.size(); i++){
                layers[i]->forwardTest(layers[i-1]->outputs, samples);
                activations[i]->forwardTest(layers[i]->outputs, samples, layers[i]->bias_size);
                std::cout << "Layer " << i << " outputs " << layers[i-1]->outputs[0][0] << " and post activation " << activations[i-1]->outputs[0][0] << std::endl;
                matrixViewer(layers[i]->outputs, 3, layers[i]->bias_size);
                matrixViewer(activations[i]->outputs, 3, layers[i]->bias_size);

            }
        }

        void backwardPass(int* y_true){
            if(layers.size() > 0){
                loss->backward(prev_layer_size, y_true, activations[activations.size()-1]->outputs);
                activations[activations.size()-1]->backward(loss->dvalues);
                layers[layers.size()-1]->backward(activations[activations.size()-1]->dinputs);
                
            }
            for(int i = layers.size()-2; i >= 0; i--){
                activations[i]->backward(layers[i+1]->dinputs);
                layers[i]->backward(activations[i]->dinputs);
            }
        }

        void optimize(){
            optimizer->preupdate();
            for(int i = 0; i < layers.size(); i++){
                optimizer->optimize_layer(layers[i]);
            }
            for(int i = 0; i < prelus.size(); i++){
                optimizer->optimize_prelu(prelus[i]);
            }
        }

        void train(NumType** data, int samples, int* y_true, int epochs){
            for(int i = 0; i < epochs; i++){
                forwardPass(data, samples);
                calculate(samples, y_true);
                backwardPass(y_true);
                optimize();
                float acc = accuracy(activations[activations.size()-1]->outputs, y_true, samples, prev_layer_size);
                std::cout << "Accuracy: " << acc << std::endl;
            }
        }

};

#endif