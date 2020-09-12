#pragma once
#include "Matrix.h"
using WeightMatrices = std::vector<Matrix<double>>;
using Dimensions = std::vector<size_t>;

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const Dimensions& dimensions);
//Funktionen
    Matrix<double> query(const Matrix<double>& input) const;
    void train();
//Getter & Setter
    WeightMatrices get_weights() const;
    Dimensions get_dimensions() const;
private:
    double learningrate;
    Dimensions dimensions;
    WeightMatrices weights;
};



