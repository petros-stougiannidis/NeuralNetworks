#pragma once
#include "Matrix.h"


class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const float& learningrate, const std::vector<std::string>& activation_function, const std::vector<int>& topology, const int& batch_size);
//Funktionen
    Matrix<float> feed_forward(const Matrix<float>& input) const;
    void train(const Matrix<float>& input, const Matrix<float>& training_data);

private:
    float learningrate;
    std::vector<int> topology;
    std::vector<std::string> activation_functions;
    std::vector<Matrix<float>> weights;
    std::vector<Matrix<float>> biases;

};



