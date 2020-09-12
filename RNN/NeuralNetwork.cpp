#include "NeuralNetwork.h"

/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/

NeuralNetwork::NeuralNetwork(double learningrate, std::vector<int> dimensions) {
    try {
        if (dimensions.size() < 2) throw std::invalid_argument("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");
        for (int i = 0; i < dimensions.size(); i++) {
            if (dimensions[i] <= 0) throw std::invalid_argument("Es wird mindestens ein Knoten pro Schicht benoetigt");
        }
        //this->learningrate = learningrate;
        this->dimensions = dimensions;
        this->weights = std::vector<Matrix<double>>(dimensions.size() - 1, Matrix<double>());
        for (int i = 0; i < weights.size(); i++) {
            weights[i] = Matrix<double>(dimensions[i + 1], dimensions[i], 0);
            weights[i].randomize_double(0.3, 0.7); //TODO: Spezielle Randomizefunktion unter Normalverteilung
        }
    }
    catch (std::invalid_argument& error) {
        std::cerr << error.what() << std::endl;
    }
}
/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/

void NeuralNetwork::query() const {

}
void NeuralNetwork::train() {

}

/********************************************************************************************/
/*                                       GETTER & SETTER                                    */
/********************************************************************************************/

std::vector<Matrix<double>> NeuralNetwork::get_weights() const {
    return weights;
}
std::vector<int> NeuralNetwork::get_dimensions() const {
    return dimensions;
}





