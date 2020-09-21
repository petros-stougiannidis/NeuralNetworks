#pragma once
#include "Matrix.h"
using Dimensions = std::vector<size_t>;
using WeightMatrices = std::vector<Matrix<double>>;
using Biases = std::vector < Matrix<double>>;

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const Dimensions& dimensions);
//Funktionen
    void print();
    Matrix<double> feed_forward(const Matrix<double>& input) const;
    void train(const Matrix<double>& input, const Matrix<double>& training_data);
//Getter & Setter
    WeightMatrices get_weights() const;
    Dimensions get_dimensions() const;
private:
    double learningrate;
    Dimensions dimensions;
    WeightMatrices weights;
    Biases biases;

};



