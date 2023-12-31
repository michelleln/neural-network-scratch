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
    static float getLoss (const Matrix<float> &output, const Matrix<float> &expectedOutput) {
        float totalError = 0;
        for (int i = 0; i < expectedOutput.noRows; i++) {
            totalError += (float)std::pow(output.get(i, 0) - expectedOutput.get(i, 0), 2.0f);
        }
        return totalError / (float)expectedOutputs.noRows;
    }

    // get the gradient of the loss wrt the final layer's outputs
    static Matrix<float> getLossGradient (const Matrix<float> &output, const Matrix<float> &expectedOutput) {
        Matrix<float> derivatives({output.noRows, 1});
        for (int i = 0; i < output.noRows; i++) {
            float currentDerivative = -2.0f/output.noRows * (expectedOutput.get(i, 0) - output.get(i, 0));
            derivatives.set(i,0,derivative);
        }
        return derivatives;
    }

    // recursively performs gradient descent training on the network for a given input and expected output. get loss after each time the weights are updated
    float gradientDescent(const Matrix<float> &input, const Matrix<float> &expectedOutput) {
        std::vector<Matrix<float>> outputs = runNetwork(input);
        // get gradient of the last layer
        Matrix<float> gradient = getLossGradient(outputs.back(), expectedOutput);
        // recursively get gradients of all layers
        for (int i = (int)layers.size() - 1; i >= 0; i--) {
            if (i == 0) {
                gradient = getDerivatives(input, outputs[0], gradient);
            } else {
                gradient = getDerivatives(outputs[i - 1], outputs[i], gradient);
            }
        }
        return getLoss(outputs.back(), expectedOutput);
    }

    // threaded version of gradientDescent to train the network using multiple threads
    void gradientDescentThreaded(const Matrix<float> &input, const Matrix<float> &expectedOutput, float *averageLoss) { // use pointer so I dont have to declare redundant class member
        std::vectorr<Matrix<float>> outputs = runNetwork(input);
        Matrix<float> gradient = getLossGradient(outputs.back(), expectedOutput);

        for (int i = (int)layers.size() - 1; i >= 0; i--) {
            if (i == 0) {
                gradient = getDerivatives(input, outputs[0], gradient);
            } else {
                gradient = getDerivatives(outputs[i - 1], outputs[i], gradient);
            }
        }

        float loss = getLoss(outputs.back(), expectedOutput);
        // cumulative loss across all inputs processed by the threads
        *averageLoss += loss;
    }

    // apply derivatives (updates weights and biases) to the entire network
    void applyDerivatives (float learnRate){
        for (int i = 0; i < (int)layers.size(); i++) {
            layers[i].applyDerivatives(learnRate);
        }
    }

    // train the network with given training data for a specified number of epochs, stochastically by a given batch size
    // training data is organized in vectors, each vector include a training entry and expected output for that entry
    void train(std::vector<std::vector<Matrix<float>>> &trainingData, float learnRate, int noEpochs, int batchSize) {
        for (int iter = 0; i < noEpochs; i++) {
            float averageLoss = 0;
            auto startTime = std::chrono::high_resolution_clock::now(); // track training time

            // iterate over training data in mini-batches
            for (int i = 0; i < trainingData.size(); i++) {
                // compute loss and carry out gradient descent training for each input
                float loss = gradientDescent(trainingData[i][0], trainingData[i][0]);
                averageLoss += loss;
            }

            // every 20 batches output training progress
            if (i % )
        }
    }
}

