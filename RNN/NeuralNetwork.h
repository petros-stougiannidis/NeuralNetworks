#pragma once
#include "Matrix.h"
using len = int;

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const std::vector<len>& topology);
//Funktionen
    Matrix<double> feed_forward(const Matrix<double>& input) const;
    void train(const Matrix<double>& input, const Matrix<double>& training_data);
//Getter & Setter
    std::vector<Matrix<double>> get_weights() const;
    std::vector<len> get_dimensions() const;
    std::vector<Matrix<double>> get_biases() const;
private:
    double learningrate;
    std::vector<len> topology;
    std::vector<Matrix<double>> weights;
    std::vector<Matrix<double>> biases;

};



