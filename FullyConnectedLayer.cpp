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
    // default constructor
    FullyConnectedLayer (int _noInputNodes, int _noOutputNodes) {
        noInputNodes = _noInputNodes;
        noOutputNodes = _noOutputNodes;

        // In default constructor initialize all the weights to 1
        weights = Matrix<float>({noOutputNodes, noInputNodes}, 1);
        biases = Matrix<float>({noOutputNodes, 1}, 0);

        weightsDerivatives = Matrix<float>({noOutputNodes, noInputNodes}, 0);
        biasesDerivatives = Matrix<float>({noOutputNodes, 1}, 0);
    }

    FullyConnectedLayer (Matrix<float> weights, )
}