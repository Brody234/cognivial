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
        bool regress;

    public:
        //Creates a new netmanager object
        NetManager(int input_size){
            this->input_size = input_size;
            prev_layer_size = input_size;
            loss = new LossCCE<NumType>();
            regress = false;
            optimizer = new OptimizerSGD<NumType>(0.01f, false, 0.001f);
        }

        NetManager(const std::string style, int input_size){
            this->input_size = input_size;
            prev_layer_size = input_size;
            if(style == "Classication"){
                loss = new LossCCE<NumType>();
                regress = false;
                optimizer = new OptimizerSGD<NumType>(0.01f, false, 0.001f);
            }
            else if(style == "Regression"){
                loss = new LossMSE<NumType>();
                regress = true;
                optimizer = new OptimizerSGD<NumType>(0.01f, false, 0.001f);
            }
            else if(style == "Small Classification"){
                addLayerToEnd(4);
                addLeakyReLU(.01);
                addLayerToEnd(1);
                addSoftmax();
                loss = new LossCCE<NumType>();
                regress = false;
                optimizer = new OptimizerSGD<NumType>(0.03f, false, 0.001f);
            }
        }


        //Adds a layer of int size neurons to the end
        void addLayerToEnd(int size){
            LayerLite<NumType>* temp = new LayerLite<NumType>(prev_layer_size, size, false);
            layers.push_back(temp);
            ActivationLinear<NumType>* lin = new ActivationLinear<NumType>();
            activations.push_back(lin);
            prev_layer_size = size;
        }

    //Loss Section

        // Sets the managers loss function to be CCE and enables classification methods. This will also disable regression.
        void setLossCCE(){
            if(loss != nullptr){
                delete loss;
            }
            loss = new LossCCE<NumType>();
            regress = false;
        }

        // Sets the managers loss function to be MSE and enables regression methods. This will also disable classification.
        void setLossMSE(){
            if(loss != nullptr){
                delete loss;
            }
            loss = new LossMSE<NumType>();
            regress = true;
        }

        // Sets the managers loss function to be MAE and enables regression methods. This will also disable classification.
        void setLossMAE(){
            if(loss != nullptr){
                delete loss;
            }
            loss = new LossMSE<NumType>();
            regress = true;
        }


    //Activation Section

        //Activation Utility

        // Removes activation functions from an index.
        void clearIndex(int index){
            if (index >= 0 && index < activations.size()) {
                BaseActivation<NumType>* toDelete = activations[index];
                delete toDelete;
                activations[index] = nullptr;

                for (auto it = prelus.begin(); it != prelus.end(); ++it) {
                    if (*it == toDelete) {
                        prelus.erase(it);
                        break;
                    }
                }
            }
        }

        //Linear Section

        // Creates a default linear activation function.
        void addLinear(){
            addLinearToIndex(-1);
        }

        // Creates a linear activation function along y = mx+b.
        void addLinear(NumType m, NumType b){
            addLinearToIndex(-1, m, b);
        }

        // Creates a linear activation function with default settings at an index.
        void addLinearToIndex(int index){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationLinear<NumType>* lin = new ActivationLinear<NumType>();
            clearIndex(index);
            activations[index] = lin;
        }

        // Creates a linear activation function along y = mx+b at an index.
        void addLinearToIndex(int index, NumType m, NumType b){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationLinear<NumType>* lin = new ActivationLinear<NumType>(m, b);
            clearIndex(index);
            activations[index] = lin;
        }

        //ReLU Section

        // Adds an ReLU activation function to the last layer, y = max(x, minimum).
        void addReLU(){
            addReLUToIndex(-1);
        }

        // Adds a ReLU activation function to the last layer, where minimum replaces zero for y = max(x, minimum).
        void addReLU(NumType minimum){
            addReLUToIndex(-1, minimum);
        }

        // Adds a ReLU activation function to an index, y = max(x, minimum).
        void addReLUToIndex(int index){
            if(index < 0 || index > activations.size()){
                ActivationReLU<NumType>* relu = new ActivationReLU<NumType>();
                activations.push_back(relu);
                return;
            }
            ActivationReLU<NumType>* relu = new ActivationReLU<NumType>();
            clearIndex(index);
            activations[index] = relu;
        }

        // Adds a ReLU activation function to an index, where minimum replaces zero for y = max(x, minimum).
        void addReLUToIndex(int index, NumType minimum){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationReLU<NumType>* relu = new ActivationReLU<NumType>(minimum);
            clearIndex(index);
            activations[index] = relu;
        }

        //LeakyReLU Section

        // Adds a leaky ReLU max(x, x*alpha) to the last layer.
        void addLeakyReLU(NumType alpha){
            addLeakyReLUToIndex(-1, alpha);
        }

        // Adds a leaky ReLU max(minimum, x*alpha) if minimum return x to the last layer.
        void addLeakyReLU(NumType alpha, NumType minimum){
            addLeakyReLUToIndex(-1, alpha, minimum);
        }

        // Adds a leaky ReLU max(x, x*alpha) to the last layer to an index.
        void addLeakyReLUToIndex(int index, NumType alpha){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationLeakyReLU<NumType>* relu = new ActivationLeakyReLU<NumType>(alpha);
            clearIndex(index);
            activations[index] = relu;
        }

        // Adds a leaky ReLU max(minimum, x*alpha) if minimum -> x to an index.
        void addLeakyReLUToIndex(int index, NumType alpha, NumType minimum){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationLeakyReLU<NumType>* relu = new ActivationLeakyReLU<NumType>(alpha, minimum);
            clearIndex(index);
            activations[index] = relu;
        }


        //PReLU Section
        
        //Sets the activation function after the most recently declared layer to be PReLU.
        void addPReLU(NumType alpha, bool alphaArray){
            addPReLUToIndex(-1, alpha, alphaArray);
        }

        //Sets the activation function after the most recently declared layer to be PReLU. Overload where minimum replaces 0 as the cutoff point.
        void addPReLU(NumType alpha, bool alphaArray, NumType minimum){
            addPReLUToIndex(-1, alpha, alphaArray, minimum);
        }

        //Sets the activation function of a layer at a certain index to be PReLU
        void addPReLUToIndex(int index, NumType alpha, bool alphaArray){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationPReLU<NumType>* prelu = new ActivationPReLU<NumType>(alpha, layers[index]->bias_size, alphaArray);
            clearIndex(index);
            activations[index] = prelu;
            prelus.push_back(prelu);
        }

        //Sets the activation function of a layer at a certain index to be PReLU. Overload where minimum replaces 0 as the cutoff point.
        void addPReLUToIndex(int index, NumType alpha, bool alphaArray, NumType minimum){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationPReLU<NumType>* prelu = new ActivationPReLU<NumType>(alpha, layers[index]->bias_size, alphaArray, minimum);
            clearIndex(index);
            activations[index] = prelu;
            prelus.push_back(prelu);
        }

        //Step Section

        // Adds a step to the last index.
        void addStep(){
            addStepToIndex(-1);
        }

        void addStep(NumType min, NumType max, NumType bar){
            addStepToIndex(-1, min, max, bar);
        }

        // Adds a step to an index.
        void addStepToIndex(int index){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationStep<NumType>* step = new ActivationStep<NumType>();
            clearIndex(index);
            activations[index] = step;
        }
        
        void addStepToIndex(int index, NumType min, NumType max, NumType bar){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationStep<NumType>* step = new ActivationStep<NumType>(bar, min, max);
            clearIndex(index);
            activations[index] = step;
        }

        //Sigmoid Section

        // 
        void addSigmoid(){
            addSigmoidToIndex(-1);
        }

        void addSigmoidToIndex(int index){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            ActivationSigmoid<NumType>* sig = new ActivationSigmoid<NumType>();
            clearIndex(index);
            activations[index] = sig;
        }

        //Softmax Section
        
        // Adds a softmax activation to the most recent layer.
        void addSoftmax(){
            addSoftmaxToIndex(-1);
        }
        
        // Adds a softmax activation to the specified index.
        void addSoftmaxToIndex(int index){
            if(index < 0 || index > activations.size()){
                index = activations.size()-1;
            }
            clearIndex(index);
            activations[index] = new ActivationSoftMax<NumType>();
        }

    //Optimizer Section

        //SGD Optimizer
        
        // Creates an SGD optimizer with special learning rate.
        void setOptimizerSGD(NumType learning_rate){
            setOptimizerSGD(learning_rate, 0.0);
        }

        // Creates an SGD optimizer with special learning rate and a decay rate.
        void setOptimizerSGD(NumType learning_rate, NumType decay_rate){
            OptimizerSGD<NumType> sgd = OptimizerSGD<NumType>(learning_rate, false, decay_rate);
            delete optimizer;
            optimizer = sgd;
        }

    // Performance Section

        //General Passing

        // Performs one iteration of the forward pass.
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


        // Performs one round of an optimizer updating ALL parameters.
        void optimize(){
            optimizer->preupdate();
            for(int i = 0; i < layers.size(); i++){
                optimizer->optimize_layer(layers[i]);
            }
            for(int i = 0; i < prelus.size(); i++){
                optimizer->optimize_prelu(prelus[i]);
            }
        }

        //Classification

        // Calculates loss at the end of the forward pass.
        void calculateClassification(int samples, int* y_true){
            float mean = loss->forwardClass(activations[activations.size()-1]->outputs, samples, layers[layers.size()-1]->bias_size, y_true);
            std::cout << "Loss: " << mean << std::endl;
        }

        // Performs one iteration of the backward pass for a classification based network where y_true is an int* array.
        void backwardPassClass(int* y_true){
            if(layers.size() > 0){
                loss->backwardClass(prev_layer_size, y_true, activations[activations.size()-1]->outputs);
                activations[activations.size()-1]->backward(loss->dvalues);
                layers[layers.size()-1]->backward(activations[activations.size()-1]->dinputs);
                
            }
            for(int i = layers.size()-2; i >= 0; i--){
                activations[i]->backward(layers[i+1]->dinputs);
                layers[i]->backward(activations[i]->dinputs);
            }
        }

        // Trains the classification model to y_true for epochs iterations.
        void trainClassification(NumType** data, int samples, int* y_true, int epochs){
            if(regress){
                return;
            }
            for(int i = 0; i < epochs; i++){
                forwardPass(data, samples);
                calculateClassification(samples, y_true);
                backwardPassClass(y_true);
                optimize();
                float acc = accuracy(activations[activations.size()-1]->outputs, y_true, samples, prev_layer_size);
                std::cout << "Accuracy: " << acc << std::endl;
            }
        }

        //Regression

        // Calculates loss at the end of the forward pass.
        void calculateRegression(int samples, NumType** y_true){
            float mean = loss->forwardRegress(activations[activations.size()-1]->outputs, samples, layers[layers.size()-1]->bias_size, y_true);
            std::cout << "Loss: " << mean << std::endl;
        }

        // Performs one backward pass for a 
        void backwardPassRegress(NumType** y_true){
            if(layers.size() > 0){
                loss->backwardRegress(activations[activations.size()-1]->outputs, y_true);
                activations[activations.size()-1]->backward(loss->dvalues);
                layers[layers.size()-1]->backward(activations[activations.size()-1]->dinputs);
                
            }
            for(int i = layers.size()-2; i >= 0; i--){
                activations[i]->backward(layers[i+1]->dinputs);
                layers[i]->backward(activations[i]->dinputs);
            }
        }

        // Trains the regression model to y_true for epochs iterations.
        void trainRegression(NumType** data, int samples, NumType** y_true, int epochs){
            if(!regress){
                return;
            }
            for(int i = 0; i < epochs; i++){
                forwardPass(data, samples);
                calculateRegression(samples, y_true);
                backwardPassRegress(y_true);
                optimize();
                NumType acc = accuracyNp(activations[activations.size()-1]->outputs, y_true, samples, prev_layer_size, 0.5);
                std::cout << "Accuracy: " << acc << std::endl;
            }
        }
};

#endif