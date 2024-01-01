#include <iostream>
#include <cmath>

#include "Matrix.cpp"
#include "TanhLayer.cpp"

class FullyConnectedLayer {
private:
    int noInputNodes;
    int noOutputNodes;
    Matrix<float> weights;
    Matrix<float> biases;

    Matrix<float> weightsDerivatives;
    Matrix<float> biasesDerivatives;

    TanhLayer activation;
    
public:
    // constructor when we only know the dimension of the layer
    FullyConnectedLayer (int _noInputNodes, int _noOutputNodes) {
        noInputNodes = _noInputNodes;
        noOutputNodes = _noOutputNodes;

        // In default constructor initialize all the weights to 1
        weights = Matrix<float>({noOutputNodes, noInputNodes}, 1);
        biases = Matrix<float>({noOutputNodes, 1}, 0);

        weightsDerivatives = Matrix<float>({noOutputNodes, noInputNodes}, 0);
        biasesDerivatives = Matrix<float>({noOutputNodes, 1}, 0);
    }

    // constructor when we have biases and weights of the layer
    FullyConnectedLayer (Matrix<float> _weights, Matrix<float> _biases) {
        noInputNodes = _weights.noColumns;
        noOutputNodes = _weight.noRows;

        weights = _weights;
        biases = _biases;

        weightsDerivatives = Matrix<float>({numNeurons,numInputs},0);
        biasDerivatives = Matrix<float>({numNeurons,1},0);
    }

    // initialize random weights and biases in range [-0.5, 0.5] with uniform distribution
    // Mersenne Twister pseudorandom number generator
    void randomLayer (std::mt19937 gen) {
        std::uniform_real_distribution<> weightDistribution(-0.5, 0.5);
        std::uniform_real_distribution<> biasDistribution(-0.5, 0.5);

        for (int i = 0; i < noInputNodes; i++) {
            for (int j = 0; j < noOutputNodes, j++) {
                weights.set(i, j, (float)(weightDistribution(gen)));
            }
            biases.set(i, 0, (float)(biasDistribution(gen)));
        }
    }

    // get output for the layer
    Matrix<float> forwardPropagate (const Matrix<float> &input){
        Matrix<float> output = weights.multiply(input);
        output.add(biases);
        return TanhLayer::forwardPropagate(output);
    }

    // get derivatives of cost wrt the input of this layer so that it can be used to recursively compute derivatives
    // of input of previous layer
    // update derivatives of cost with respect to each of the weights & biases in this current layer, obtained by
    // multiplying such derivative of the layer following it and the input of this layer (by chain rule)
    Matrix<float> getDerivatives (const Matrix<float> &input, const Matrix<float> &nextLayerDerivatives) {
        // account for sigmoid derivatives of the input
        Matrix<float> outputDerivatives = TanhLayer::getDerivatives(output, nextLayerDerivatives);

        biasesDerivatives.add(outputDerivatives);
        weightsDerivatives.add(Matrix<float>::multiply(outputDerivatives, Matrix<float>::transpose(input)));

        Matrix<float> inputDerivatives = Matrix<float>::multiply(weights, outputDerivatives);
        inputDerivatives.divide(weights.noRows);

        return inputDerivatives;
    }

    void applyDerivatives(float learnRate) {
        biases.subtract(biasDerivatives.multiply(learnRate));
        biasesDerivatives.setAll(0);

        weights.subtract(weightsDerivatives.multiply(learnRate));
        weightsDerivatives.setAll(0);
    }
}