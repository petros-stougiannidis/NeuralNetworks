#include "NeuralNetwork.h"
#include <algorithm>

NeuralNetwork::NeuralNetwork(const float& learningrate, const std::vector<std::string>& activation_functions, const std::vector<int>& topology, const int& batch_size)
    try :   learningrate(learningrate),
            activation_functions(activation_functions),
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

            if (activation_functions.size() != weights.size()) {
                std::cout << std::endl;
                std::cout << "The number of activations functions doesnt match the number of layers. Initializing with sigmoid (default)." << std::endl << std::endl;
                this->activation_functions = std::vector<std::string>(weights.size() - 1, std::string("sigmoid"));
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
//float softmax(const float& x) { // TODO
//    return 
//}
Matrix<float> NeuralNetwork::feed_forward(const Matrix<float>& input) const {

    Matrix<float> output = input;
    for (int i = 0; i < weights.size(); i++) {

        auto activation = sigmoid;
        if (activation_functions[i] == "relu") {
            auto activation = ReLU;
        }
        else if (activation_functions[i] == "tanh") {
            auto activation = m_tanh;
        }
        else if (activation_functions[i] == "softsign") {
            auto activation = softsign;
        }

        output = (weights[i] * output) + biases[i];
        output.map(activation);
    }
    return  output;
}
void NeuralNetwork::train(const Matrix<float>& input, const Matrix<float>& training_data) {

    std::vector<Matrix<float>> outputs(topology.size());
    std::vector<Matrix<float>> weighted_sum(topology.size()-1);
    std::vector<Matrix<float>> errors(weights.size());

    outputs[0] = input;          

    for (int i = 0; i < outputs.size()-1; i++) {    


        auto activation = sigmoid;
        if (activation_functions[i] == "relu") {
            auto activation = ReLU;
        }
        else if (activation_functions[i] == "tanh") {
            auto activation = m_tanh;
        }
        else if (activation_functions[i] == "softsign") {
            auto activation = softsign;
        }

        outputs[i + 1] = (weights[i] * outputs[i]) + biases[i];
        weighted_sum[i] = outputs[i + 1];
        outputs[i + 1].map(activation);
    }

    errors.back() = training_data - outputs.back(); 
    
    for (int i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; //TODO:: .* activation'(z(i+1)) ????
    }
       
    for (int i = weights.size() - 1; i >= 0; i--) {

        auto activation_derivative = apply_sigmoid_derivative;
        if (activation_functions[i] == "relu") {
            auto activation_derivative = apply_ReLU_derivative;
            //std::cout << "using relu" << std::endl;
        }
        else if (activation_functions[i] == "tanh") {
            auto activation_derivative = apply_tanh_derivative;
            //std::cout << "using tanh" << std::endl;
        }
        else if (activation_functions[i] == "softsign") {
            auto activation_derivative = apply_softsign_derivative;
            //std::cout << "using soft" << std::endl;
        }
        else {
            //std::cout << "using sigmoid" << std::endl;
        }

        Matrix<float> delta_biases = errors[i].hadamard(activation_derivative(weighted_sum[i]));
        Matrix<float> delta_weights = delta_biases * outputs[i].transpose();
        biases[i] += delta_biases * learningrate;
        weights[i] += delta_weights * learningrate;
    } 
}

