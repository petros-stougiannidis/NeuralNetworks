#pragma once
#include "Matrix.h"


class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const std::vector<int>& topology, const int& batch_size);
//Funktionen
    Matrix<double> feed_forward(const Matrix<double>& input) const;
    void train(const Matrix<double>& input, const Matrix<double>& training_data);

private:
    double learningrate;
    std::vector<int> topology;
    std::vector<Matrix<double>> weights;
    std::vector<Matrix<double>> biases;

};



