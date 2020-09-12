#pragma once
#include "Matrix.h"

class NeuralNetwork {
public:
//Konstruktoren
    NeuralNetwork(double learningrate, std::vector<int> dimensions);
//Funktionen
    void query() const;
    void train();
   
//Getter & Setter
    std::vector<Matrix<double>> get_weights() const;
    std::vector<int> get_dimensions() const;
private:

    double learningrate;
    std::vector<int> dimensions;
    std::vector<Matrix<double>> weights;
};



