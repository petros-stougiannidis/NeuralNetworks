#include "NeuralNetwork.h"
#include <algorithm>

NeuralNetwork::NeuralNetwork(const float& learningrate, const std::string& activation_function, const std::vector<int>& topology, const int& batch_size)
    try :   learningrate(learningrate),
            activation_function(activation_function),
            topology(topology),
            weights(std::vector<Matrix<float>>(topology.size() - 1)),
            biases(std::vector<Matrix<float>>(weights.size())) {

            if (topology.size() < 2) throw std::invalid_argument("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

            for (const int& val : topology) if (val <= 0) throw std::invalid_argument("Es wird mindestens ein Knoten pro Schicht benoetigt");

            for (int i = 0; i < weights.size(); i++) {
                weights[i] = Matrix<float>(topology[i + 1], topology[i], 0);
                weights[i].randomize(-1 / sqrt(topology[i]), 1 / sqrt(topology[i]));
            }

            for (int i = 0; i < weights.size(); i++) {
                biases[i] = Matrix<float>(topology[i + 1], batch_size, 0); 
            }

    } catch (std::invalid_argument& error) {
         std::cerr << error.what() << std::endl;
    }


float sigmoid(const float& x) {
    return 1 / (1 + exp(-x));
}
Matrix<float>& apply_sigmoid_derivative(Matrix<float>& matrix) { 
    return matrix.map([](const float& x) {return sigmoid(x) * (1 - sigmoid(x)); });
}
float ReLU(const float& x) {
    return (0 <= x) ? x : 0;
}
Matrix<float>& apply_ReLU_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return (0 <= x) ? 1 : 0; });
}
float m_tanh(const float& x) {
    return tanh(x);
}
Matrix<float>& apply_tanh_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return 1 - pow(tanh(x), 2); });
}
float softsign(const float& x) {
    return x / (1 + abs(x));
}
Matrix<float>& apply_softsign_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return 1 / pow((1 + abs(x)), 2); });
}
Matrix<float> NeuralNetwork::feed_forward(const Matrix<float>& input) const {

    auto activation = sigmoid;
    if (activation_function == "relu") {
        auto activation = ReLU;
    }
    else if (activation_function == "tanh") {
        auto activation = m_tanh;
    }
    else if (activation_function == "softsign") {
        auto activation = softsign;
    }

    Matrix<float> output = input;
    for (int i = 0; i < weights.size(); i++) {
        output = (weights[i] * output) + biases[i];
        output.map(activation);
    }
    return  output;
}
void NeuralNetwork::train(const Matrix<float>& input, const Matrix<float>& training_data) {

    auto activation = sigmoid;
    auto activation_derivative = apply_sigmoid_derivative;
    if (activation_function == "relu") {
        auto activation = ReLU;
        auto activation_derivative = apply_ReLU_derivative;
    }
    else if (activation_function == "tanh") {
        auto activation = m_tanh;
        auto activation_derivative = apply_tanh_derivative;
    }
    else if (activation_function == "softsign") {
        auto activation = softsign;
        auto activation_derivative = apply_softsign_derivative;
    }

    std::vector<Matrix<float>> outputs(topology.size());
    std::vector<Matrix<float>> weighted_sum(topology.size()-1);
    std::vector<Matrix<float>> errors(weights.size());

    outputs[0] = input;          

    for (int i = 0; i < outputs.size()-1; i++) {        
        outputs[i + 1] = (weights[i] * outputs[i]) + biases[i];
        weighted_sum[i] = outputs[i + 1];
        outputs[i + 1].map(activation);
    }

    errors.back() = training_data - outputs.back(); 
    
    for (int i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; //TODO:: .* activation'(z(i+1)) ????
    }
       
    for (int i = weights.size() - 1; i >= 0; i--) {
        Matrix<float> delta_biases = errors[i].hadamard(activation_derivative(weighted_sum[i]));
        Matrix<float> delta_weights = delta_biases * outputs[i].transpose();
        biases[i] += delta_biases * learningrate;
        weights[i] += delta_weights * learningrate;
    } 
}

