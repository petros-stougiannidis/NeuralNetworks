#pragma once
#include "Matrix.h"

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(const double& learningrate, const std::vector<size_t>& dimensions);
//Funktionen
    Matrix<double> query(const Matrix<double>& input) const;
    void train();
//Getter & Setter
    std::vector<Matrix<double>> get_weights() const;
    std::vector<size_t> get_dimensions() const;
private:
    double learningrate;
    std::vector<size_t> dimensions;
    std::vector<Matrix<double>> weights;
};



