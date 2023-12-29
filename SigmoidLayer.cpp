#include <cmath>
#include "Matrix.cpp"

class SigmoidLayer{
public:
    static Matrix<float> forwardPropagate(const Matrix<float> &output) {
        return Matrix<float>::opElement(output, sigmoid);
    }

    static Matrix<float> getDerivatives(const Matrix<float> &thisLayerOutput, const Matrix<float> &nextLayerDerivatives) {
        Matrix<float> layerInputDerivatives = Matrix<float>::opElement(previousLayerOutput, [](float n) {return std::exp(-n) / std::pow(1.0f + std::exp(-n), 2.0f));
        layerInputDerivatives.hProduct(nextLayerDerivatives);

        return layerInputDerivatives;
    }
}