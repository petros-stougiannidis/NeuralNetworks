#pragma once
#include "Matrix.h"
using len = int;
using Topology = std::vector<len>;
using WeightMatrices = std::vector<Matrix<double>>;
using Biases = std::vector < Matrix<double>>;

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const Topology& topology);
//Funktionen
    void print();
    Matrix<double> feed_forward(const Matrix<double>& input) const;
    void train(const Matrix<double>& input, const Matrix<double>& training_data);
//Getter & Setter
    WeightMatrices get_weights() const;
    Topology get_dimensions() const;
    Biases get_biases() const;
private:
    double learningrate;
    Topology topology;
    WeightMatrices weights;
    Biases biases;

};



