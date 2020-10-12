#include "NeuralNetwork.h"
#include <algorithm>
#include <cmath>
#define ACTIVATION sigmoid
#define ACTIVATION_DERIVATIVE apply_sigmoid_derivative 

//TODO: simoid-He-Initialisation; tanh-Xavier-Initialisation

NeuralNetwork::NeuralNetwork(const double& learningrate, const std::vector<len>& topology)
    /*  try*/ : learningrate(learningrate),
    topology(topology),
    weights(std::vector<Matrix<double>>(topology.size() - 1)),
    biases(std::vector<Matrix<double>>(weights.size())) {

    if (topology.size() < 2) throw std::invalid_argument("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

    for (const len& val : topology) if (val <= 0) throw std::invalid_argument("Es wird mindestens ein Knoten pro Schicht benoetigt");

    for (int i = 0; i < weights.size(); i++) {
        weights[i] = Matrix<double>(topology[i + 1], topology[i], 0);
        weights[i].randomize_double(-1 / sqrt(topology[i]), 1 / sqrt(topology[i])); // times small scalar???
    }

    for (int i = 0; i < weights.size(); i++) {
        biases[i] = Matrix<double>(topology[i + 1], 1); // 0 Anfangsgewichtung
    }

    /* } catch (std::invalid_argument& error) {
         std::cerr << error.what() << std::endl;
     }*/
}

double sigmoid(const double& x) {
    return 1 / (1 + exp(-x));
}
Matrix<double>& apply_sigmoid_derivative(Matrix<double>& matrix) { 
    return matrix.map([](const double& x) {return x * (1 - x); });
}
double ReLU(const double& x) {
    return (0 <= x) ? x : 0;
}
Matrix<double>& apply_ReLU_derivative(Matrix<double>& matrix) {
    return matrix.map([](const double& x) -> double {return (0 <= x) ? 1 : 0; });
}
double m_tanh(const double& x) {
    return tanh(x);
}
Matrix<double>& apply_tanh_derivative(Matrix<double>& matrix) {
    return matrix.map([](const double& x) -> double {return 1 - pow(tanh(x), 2); });
}
double softsign(const double& x) {
    return x / (1 + abs(x));
}
Matrix<double>& apply_softsign_derivative(Matrix<double>& matrix) {
    return matrix.map([](const double& val) -> double {return 1 / pow((1 + abs(val)), 2); });
}
Matrix<double> NeuralNetwork::feed_forward(const Matrix<double>& input) const {
    Matrix<double> output = input;
    for (len i = 0; i < weights.size(); i++) {
        output = (weights[i] * output);// +biases[i];
        output.map(ACTIVATION);
    }
    return  output;
}
void NeuralNetwork::train(const Matrix<double>& input, const Matrix<double>& training_data) {

    std::vector<Matrix<double>> outputs(topology.size());
    std::vector<Matrix<double>> errors(weights.size());

    outputs[0] = input;          

    for (len i = 0; i < outputs.size()-1; i++) {        
        outputs[i + 1] = (weights[i] * outputs[i]);// +biases[i];
        outputs[i + 1].map(ACTIVATION);
    }

    errors[errors.size() - 1] = training_data - outputs[outputs.size()-1]; 
    
    for (len i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; //TODO:: .* activation'(z(i+1)) ????
    }
        
    for (len i = weights.size() - 1; i >= 0; i--) {
        Matrix<double> delta_biases = errors[i].hadamard(ACTIVATION_DERIVATIVE(outputs[i + 1]));
        Matrix<double> delta_weights = delta_biases * outputs[i].transpose();
        //biases[i] += delta_biases * learningrate;
        weights[i] += delta_weights * learningrate;
    } 
}
std::vector<Matrix<double>> NeuralNetwork::get_weights() const {
    return weights;
}
std::vector<len> NeuralNetwork::get_dimensions() const {
    return topology;
}
std::vector<Matrix<double>> NeuralNetwork::get_biases() const {
    return biases;
}