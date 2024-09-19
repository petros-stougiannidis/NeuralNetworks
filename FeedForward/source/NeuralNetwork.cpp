#include "NeuralNetwork.h"
#include <algorithm>

NeuralNetwork::NeuralNetwork(const float& learningrate, const std::vector<std::string>& activation_functions, const std::vector<int>& topology, const int& batch_size)
    try :   learningrate(learningrate),
            activation_functions(activation_functions),
            topology(topology),
            batch_size(batch_size),
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
                this->activation_functions = std::vector<std::string>(weights.size(), std::string("sigmoid"));
            }


    } catch (std::invalid_argument& error) {
         std::cerr << error.what() << std::endl;
    }


float sigmoid(const float& x) {
    return 1 / (1 + exp(-x));
}
Matrix<float>& apply_sigmoid(Matrix<float>& matrix) {
    return matrix.map([](const float& x) {return sigmoid(x); });
}
Matrix<float>& apply_sigmoid_derivative(Matrix<float>& matrix) { 
    return matrix.map([](const float& x) {return sigmoid(x) * (1 - sigmoid(x)); });
}
float ReLU(const float& x) {
    return (0 <= x) ? x : 0;
}
Matrix<float>& apply_ReLU(Matrix<float>& matrix) {
    return matrix.map([](const float& x) {return ReLU(x); });
}
Matrix<float>& apply_ReLU_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return (0 <= x) ? 1 : 0; });

}
float m_tanh(const float& x) {
    return tanh(x);
}
float m_exp(const float& x) {
    return exp(x);
}
Matrix<float>& apply_tanh(Matrix<float>& matrix) {
    return matrix.map(m_tanh);
}
Matrix<float>& apply_tanh_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return 1 - pow(tanh(x), 2); });
}
float softsign(const float& x) {
    return x / (1 + abs(x));
}
Matrix<float>& apply_softsign(Matrix<float>& matrix) {
    return matrix.map([](const float& x) {return softsign(x); });
}
Matrix<float>& apply_softsign_derivative(Matrix<float>& matrix) {
    return matrix.map([](const float& x) -> float {return 1 / pow((1 + abs(x)), 2); });
}
// Applies the softmax function to a batch of column vectors
Matrix<float>& apply_softmax(Matrix<float>& matrix) { // 
    float denominator;
    std::vector<int> position_of_biggest_per_column = matrix.argmax_batch();

    for (int j = 0; j < matrix.get_columns(); j++) {
        float val = matrix(position_of_biggest_per_column[j], j);
        for (int i = 0; i < matrix.get_rows(); i++) {

            matrix(i, j, matrix(i, j) - val);
        }
    }

    matrix.map(m_exp);
    for (int j = 0; j < matrix.get_columns(); j++) {
        float acc = 0;
        for (int i = 0; i < matrix.get_rows(); i++) {
            acc += matrix(i, j);
        }
        denominator = acc;
        for (int i = 0; i < matrix.get_rows(); i++) {
            matrix(i, j, matrix.get_value(i, j) / denominator);
        }
    }
    return matrix;
}
// This is still a wrong implementation
Matrix<float>& apply_softmax_derivative(Matrix<float>& matrix) { 
    apply_softmax(matrix);
    matrix = matrix.hadamard(Matrix<float>(matrix.get_rows(), matrix.get_columns(), 1) - matrix);
    return matrix;
}

Matrix<float> NeuralNetwork::feed_forward(const Matrix<float>& input) const {

    Matrix<float> output = input;
    for (int i = 0; i < weights.size(); i++) {

        auto activation = apply_sigmoid;
        if (activation_functions[i] == "relu") {
            activation = apply_ReLU;
        } else if (activation_functions[i] == "tanh") {
            activation = apply_tanh;
        } else if (activation_functions[i] == "softsign") {
            activation = apply_softsign;
        } else if (activation_functions[i] == "sigmoid") {
            activation = apply_sigmoid;
        }
        else if (activation_functions[i] == "softmax") {
            activation = apply_softmax;
        }
     

        output = (weights[i] * output) + biases[i];
        activation(output);
    }
    return  output;
}
void NeuralNetwork::train(const Matrix<float>& input, const Matrix<float>& training_data) {

    std::vector<Matrix<float>> outputs(topology.size());
    std::vector<Matrix<float>> weighted_sum(topology.size()-1);
    std::vector<Matrix<float>> errors(weights.size());

    outputs[0] = input;          

    for (int i = 0; i < outputs.size()-1; i++) {    


        auto activation = apply_sigmoid;
        if (activation_functions[i] == "relu") {
            activation = apply_ReLU;
        } else if (activation_functions[i] == "tanh") {
            activation = apply_tanh;
        } else if (activation_functions[i] == "softsign") {
            activation = apply_softsign;
        } else if (activation_functions[i] == "sigmoid") {
            activation = apply_sigmoid;
        } else if (activation_functions[i] == "softmax") {
            activation = apply_softmax;
        }

        outputs[i + 1] = (weights[i] * outputs[i]) + biases[i];
        weighted_sum[i] = outputs[i + 1];
        activation(outputs[i + 1]);
    }

    errors.back() = training_data - outputs.back(); 
    
    for (int i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; 
    }
       
    for (int i = weights.size() - 1; i >= 0; i--) {

        auto activation_derivative = apply_sigmoid_derivative;
        if (activation_functions[i] == "relu") {
            activation_derivative = apply_ReLU_derivative;
        } else if (activation_functions[i] == "tanh") {
            activation_derivative = apply_tanh_derivative;
        } else if (activation_functions[i] == "softsign") {
            activation_derivative = apply_softsign_derivative;
        } else if (activation_functions[i] == "sigmoid") {
            activation_derivative = apply_sigmoid_derivative;
        } else if (activation_functions[i] == "softmax") {
            activation_derivative = apply_softmax_derivative; 
        }
  

        Matrix<float> delta_biases = errors[i].hadamard(activation_derivative(weighted_sum[i]));
        Matrix<float> delta_weights = delta_biases * outputs[i].transpose();
        biases[i] += delta_biases * (learningrate / batch_size); 
        weights[i] += delta_weights * (learningrate / batch_size);
    } 
}

