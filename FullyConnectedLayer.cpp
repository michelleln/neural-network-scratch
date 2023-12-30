#include <iostream>
#include <vector>
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

        weightDerivatives = Matrix<float>({numNeurons,numInputs},0);
        biasDerivatives = Matrix<float>({numNeurons,1},0);
    }

    // get outputt for the layer
    Matrix<float> forwardPropagate (const Matrix<float> &input){
        Matrix<float> output = weights.multiply(input);
        output.add(biases);
        return TanhLayer::forwardPropagate(output);
    }

    // get derivatives of cost with respect to each of the weights in this current layer, which is obtained by
    // multiplying such derivative of the layer following it and the input of this layer (by chain rule)
    Matrix<float> getDerivatives (const Matrix<float> &input) {
        
    }
}