#ifndef LAYERHEAVY_H
#define LAYERHEAVY_H

class LayerHeavy
{
    private:
        double* biases;
        int weight_size;
    public:
        LayerHeavy(int this_layer, int next_layer, int prev_layer){
            biases = new double[this_layer];
            for(int i = 0; i < this_layer; i++){
                biases[i] = 0.0;
            }
        }
};

#endif