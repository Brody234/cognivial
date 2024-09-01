# Neural Network Library
Hi! My name is Brody and welcome to my C++ Neural Network library. Here's some documentation.

## /utility
Starting with the least Neural Network/AI related directory and working up to the more complicated functions, let's get into our utility functions. These are basically just useful things that will come up when dealing with the objects and data types that come up a lot in AI. Basically, if I didn't want to worry about coding it twice or thought someone would like it, it's here.

### matrixutility.hpp
The most obvious type of utility for Neural Network work is that which deals with 2D arrays. Matrix Utility is exactly that. They are not necessarily linear algebra functions, but just general things that are easier to make functions than have as repeating code.

#### void clearMatrix(float** matrix, int row)
Here's a clearMatrix function, which simply takes any float** and the number of rows it has and frees up all that sweet memory. Don't be shy when using it.

#### float** copyMatrix(float** matrix, int row, int col)
Training neural networks uses a lot of ram and a lot of CPU space. One way to run out of ram quickly is by continuously making new arrays, especially if you forget to clear one. copyMatrix makes this much simpler, by copying the matrix, so that the majority of the functions in this file can edit the matrix it is inputted directly, rather than saving 10 matrices per epoch.

## /testdata
This is a folder devoted to giving you deterministic samples to practice models on, randomized training data and other functions that can be used when training a model.

### viewer.hpp
This file is devoted to functions that allow you to visualize your data.

#### void matrixViewer(float** matrix, int row, int col)
matrixViewer is a function that outputs a 2D array to the terminal in the form 
[
    [ val val val val ]
    [ val val val val ]
    [ val val val val ]
]
matrix is the float** that is printed, row is the number of rows, col is the number of columns.

### generatenumbers.hpp
This file is devoted to making matrices of numbers for you to play with and test your networks on. Obviously the main usecase of random filler data is learning the library. The functions in this file cannot be used to train a model, and are mainly for making sure you're shapes are correct and you know how to pass data. It can also be used to test various activation functions, and individual layers.

#### float** createDeterministicFloat4x4()
This function returns a deterministic 4x4 matrix of floats. They are not classed, nor do they have any relation. They are between -1 and 1. Below is the exact matrix this returns.
[
[  -0.9  -0.5  0  0.2  ]
[  0.4  -0.3  0.7  -0.8  ]
[  0.6  -0.1  -0.7  0.9  ]
[  -0.2  0.8  -0.4  0.1  ]
]

#### float** createDeterministicFloat3x4()
This function returns a deterministic 3x4 matrix of floats. They are not classed, nor do they have any relation. They are between -1 and 1. It is the same matrix as the 4x4 function, but without the last row.

#### float** createDeterministicFloat4x3()
This function returns a deterministic 4x3 matrix of floats. They are not classed, nor do they have any relation. They are between -1 and 1. It is the same matrix as the 4x4 function, but without the last column.

## /activation
This folder holds classes for different activation functions. Each activation function gets its own class and file.

### reluactivation.hpp
This file is for the reluactivation class, ActivationReLU, and only said class. The following are it's methods. I have chosen to make this class a modified version of the standard relu. Most ReLU functions work by taking the maximum of the a given value and 0 and replacing that value with with the outcome, so x = max(0, x). But in this case, this function uses x = max(minimum, x). By default minimum is 0, and I recommend that you don't change it, because why would you. But you can.

#### float** forwardTest(float** inputs, int samples, int prev_layer)
ActivationReLU.forwardTest is a function that takes the number of samples in the training or test data as samples, the number of neurons in the layer it is acting as the activation function for and the inputs matrix, which would be the output of the last layer, and the input of the current layer. The output is a matrix of the same shape as inputs. The output has the same address as the inputs and overwrites said array for the sake of space. It also returns said array.

### softmaxactivation.hpp
The SoftMax activation class, ActivationSoftMax, is a class devoted to the softmax activation function, where values are exponentiated, then normalized to 0-1.

#### float** forwardTest(float** inputs, int samples, int prev_layer)
ActivationSoftMax.forwardTest() takes a matrix inputs, the number of samples in the data set and the number of neurons in the layer it is the activation function for. It then runs the SoftMax algorithmn on these values.

### stepactivation.hpp
The Step activation class, ActivationStep, is a class devoted to the step activation function, where values are set to either 0 or 1, no in between. There are again 2 constructors for a parameter bar. If no parameter is passed, it defaults to 0. If a parameter is passed, that will be the bar.

#### float** forwardTest(float** inputs, int samples, int prev_layer)
ActivationSoftMax.forwardTest() takes a matrix inputs, the number of samples in the data set and the number of neurons in the layer it is the activation function for. If any given value in the matrix is less than or equal to the bar, it becomes 0. Any other value becomes 1.

### sigmoidactivation.hpp
This is the file dedicated to the sigmoid activation function.


## /layer
This folder holds layer files.

### layerlite.hpp
This file contains the LayerLite class, a layer of neurons whose inputs, weights and biases are all floats.

#### constructor(int prev_layer, int this_layer)
There is only one constructor, it requires the size of the previous layer, and the size of the current layer. Do NOT use the same layer object for different layers in your network even if the constructor would be same.

#### float** forwardTest(float** input, int samples)
This is the forward pass, it does a dot product of the input and the weights and adjusts to the biases. Samples is the number of samples in the dataset. It is not part of the constructor/saved in the object, so you can use a different sample size for different epochs. Returns an array with a different address, containing the outputs of the layer.