#include "uni/allsettings.hpp"
#include "layer/layerlite.hpp"
#include "testdata/generatenumbers.hpp"
#include "testdata/viewer.hpp"
#include "activation/reluactivation.hpp"
#include "activation/softmaxactivation.hpp"
#include "utilities/matrixutility.hpp"

// The following function displays how to use this library. I tried to use as many functions as possible. I also use array, 2D array and matrix interchangeably.
// Feel free to skip the intro to utility functions and data generation and go strait to the actual AI Section.
int main(){


    // SECTION 1: Utility Functions and Number Generation


    std::cout << "---SECTION 1---" << std::endl;
    std::cout << "Utility Functions and Number Generation" << std::endl;


    // Create a 3 samples of 4 neurons. These are not labeled and are simply for making sure data can make it through forward passes.
    NumType** rawdata = createDeterministicArray3x4();

    // Let's now use the matrixViewer function to analyze our traindata
    std::cout << "The createDeterministicArray3x4 matrix:" << std::endl; // std:couts are so you can follow along in the terminal if you wish.
    matrixViewer(rawdata, 3, 4);
    // Notice how the first argument is the number of arrays, the second is the length of the arrays in each matrix.
    // This can be used for any matrix.

    // Let's create some more samples. All 3 of these functions are for creating raw data purely to see how passing data works.
    NumType** rawdata2 = createDeterministicArray4x4();
    std::cout << "The createDeterministicFloat4x4 matrix:" << std::endl;
    matrixViewer(rawdata2, 4, 4);
    NumType** rawdata3 = createDeterministicArray4x3();
    std::cout << "The createDeterministicFloat4x3 matrix:" << std::endl;
    matrixViewer(rawdata3, 4, 3);

    // We really don't need rawdata2 and rawdata3 anymore, so let's delete them.
    clearMatrix(rawdata2, 4); // The number parameter is the number of rows of the matrix.
    clearMatrix(rawdata3, 4);
    // Now none of the rows of these are taking up memory.


    // SECTION 2: AI Classes and Basic Individual Functions


    std::cout << "---SECTION 2---" << std::endl;
    std::cout << "AI Classes and Basic Individual Functions" << std::endl;


    /* Create an initial layer to recieve these neurons.
     * Note that this is not the input layer as seen in many abstractions.
     * That doesn't actually exist as an object, it's an array.
     * I am going to use variables for sizes in this file, feel free to not allocate the memory in your own code.
     * I'm just doing it for readability.
     */
    int input_layer_size = 4; // see rawdata line 10
    int number_of_samples = 3; // see rawdata line 10
    int number_of_neurons_in_hidden_1 = 5; // this is a completely arbitrary value.
    LayerLite hidden_layer_1(input_layer_size, number_of_neurons_in_hidden_1);

    /* I am now going to create a second hidden layer.
     * This layer takes activated values from hidden_layer_1 and augments them again.
     * To take these values, it's previous layer must be the size of number_of_neurons_in_hidden_1.
     * That is why I made a variable, so you can see what must be constant to avoid a shape error.
     */
    int number_of_neurons_in_hidden_2 = 2; // this again is arbitrary.
    LayerLite hidden_layer_2(number_of_neurons_in_hidden_1, number_of_neurons_in_hidden_2);

    /* Let's make an activation function now.
     * Activation functions augment each layers output to something non linear.
     * Let's start with relu. In my library, ReLU is modified to not need to be max(0, x) and instead be max(minimum, x).
     * By default minimum is 0, and I strongly advise against changing it, but to each their own.
     * Also note activation functions directly modify the array, rather than creating a bunch of new data, so let's make sure to copy our rawdata before testing this.
    */

    // ReLU with 0 as minimum RECOMMENDED
    NumType** activate1 = copyMatrix(rawdata, 3, 4); // copy rawdata, as relu would modify it otherwise.
    ActivationReLU relu; // declare relu with no minimum/0 as the minimum.
    relu.forwardTest(activate1, 3, 4); // Run ReLU on the data. Array, Rows, Cols.
    std::cout << "The rawdata matrix with relu:" << std::endl;
    matrixViewer(activate1, 3, 4); // View it
    clearMatrix(activate1, 3); //and free up our memory

    // ReLU with a custom minimum NOT RECOMMENDED
    NumType** activate2 = copyMatrix(rawdata, 3, 4); // copy rawdata, as relu would modify it otherwise.
    ActivationReLU relu8Min(0.8f); // declare relu with minimum 0.8f. This is really high and will likely result in mostly 0s. This is to show you the difference between 0 and 0.8f regardless of what's generated.
    relu8Min.forwardTest(activate2, 3, 4); // Run ReLU on the data.
    std::cout << "The rawdata matrix with relu(0.8f) aka max(0.8f):" << std::endl;
    matrixViewer(activate2, 3, 4); // View it
    clearMatrix(activate2, 3); //and free up our memory

    /* Let's try SoftMax now.
     * SoftMax has the standard SoftMax implementation.
     * [n1, n2, n3] -> [e^n1, e^n2, e^n3]/sum(e^n1, e^n2, e^n3) -> [m1, m2, m3]
     * Here's an example of SoftMax.
    */

    NumType** activate3 = copyMatrix(rawdata, 3, 4); // copy rawdata, as softmax would modify it otherwise.
    ActivationSoftMax soft; // create a softmax. There are no constructor arguments.
    soft.forwardTest(activate3, 3, 4); // Run softmax on the data.
    std::cout << "The rawdata matrix softmax:" << std::endl;
    matrixViewer(activate3, 3, 4); // View it
    clearMatrix(activate3, 3); //and free up our memory

    /* Now that we have Activation Functions and Layers, we can create a Network.
     * Here's an example of a Network, featuring a flow of frontpasses.
    */

    NumType** input_layer = copyMatrix(rawdata, 3, 4); // Remember, "input layers" are just arrays to be put into the first real layer.
    NumType** output_of_layer_1 = hidden_layer_1.forwardTest(input_layer, number_of_samples); // Apply the layer's math to data_pass.
    relu.forwardTest(output_of_layer_1, number_of_samples, number_of_neurons_in_hidden_1); // Remember, we don't have to save the return value for activations.
    NumType** output_of_layer_2 = hidden_layer_2.forwardTest(output_of_layer_1, number_of_samples);
    soft.forwardTest(output_of_layer_2, number_of_samples, number_of_neurons_in_hidden_2);
    std::cout << "The rawdata matrix being put through 2 layers of random weights, a ReLU and a SoftMax:" << std::endl;
    matrixViewer(output_of_layer_2, number_of_samples, number_of_neurons_in_hidden_2); // Had this model done anything, we might get some cool data here. In a trained model, the rows you see would be each sample, and the columns would be a different classification.
    clearMatrix(input_layer, number_of_samples); // SAVE RAM
    clearMatrix(output_of_layer_1, number_of_samples);
    clearMatrix(output_of_layer_2, number_of_samples);


    // SECTION 3: Backpasses, Epochs, and Actual Training


    std::cout << "---SECTION 3---" << std::endl;
    std::cout << "Backpasses, Epochs and Actual Training" << std::endl;


    std::cout << "Fin. You now have the output of the tutorial in your terminal." << std::endl;
    return 0;
}