#include <iostream>
#include <vector>
#include <cmath>

#include "FullyConnectedLayer.cpp"

class Network {
private:
    std::vector<FullyConnectedLayer> layers;
public:
    explicit FullyConnectedLayer (std::vector<std::vector<int>> dimensions) {
        // dimensions contain number of input nodes & output nodes in pairs for each of the layers
        for (int i = 0; i < dimensions.size(); i++) {
            layers.emplace_back(FullyConnectedLayer(dimensions[i][0], dimensions[i][1]));
        }
    }

    
}

