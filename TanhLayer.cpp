#include <cmath>
#include "Matrix.cpp"

class TanhLayer{
public:
    static Matrix<float> forwardPropagate(const Matrix<float> &output) {
        return Matrix<float>::opElement(output, sigmoid);
    }

    static Matrix<float> getDerivatives(const Matrix<float> &thisLayerOutput, const Matrix<float> &nextLayerDerivatives) {
        Matrix<float> layerInputDerivatives = Matrix<float>::opElement(previousLayerOutput, [](float n) {return 1 - std::pow(n, 2.0f)); // derivative of tanhx is 1 - tanhx squared
        layerInputDerivatives.hProduct(nextLayerDerivatives);

        return layerInputDerivatives;
    }
}