#ifndef TWOD
#define TWOD

template <typename ArrType = float>
class Array {
    private:
        ArrType* data;
        int dims;
        int* shape;
    public:
        Array(int n){
            data = new ArrType[n];
            dims = 1;
            shape = new int[1];
            shape[0] = n;
        }
        Array(int n, int m){

        }
        Array(int n, int m, int p){

        }
        Array(int n, int m, int p, int q){

        }
        ~Array(){
            delete[] data;
            delete[] shape;
        }
        auto& operator[](int pos){
            return data[pos];
        }
        const ArrType& operator[](int pos) const {
            return data[pos];
        }
};

#endif