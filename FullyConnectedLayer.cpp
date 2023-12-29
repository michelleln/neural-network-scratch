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
    
public:
    FullyConnectedLayer (int _noInputNodes, int _noOutputNodes) {
        vector<double> weights;
        vector<double> biases;

        vector<double> output;

        for (int i = 0; i < noNodes, i++){

        }

    }
}