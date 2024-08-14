class ActivationReLU
{
    private:
        float** saved_inputs;
    public:
        float** forward(float** inputs){
            int outMax = sizeof(inputs);
            if(outMax <= 0){
                return new float*[0];
            }
            saved_inputs = new float*[outMax];
            int inMax = sizeof(inputs[0]);
            for(int i = 0; i < outMax; i++){
                saved_inputs[i] = new float[inMax];
                for(int j = 0; j < inMax; j++){
                    saved_inputs[i][j] = inputs[i][j];
                    if(inputs[i][j] < 0){
                        inputs[i][j] = 0;
                    }
                }
            }
        }
        float** backward(){

        }
};