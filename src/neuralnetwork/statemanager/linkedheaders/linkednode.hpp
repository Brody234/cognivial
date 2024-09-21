#ifndef LINKEDNODEMANAGER_H
#define LINKEDNODEMANAGER_H

#include <vector>
#include "../../layer/layerlite.hpp"
#include "../../activation/baseactivation.hpp"
#include "../../activation/linearactivation.hpp"

template <typename NumType = float>
class LinkedNode{
    private:
        bool isLayer;
        LayerLite<NumType>* layer;
        int prev_layer_neurons;
        int neurons;
        BaseActivation<NumType>* activation;
        LinkedNode<NumType>* nextLayer = nullptr;
        LinkedNode<NumType>* prevLayer = nullptr;
        int id;
    public:
        LinkedNode(LayerLite<NumType>* layerVal, int idVal){
            layer = layerVal;
            neurons = layer->getNeurons();
            prev_layer_neurons = layer->getPrevLayer();
            id = idVal;
            isLayer = true;
        }
        LinkedNode(BaseActivation<NumType>* activationVal, int idVal){
            activation = activationVal;
            id = idVal;
            isLayer = false;
        }
        LinkedNode(int idVal){
            activation = new ActivationLinear<NumType>();
            id = idVal;
            isLayer = false;
        }
        LayerLite<NumType>* getLayer(){
            return layer;
        }
        LinkedNode* getNext(){
            return nextLayer;
        }
        LinkedNode* getPrev(){
            return prevLayer;
        }
        void addNextLayer(LinkedNode* newLayer){
            nextLayer = newLayer;
        }
        void addPrevLayer(LinkedNode* newLayer){
            prevLayer = newLayer;
        }
        void clearNextLayer(){
            if(nextLayer != nullptr){
                nextLayer = nullptr;
            }
        }
        void clearPrevLayer(){
            if(prevLayer != nullptr){
                prevLayer = nullptr;
            }
        }
        bool checkLayer(){
            return isLayer;
        }
        int print(){
            std::cout << "ID Number: " << id << " ";
            if(isLayer){
                layer->print();
            }
            else{
                activation->print();
            }
            return 1;
        }
        int getId(){
            return id;
        }
        NumType** layerForward(NumType** input, int samples){
            if(layer != nullptr){
                return layer->forwardTest(input, samples);
            }
            else{
                return new NumType*[0];
            }
        }
        NumType** activationForward(NumType** inputs, int samples, int prev_layer){
            if(activation != nullptr){
                return activation->forwardTest(inputs, samples, prev_layer);
            }
            else{
                return new NumType*[0];
            }

        }
        NumType** forward(NumType** input, int samples, int prev_layer){
            if(isLayer && layer != nullptr){
                return layer->forwardTest(input, samples);
            }
            else if(!isLayer && activation != nullptr){
                //std::cout << "PREV LAYER" << prev_layer<< std::endl;
                return activation->forwardTest(input, samples, prev_layer);
            }
            else{
                return new NumType*[0];
            }
        }
        NumType** layerBackward(NumType** dvalues){
            if(layer != nullptr){
                return layer->backward(dvalues);
            }
            else{
                return new NumType*[0];
            }
        }
        NumType** activationBackward(NumType** dvalues){
            if(activation != nullptr){
                return activation->backward(dvalues);
            }
            else{
                return new NumType*[0];
            }
        }
        NumType** backward(NumType** dvalues){
            if(isLayer && layer != nullptr){
                return layer->backward(dvalues);
            }
            else if(!isLayer && activation!= nullptr){
                return activation->backward(dvalues);
            }
            else{
                return new NumType*[0];
            }
        }
        void clearLayer(){
            if(layer!= nullptr){
                delete layer;
                layer = nullptr;
            }
        }
        void clearActivation(){
            if(activation!= nullptr){
                delete activation;
                activation = nullptr;
            }
        }
        void addLayer(LayerLite<NumType>* layerVal){
            if(layer != nullptr){
                delete layer;
            }
            layer = layerVal;
        }
        void addActivation(BaseActivation<NumType>* actVal){
            if(activation!= nullptr){
                delete activation;
            }
            activation = actVal;
        }
        void resizeLayer(int prev_layer_size, int layer_size){
            if(!isLayer){
                neurons = prev_layer_size;
            }
            else if(prev_layer_size == prev_layer_neurons && layer_size == neurons){
                return;
            }
            else{
                LayerLite<NumType>* temp = new LayerLite<NumType>(prev_layer_size, layer_size, false);
                delete layer;
                layer = temp;
            }
        }
        int getNeurons(){
            if(isLayer){
                return neurons;
            }
            else if(prevLayer != nullptr){
                return prevLayer->getNeurons();
            }
            else{
                return -1;
            }
        }
        int prevNeurons(){
            if(isLayer){
                return prev_layer_neurons;
            }
            else{
                LinkedNode<NumType>* temp = prevLayer;
                while(temp != nullptr){
                    if(temp->checkLayer()){
                        return neurons;
                    }
                    temp = temp->getPrev();
                }
            }
            return -1;
        }
};

#endif