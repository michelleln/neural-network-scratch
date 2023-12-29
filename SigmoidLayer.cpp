#include <cmath>
#include "Matrix.cpp"

class SigmoidLayer{
public:
    static Matrix<float> forwardPropagate(const Matrix<float> &output) {
        return Matrix<float>::opElement(output, sigmoid);
    }

    static Matrix<float> getDerivatives(const Matrix<float> &layerInputDerivatives, const Matrix<float> &nextLayerDerivatives) {
        
    }
}