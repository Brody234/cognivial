#ifndef LINKEDMANAGER_H
#define LINKEDMANAGER_H

#include <vector>
#include "../layer/layerlite.hpp"
#include "../activation/baseactivation.hpp"
#include "../activation/preluactivation.hpp"
#include "../loss/baseloss.hpp"
#include "../optimizer/baseoptimizer.hpp"
#include "../activation/reluactivation.hpp"
#include "../activation/linearactivation.hpp"
#include "./linkedheaders/linkednode.hpp"

template <typename NumType = float>
class LinkedManager{
    private:
        std::vector<LinkedNode<NumType>*> chains;
        std::vector<ActivationPReLU<NumType>*> prelus;
        BaseLoss<NumType>* loss;
        BaseOptimizer<NumType>* optimizer;
        int input_size;
        int prev_layer_size;
        bool regress;
        int idMax = 0;
    public:
        //Creates a new netmanager object
        LinkedManager(int input_size){
            this->input_size = input_size;
            prev_layer_size = input_size;
            loss = new LossCCE<NumType>();
            regress = false;
            optimizer = new OptimizerSGD<NumType>(0.01f, false, 0.001f);
        }
        void outputArchitecture(){
            std::cout << "Size: " << chains.size() << std::endl;
            std::cout << "Chain 1" << chains[0]->getNext() <<std::endl;
        }
        void addLayer(int size){
            LayerLite<NumType>* temp = new LayerLite<NumType>(prev_layer_size, size, false);
            LinkedNode<NumType>* node = new LinkedNode<NumType>(temp, idMax);
            idMax++;
            chains.push_back(node);
        }
        //links 2 nodes, -1 if fail, 1 if success
        int linkNodes(int id1, int id2){
            LinkedNode<NumType>* node1 = nullptr;
            LinkedNode<NumType>* node2 = nullptr;
            int node2I = 0;
            for(int i = 0; i < chains.size(); i++){
                LinkedNode<NumType>* temp = chains[i];
                while(temp != nullptr){
                    if(temp->getId() == id1){
                        node1 = temp;
                    }
                    else if(temp->getId() == id2){
                        node2 = temp;
                        node2I = i;
                    }
                    temp = temp->getNext();
                }
            }
            if(node1 == nullptr || node2 == nullptr){
                return -1;
            }
            if(node1->getNext() != nullptr){
                chains.push_back(node1->getNext());
                node1->getNext()->clearPrevLayer();
            }
            if(node2->getPrev() != nullptr){
                node2->getPrev()->clearNextLayer();
            }
            chains.erase(chains.begin() + node2I);
            node1->addNextLayer(node2);
            return 1;
        }

        LinkedNode<NumType>* newActivation(){
            LinkedNode<NumType>* temp = new LinkedNode<NumType>(idMax);
            idMax++;
            chains.push_back(temp);
            return temp;
        }

        void addLinearActivation(NumType m, NumType b){
            newActivation()->addActivation(new ActivationLinear<NumType>(m, b));
        }

        void addReLUActivation(NumType minimum){
            newActivation()->addActivation(new ActivationReLU<NumType>());
        }

};

#endif