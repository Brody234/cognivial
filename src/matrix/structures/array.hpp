#ifndef ARRAYHEAD
#define ARRAYHEAD

#include <cstddef>
#include <stdexcept>
#include <string>

/* 
 * This class handles n dimensional arrays.
 * It is for multi dimensional arrays. 
 * Single dimensional arrays are defined below.
 * Subarray refers to an array at a lower level of this one.
 * For example, if arr is 2D, arr[1] is the second subarray.
 * ArrType is a type for the data stored in the array.
 * Arrays were only designed and tested for numerical types, use others at own risk. 
 * dims is the dimensions of the array.
 */
template <typename ArrType, std::size_t dims>
class Array {
    static_assert(dims >=2, "Use 1 dimensional array.");
    private:
        // Location of first index of first subarray.
        ArrType* data;
        // Distance between subarrays/length of subarrays, first index this level, following indices as follows.
        std::size_t* stride;
        // Shape of the array. First index is highest dimension.
        std::size_t* shape;
        // Boolean to track parent array to prevent use after free bugs.
        bool owns;

        // Private constructor for accessing subarrays.
        Array(ArrType* d, std::size_t* _stride, std::size_t* _shape)
        : data(d), owns(false)
        {
            shape = new std::size_t[dims];
            stride = new std::size_t[dims];
            for(std::size_t i = 0; i < dims; i++){
                shape[i] = _shape[i];
                stride[i] = _stride[i];
            }
        }

    public:
        // For users to create a new array.
        Array(const std::size_t* s);

        // Frees memory.
        ~Array();

        // Overrides [] to access the next subarray, ex arr[1].
        Array<ArrType, dims-1> operator[](size_t idx) const;

        // Prints the array, recursively calls lower dimensions to make a good picture, tried to base on numpy.
        std::string toString() const;

        // Non const override.
        Array<ArrType, dims-1> operator[](size_t idx);

        /* 
         * Preforms a transpose on a 2 dimensional array. 
         * O(1) time complexity.
         * Only increases memory by 1 pointer to data, and the two size_t arrays and their pointers.
         * Does not copy data, so editing on a transpose will edit the original array.
         * Simply a different way to view the same point in memory.
         */
        Array<ArrType, dims> transpose() const;
};

/*
 * This class is for 1 dimensional arrays.
 * For higher dimensional arrays, it is a recursive base case.
 * It is needed to access any scalar in a higher dimensional array.
 * So every time you write arr[1][1] on a 2d array, one of these is created and destroyed.
 * Internal usage as a basecase is O(1) time and space.
 * ArrType is the datatype used in the array.
 * What was dims is now forced to be a constant 1. 
 * Shape became len, as there is only 1 dimension. 
 * Similarly, stride is now a scalar.
 */
template <typename ArrType>
class Array<ArrType, 1> {
    private:
        // The first index of the data.
        ArrType* data;
        // Number of datapoints in this array/subarray.
        std::size_t len;
        // Distance between datapoints, only used when this is a subarray.
        std::size_t stride;
        // Boolean to know if this should be freeing memory.
        bool owns;
    public:
        // Creates the array.
        Array(const std::size_t* s);

        // Deletes the array from memory.
        ~Array();

        /*
         * Don't use this, it's for n dimensional arrays and only public for them.
         * Your array will NOT free properly.
         * If you set s to a non 1 value, you are setting yourself up for accessing memory you can't access.
         * Best case, that is a crash, worst case you put a vulnerability into your code.
         */ 
        Array(std::size_t l, std::size_t s, ArrType* d)
        : data(d), len(l), stride(s), owns(false)
        {}

        // Accesses a value at an index, const.
        const ArrType& operator[](size_t idx) const;

        /*
         * Prints the array. 
         * If longer than six elements, 1-3, ... , -3 - -1.
         * Also called as a recursive base case for other print functions.
         */ 
        std::string toString() const;

        // Accesses a value at an index, nonconst.
        ArrType& operator[](std::size_t idx);
};

// The file I actually implemented this stuff in.
#include "array.tpp"
#endif
