// main function
// load training data here
// output into a csv file
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "Network.cpp"

int main()
{
    // read training entries from csv file
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> entry;
    std::string line;
    std::string word;

    std::fstream trainingFile("mnist_train.csv", std::ios::in);
    // get training entry by entry
    if (trainingFile.is_open())
    {
        std::cout << "Reading training data" << std::endl;
        while (std::getline(trainingFile, line))
        {
            entry.clear();
            std::stringstream str(line);
            while (std::getline(str, word, ','))
            {
                entry.push_back(word);
            }
            content.push_back(entry);
        }
    }
    else
    {
        std::cout << "Could not open file" << std::endl;
        return 0;
    }
    std::cout << "File reading completed" << std::endl;

    std::cout << "Processing training data" << std::endl;

    std::vector<std::vector<Matrix<float>>> trainingData; // transform into format compatible with train fucntion in Network layer

    //skip fieldname line in csv
    for (int i = 1; i < content.size(); i++)
    {
        entry = content[i];

        std::vector<float> inputPixel(784);
        std::vector<float> outputLabel(10);
        outputLabel[std::stoi(entry[0])] = 1; // only correct label set to 1, rest set to 0
        for (int j = 1; j < 784 + 1; j++)
        {
            inputPixel[j - 1] = std::stof(entry[j]) / 255; // normalize pixel input to have value [0, 1]
        }
        trainingData.push_back({Matrix<float>({784, 1}, inputPixel), Matrix<float>({10, 1}, outputLabel)});
    }

    std::cout << "Training data processing completed" << std::endl;

    // initiate a network with only 1 hidden layer that has 50 neurons
    std::vector<std::vector<int>> networkDimension = {
        {784, 50},
        {50, 10}};

    Network myNetwork = Network(networkDimension);

    // randomize weights & biases for each epoch

    myNetwork.randomNetwork();
    std::cout << "Running network" << std::endl;

    int noEpochs = 15;
    int batchSize = 16;
    float learnRate = 0.03;

    // Heavy-lifting train function
    myNetwork.trainThreaded(trainingData, noEpochs, batchSize, learnRate);

    content.clear();
        // get test data entry by entry
        std::fstream testFile("mnist_test.csv", std::ios::in);
    if (testFile.is_open())
    {
        std::cout << "Reading test data" << std::endl;
        while (std::getline(testFile, line))
        {
            entry.clear();
            std::stringstream str(line);
            while (std::getline(str, word, ','))
            {
                entry.push_back(word);
            }
            content.push_back(entry);
        }
    }
    else
    {
        std::cout << "Could not open file" << std::endl;
        return 0;
    }
    std::cout << "File reading completed" << std::endl;

    std::cout << "Processing test data" << std::endl;

    std::vector<std::vector<Matrix<float>>> testData; // transform into format compatible with train fucntion in Network layer

    //skip fieldname line in csv
    for (int i = 1; i < content.size(); i++)
    {
        entry = content[i];

        std::vector<float> inputPixel(784);
        std::vector<float> outputLabel(10);
        outputLabel[std::stoi(entry[0])] = 1; // only correct label set to 1, rest set to 0
        for (int j = 1; j < 784 + 1; j++)
        {
            inputPixel[j - 1] = std::stof(entry[j]) / 255; // normalize pixel input to have value [0, 1]
        }
        testData.push_back({Matrix<float>({784, 1}, inputPixel), Matrix<float>({10, 1}, outputLabel)});
    }

    std::cout << "Test data processing completed" << std::endl;

    // Network predicts test data and log accuracy
    int noCorrect = 0;
    for (int i = 0; i < testData.size(); i++)
    {
        Matrix<float> output = myNetwork.runNetwork(testData[i][0]).back();
        int predictedOutput = 0;
        for (int j = 1; j < output.noRows; j++)
        {
            if (output.get(j, 0) > output.get(predictedOutput, 0))
            {
                predictedOutput = j;
            }
        }

        int expectedOutput = 0;
        for (int j = 1; j < testData[i][1].data.size(); j++)
        {
            if (testData[i][1].data[j] > testData[i][1].data[expectedOutput])
            {
                expectedOutput = j;
            }
        }

        if (predictedOutput == expectedOutput)
        {
            noCorrect++;
        }
        std::cout << "Predicted: " + std::to_string(predictedOutput) + " Actual: " + std::to_string(expectedOutput) << std::endl;
    }
    std::cout << "Accuracy: " + std::to_string((float)noCorrect / (float)testData.size()) << std::endl;

    return 0;
}
