#include <vector>
#include <random>

class LayerLite
{
    private:
        float* biases;
        int bias_size;
        float** weights;
        int weight_size;
        int weight_inner_size;
        float** input_save;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> dis;

    public:
        LayerLite(int this_layer, int next_layer, int prev_layer)
        : 
        gen(rd()),
        dis(0.0f, 1.0f)
        {
            biases = new float[this_layer];
            bias_size = this_layer;
            weight_size = prev_layer;
            weights = new float*[prev_layer];
            for(int i = 0; i < this_layer; i++){
                biases[i] = 0.0f;
            }
            for(int i = 0; i < prev_layer; i++){
                weights[i] = new float[this_layer];
                for(int j = 0; j < this_layer; j++){
                    weights[i][j]= dis(gen);
                }
            }
        }
        float** forward(float** input){
            int max = sizeof(input);
            float** outputs = new float*[max];
            input_save = new float*[max];
            for(int k = 0; k < max; k++){
                outputs[k] = new float[bias_size];
                input_save[k] = new float[bias_size];
                for(int i = 0; i < bias_size; i++){
                    outputs[i] = 0;
                    for(int j = 0; j < weight_size; j++){
                        outputs[k][i] += input[k][j] * weights[j][i];
                        input_save[k][j] = input[k][j];
                    }
                    outputs[k][i] += biases[i];
                }
            }
            return outputs;
        }
        float** backward(float** dvalues){
            int max = sizeof(dvalues);
            
        }
};

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

int main(){

}