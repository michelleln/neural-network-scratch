#include <cmath>
#include "Matrix.cpp"

// Separate these activation operations into its own layer to make fully connected layer more organized
class TanhLayer{
public:
    static Matrix<float> forwardPropagate(const Matrix<float> &output) {
        return Matrix<float>::opElement(output, tanh);
    }

    static Matrix<float> getDerivatives(const Matrix<float> &previousLayerOutput, const Matrix<float> &nextLayerDerivatives) {
        Matrix<float> layerInputDerivatives = Matrix<float>::opElement(previousLayerOutput,[](float n) {return 1 - (float)std::pow(n,2.0f);}); // derivative of tanhx is 1 - tanhx squared
        layerInputDerivatives.hProduct(nextLayerDerivatives);

        return layerInputDerivatives;
    }
};