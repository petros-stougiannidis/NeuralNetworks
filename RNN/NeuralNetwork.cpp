#include "NeuralNetwork.h"
#include <algorithm>
#define ACTIVATION sigmoid  // Zur Verfügung stehen bisher "id", "sigmoid", "ReLU", 
                            //"tanh" und "softsign".
#define ACTIVATION_DERIVATIVE apply_sigmoid_derivative
//TODO: simoid-He-Initialisation; tanh-Xavier-Initialisation
using Dimensions = std::vector<size_t>;
using WeightMatrices = std::vector<Matrix<double>>;
using Biases = std::vector < Matrix<double>>;

/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Konstruktor bekommt zwei Argumente: die Lernrate und einen double-Vektor, der die    //
// Dimension des neuronales Netzes angibt. Ein Vektor der Form {10,20,30,15} initialisiert  //
// ein Netz mit 10 Inputneuronen, zwei Hidden Layer mit jeweils 20 und 30 Neuronen und 15   //
// Outputneuronen.                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

NeuralNetwork::NeuralNetwork(const double& learningrate, const Dimensions& dimensions)
    try :   learningrate(learningrate),
            dimensions(dimensions),
            weights(WeightMatrices(dimensions.size() - 1)),
            biases(Biases(weights.size())) {

        if (dimensions.size() < 2) 
            throw std::invalid_argument
            ("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

        for (const size_t& val : dimensions) if (val <= 0) 
            throw std::invalid_argument
            ("Es wird mindestens ein Knoten pro Schicht benoetigt");

        for (int i = 0; i < weights.size(); i++) {
            weights[i] = Matrix<double>(dimensions[i + 1], dimensions[i], 0);
            weights[i].randomize_double(-1 / sqrt(dimensions[i]), 1 / sqrt(dimensions[i])); // times small scalar???
        }

        for (int i = 0; i < weights.size(); i++) {
            biases[i] = Matrix<double>(dimensions[i + 1], 1); // 0 Anfangsgewichtung
        }

    } catch (std::invalid_argument& error) { std::cerr << error.what() << std::endl; }

//////////////////////////////////////////////////////////////////////////////////////////////
// Da eine Gewichtsmatrix die Gewichtungen zwischen zwei Neuronenschichten darstellt, gibt  //
// es bei n Neuronenschichten immer n-1 Gewichtungsmatrizen. Deshalb wurde weights mit der  //
// Länge dimensions.size() - 1 initialisiert. Die Zeilenanzahl einer Gewichtungsmatrix ent- //
// spricht der Neuronenanzahl der Schicht in die sie führt und die Spaltenanzahl entspricht //
// der Neuronenanzahl der Schicht aus der sie stammt, daher wird die Matrix an der Stelle   //
// i, also weights[i],  mit einer Matrix mit Zeilenanzahl dimensions[i + 1] und Spaltenan-  //
// zahl dimensions[i] initialisiert. Die Matrizen werden dann mit zufälligen double-Werten  //
// besetzt.                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion randomize_double(double a, double b) besetzt eine Matrix mit zufälligen     //
// double-Werten innerhalb des Intervalls [a,b)/{0}. Die hier gewählten Grenzen             //
// -1/sqrt(dimensions[i]) und 1 / sqrt(dimensions[i]) entsprechen der                       //
// "Xavier-Initialisierung" und sind abhängig von der Spaltenanzahl der Gewichtungsmatrix.  //
// Diese Technik führt zu einem effizienteren Lernen.                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// mathematisch //////////////////////////////////////////////////////////////////////////////

double id(const double& x) {
    return x;
}

Matrix<double> apply_id_derivative(Matrix<double> matrix) {
    return matrix.map([](const double& val) -> double {return 1; });
}

double sigmoid(const double& x) {
    return 1 / (1 + exp(-x));
}

Matrix<double> apply_sigmoid_derivative(Matrix<double> matrix) { 
    return matrix.map([](const double& val) {return val * (1 - val); });
}

double ReLU(const double& x) {
    return (0 <= x) ? x : 0;
}

Matrix<double> apply_ReLU_derivative(Matrix<double> matrix) {
    return matrix.map([](const double& val) -> double {return (0 <= val) ? 1 : 0; });
}

//double tanh(const double& x) In cmath definiert
Matrix<double> apply_tanh_derivative(Matrix<double> matrix) {
    return matrix.map([](const double& val) -> double {return 1 - pow(tanh(val), 2); });
}

double softsign(const double& x) {
    return x / (1 + abs(x));
}

Matrix<double> apply_softsign_derivative(Matrix<double> matrix) {
    return matrix.map([](const double& val) -> double {return 1 / pow((1 + abs(val)), 2); });
}

Matrix<double> mean_squared_error(const Matrix<double>& y, const Matrix<double>& y_hat) {
    Matrix<double> result;
    result = ((y - y_hat).map([](const double& val) -> double {return pow(val, 2); }))*0.5;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Print & Debugging /////////////////////////////////////////////////////////////////////////

void NeuralNetwork::print() {
    for (int i = 0; i < weights.size(); i++) {
        std::cout << i + 1 << "te Gewichtungsmatrix: " << dimensions[i + 1] << "x" << dimensions[i] << "\n\n";
        weights[i].print();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Netzfunktionen ////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion feed_forward() bekommt einen Inputvektor als Argument, lässt diesen einmal  //
// durch das neuronale Netz laufen und gibt dann einen Outputvektor zurück. Im trainierten  //
// Zustand des Netzes erhält man mit dieser Funktion eine Lösung für eine Regressions- oder //
// Klassifikationsaufgabe.                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////

Matrix<double> NeuralNetwork::feed_forward(const Matrix<double>& input) const {
    Matrix<double> output = input;
    for (int i = 0; i < weights.size(); i++) {
        output = (weights[i] * output) + biases[i];
        output.map(ACTIVATION);
    }
    return  output;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion train() führt einmal die Funktion feed_forward() aus, vergleicht den        //
// Outputvektor mit dem Label des Datensatzes, berechnet daraus den Fehler E und passt dann //
// mit Backpropagation die Gewichtungen und den Bias an.                                    //
//////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetwork::train(const Matrix<double>& input, const Matrix<double>& training_data) {

    WeightMatrices outputs(dimensions.size());      // Pro Layer, ein Output
    WeightMatrices errors(weights.size());          // Pro Gewichtungsmatrix, ein Fehler
    outputs[0] = input;                             // Der erste Output ist der Input-Vektor;
    for (int i = 0; i < outputs.size()-1; i++) {    // Feedforward, wobei die alle Outputs 
                                                    // zwischengespeichert werden
        outputs[i + 1] = (weights[i] * outputs[i]) + biases[i];
        outputs[i + 1].map(ACTIVATION);
    }

    errors[errors.size() - 1] = training_data - outputs[outputs.size()-1]; 
    //der letzte Fehler ist E = Zielwerte minus dem letzten Output
    for (int i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; //TODO:: .* activation'(z(i+1)) ????
        // Error_i-1 = Gewichtungen_i^T * Error_i (Fehler-Backpropagation)
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Fehler in vorhergehenden Schichten wird berechnet, indem der Fehler aus der Schicht  //
// davor den Gewichtungen entsprechend aufgeteilt wird. Lässt man die Normierungskonstante  //
// weg erhält man den Ausdruck: Error_(i-1) = Gewichtungen_(i)^T * Error_(i)                //
//////////////////////////////////////////////////////////////////////////////////////////////

    for (int i = weights.size() - 1; i >= 0; i--) {
        
        Matrix<double> delta_biases = errors[i].hadamard(ACTIVATION_DERIVATIVE(outputs[i+1]));
        Matrix<double> delta_weights = delta_biases * outputs[i].transpose();
        biases[i] += delta_biases * learningrate;
        weights[i] += delta_weights * learningrate;
        // analytischer Ausdruck zur Berechnung der Gewichtungsaktualisierung basierend auf dem
        // Fehler in der jeweiligen Schicht
        
    } 
}

/********************************************************************************************/
/*                                     GETTER & SETTER                                      */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Getter ////////////////////////////////////////////////////////////////////////////////////

WeightMatrices NeuralNetwork::get_weights() const {
    return weights;
}

Dimensions NeuralNetwork::get_dimensions() const {
    return dimensions;
}

Biases NeuralNetwork::get_biases() const {
    return biases;
}