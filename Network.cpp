#include <iostream>
#include <vector>
#include <cmath>

#include "FullyConnectedLayer.cpp"

class Network {
private:
    std::vector<FullyConnectedLayer> layers;
public:
    // constructor
    explicit FullyConnectedLayer (std::vector<std::vector<int>> dimensions) {
        // dimensions contain number of input nodes & output nodes in pairs for each of the layers
        for (int i = 0; i < dimensions.size(); i++) {
            layers.emplace_back(FullyConnectedLayer(dimensions[i][0], dimensions[i][1]));
        }
    }

    // assign random weights & biases to each layer
    void randomNetwork {
        std::random_device rd; //obtain a seed for the random number generator
        std::mt19937 gen(rd()); //initializes a Mersenne Twister pseudorandom number generator with the seed obtained from the random device

        for (int i = 0; i < layers.size(); i++) {
            //pass the gen object eeach layer to allow the layers to generate random weights and biases using the same random number generator across layers
            layers[i].randomLayer(gen); 
        }
    }

    // Forrward pass, get all outputs of all layers
    // input is a vector with size equal to noInputNodes of 1st layer, similarly output size equals nOutputNodes of last layer
    std::vector<Matrix<float>> runNetwork(Matrix<float> input) {
        std::vector<Matrix<float>> outputs;
        for (int i = 0; i < layers.size(); i++) {
            input = layers[i].forwardPropagate(input);
            outputs.push_back(input);
        }
        return outputs;
    }

    // get loss using mean-squared error loss
    static float getLoss (Matrix<float> &output, Matrix<float> &expectedOutput) {
        float totalError = 0;
        for (int i = 0; i < expectedOutput.noRows; i++) {
            totalError += (float)std::pow(output.get(i, 0) - expectedOutput.get(i, 0), 2.0f);
        }
        return totalError / (float)expectedOutputs.noRows;
    }

    // get the gradient of the loss wrt the final layer's outputs
    static Matrix<float> getLossGradient (Matrix<float> &output, Matrix<float> &expectedOutput) {
        Matrix<float> derivatives({output.noRows, 1});
        for (int i = 0; i < output.noRows; i++) {
            float currentDerivative = -2.0f/output.noRows * (expectedOutput.get(i, 0) - output.get(i, 0));
            derivatives.set(i,0,derivative);
        }
        return derivatives;
    }

    // recursively performs gradient descent training on the network for a given input and expected output. get loss after each time weights are updated
    float gradientDescent(Matrix<float> &input, Matrix<float> &expectedOutput) {
        
    }
}

