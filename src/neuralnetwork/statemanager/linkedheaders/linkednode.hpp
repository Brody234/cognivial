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
        BaseActivation<NumType>* activation;
        LinkedNode<NumType>* nextLayer = nullptr;
        LinkedNode<NumType>* prevLayer = nullptr;
        int id;
    public:
        LinkedNode(LayerLite<NumType>* layerVal, int idVal){
            layer = layerVal;
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
        LinkedNode* getNext(){
            return nextLayer;
        }
        LinkedNode* getPrev(){
            return nextLayer;
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
};

#endif