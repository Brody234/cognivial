#ifndef ARRAYHEAD
#define ARRAYHEAD

#include <cstddef>
#include <stdexcept>
#include <string>

/* 
 * This class handles n dimensional arrays where n>1. 
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

        // Boolean to track parent array to prevent use after free bugs.
        bool owns;

    public:
        // Shape of the array. First index is highest dimension.
        std::size_t* shape;
    // Essential functions for basic array functionality

        // Create an empty array object for class declarations
        Array();
        // For users to create a new array.
        Array(const std::size_t* s);

        // Frees memory.
        ~Array();

        /*
         * This constructor is not for public use.
         * It is public so that a 1D arrays can call it.
         * Usage of this constructor will in the best case fail to properly free memory when you are done. 
         * In the worst case it will allow exploit developers to attack the heap in your program. 
         * Don't use this, unless you know how to attack heap based exploit developement works.
         */
        Array(ArrType* d, std::size_t* _stride, std::size_t* _shape);

        /*
         * This constructor is not for public use.
         * It is public so that a 1D arrays can call it.
         * Usage of this constructor will in the best case fail to properly free memory when you are done. 
         * In the worst case it will allow exploit developers to attack the heap in your program. 
         * Don't use this, unless you know how to attack heap based exploit developement works.
         * Only difference is this allows you to set owns to true.
         */
        Array(ArrType* d, std::size_t* _stride, std::size_t* _shape, bool owns);


        // Overrides [] to access the next subarray, ex arr[1].
        Array<ArrType, dims-1> operator[](size_t idx) const;

        // Non const override.
        Array<ArrType, dims-1> operator[](size_t idx);

    // Non essential utility functions
        
        // Prints the array, recursively calls lower dimensions to make a good picture, tried to base on numpy.
        std::string toString() const;

        /* 
         * Preforms a transpose on a 2 dimensional array. 
         * O(1) time complexity.
         * Only increases memory by 1 pointer to data, and the two size_t arrays and their pointers.
         * Does not copy data, so editing on a transpose will edit the original array.
         * Simply a different way to view the same point in memory.
         * Use arr.copy().transpose() for a new array that is transposed.
         * Since it's O(1), copy(), transpose is not inefficient.
         */
        Array<ArrType, dims> transpose() const;

        /*
         * Copies the array into a new block of memory.
         * Because new memory is used, this is O(n) space.
         * WARNING: See the 1D array's copy function for full warning.
         * The full time complexity of this function is O(n*dims), to handle strides.
         */
        Array<ArrType, dims> copy();

        /*
         * WARNING DO NOT USE THIS UNLESS YOU ARE VERY CONFIDENT, THIS FUNCTION IS BASICALLY A BUG.
         * This function is a helper function for copy. It blindly copies from a total.
         * If an array was unchanged, meaning every stride[i] == shape[i+1] and stride[dims-1] = 1,
         * the array can be copied in O(n), not O(n*dims), where n is the number of elements. 
         * copy() will automatically check this and call copyTurbo directly, so there really isn't any reason for you to use it. 
         * But if you really want it, here it is. Don't blame me when it creates vulnerabilities in your code.
         */
        Array<ArrType, dims> copyTurbo(std::size_t total);
        /*
         * Scalar multiplication. 
         * Very simple concept, for each value in the array, multiply it by a scalar.
         * Return the larger array. 
         * O(n). Note that it will only affect the array, but if the array shares data with another array, it will effect it too. 
         * Ex: c = arr[1]. c*=4 scales the first row of arr. 
         * Note that if ArrType is non numerical, you'll get an error. 
         */
        void operator *=(ArrType num);

        /*
         * Same situation as copy but a little less dangerous. 
         * Basically, lets unchanged arrays go faster.
         * This is for me, not you, don't use it unless you're very confident.
         */
        void scalarMultTurbo(ArrType num, size_t total);

        /*
         * Scalar addition. 
         * Adds a scalar to every index of the array.
         */
        void operator +=(ArrType num);

        /*
         * Specialized helper function for faster computation. 
         * Be careful if you use it.
         */
        void scalarAddTurbo(ArrType num, size_t total);

        /*
         * Returns a new array that has zeros in all positions and the same shape.
         * O(n) space and time.
         */
        Array<ArrType, dims> zeros();

        /*
         * Dot Product
         */
        Array<ArrType, dims> operator*(const Array<ArrType, dims>& B) const;

        /*
         * Vector Dot Product
         * Returns a scalar, not a vector
         */
        Array<ArrType, dims> operator*(const Array<ArrType, 1>& vector) const;

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
        // Distance between datapoints, only used when this is a subarray.
        std::size_t stride;
        // Boolean to know if this should be freeing memory.
        bool owns;
    public:
        // Number of datapoints in this array/subarray.
        std::size_t len;
    // Essential to array functionality.
        // Create an empty array
        Array();

        // Creates the array using a 1D array.
        Array(const std::size_t* s);

        // Creates the array using a single value.
        Array(const std::size_t s);

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

        // Accesses a value at an index, nonconst.
        ArrType& operator[](std::size_t idx);

    // Non essential array utilities

        /*
         * Prints the array. 
         * If longer than six elements, 1-3, ... , -3 - -1.
         * Also called as a recursive base case for other print functions.
         */ 
        std::string toString() const;

        /*
         * Transpose for 1D array.
         * Returns a 2x2 array, with each value on its own row.
         * O(1) space and time, new array uses same data address. 
         * For a new array that's transposed, use arr.copy().transpose().
         * Since it's O(1), copy(), transpose is not inefficient.
         */ 
        Array<ArrType, 2> transpose() const;

        /*
         * Copies the array to give you a new array just like this one. 
         * WARNING: This is O(n), in both space and time and WILL create a new array.
         * Using this too often can slow down runtime and use more RAM on larger datasets. 
         * If your code runs too slowly and takes up a lot of RAM, try to work with less copies.
         * Because it is linear, and not exponential or polynomial, if Array's are most of your RAM, 
         * expect the number of copies to be linearly related to the RAM used. 
         * That means removing half your copy statements will make your code run twice as fast. 
         * On small datasets, knock yourself out I guess. 
         */
        Array<ArrType, 1> copy();

        /*
         * Scalar multiplies a 1D array by a scalar.
         * Basically multiplies each index by the scalar. 
         * Mathematically this is scaling a vector.
         */
        void operator*=(ArrType num);

        /*
         * Adds a scalar to every index of a 1D array.
         */
        void operator+=(ArrType num);

        /*
         * Returns a new array that has zeros in all positions and the same shape.
         * O(n) space and time.
         */
        Array<ArrType, 1> zeros();

        /*
         * Vector Dot Product
         * Returns a scalar, not a vector
         */
        ArrType operator*(const Array<ArrType, 1>& B) const;

};

// The file I actually implemented this stuff in.
#include "arraynd.tpp"
#include "array1d.tpp"
#endif
