#include "NeuralNetwork.h"
#include <algorithm>
#define ACTIVATION sigmoid  // Zur Verf�gung stehen bisher "id", "sigmoid", "ReLU", 
                            //"tanh" und "softsign".
#define ACTIVATION_DERIVATIVE apply_sigmoid_derivative
//TODO: simoid-He-Initialisation; tanh-Xavier-Initialisation

/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Konstruktor bekommt zwei Argumente: die Lernrate und einen double-Vektor, der die    //
// Dimension des neuronales Netzes angibt. Ein Vektor der Form {10,20,30,15} initialisiert  //
// ein Netz mit 10 Inputneuronen, zwei Hidden Layer mit jeweils 20 und 30 Neuronen und 15   //
// Outputneuronen.                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

NeuralNetwork::NeuralNetwork(const double& learningrate, const Topology& topology)
    try :   learningrate(learningrate),
            topology(topology),
            weights(WeightMatrices(topology.size() - 1)),
            biases(Biases(weights.size())) {

        if (topology.size() < 2) 
            throw std::invalid_argument
            ("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

        for (const len& val : topology) if (val <= 0) 
            throw std::invalid_argument
            ("Es wird mindestens ein Knoten pro Schicht benoetigt");

        for (int i = 0; i < weights.size(); i++) {
            weights[i] = Matrix<double>(topology[i + 1], topology[i], 0);
            weights[i].randomize_double(-1 / sqrt(topology[i]), 1 / sqrt(topology[i])); // times small scalar???
        }

        for (int i = 0; i < weights.size(); i++) {
            biases[i] = Matrix<double>(topology[i + 1], 1); // 0 Anfangsgewichtung
        }

    } catch (std::invalid_argument& error) { std::cerr << error.what() << std::endl; }

//////////////////////////////////////////////////////////////////////////////////////////////
// Da eine Gewichtsmatrix die Gewichtungen zwischen zwei Neuronenschichten darstellt, gibt  //
// es bei n Neuronenschichten immer n-1 Gewichtungsmatrizen. Deshalb wurde weights mit der  //
// L�nge topology.size() - 1 initialisiert. Die Zeilenanzahl einer Gewichtungsmatrix ent- //
// spricht der Neuronenanzahl der Schicht in die sie f�hrt und die Spaltenanzahl entspricht //
// der Neuronenanzahl der Schicht aus der sie stammt, daher wird die Matrix an der Stelle   //
// i, also weights[i],  mit einer Matrix mit Zeilenanzahl topology[i + 1] und Spaltenan-  //
// zahl topology[i] initialisiert. Die Matrizen werden dann mit zuf�lligen double-Werten  //
// besetzt.                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion randomize_double(double a, double b) besetzt eine Matrix mit zuf�lligen     //
// double-Werten innerhalb des Intervalls [a,b)/{0}. Die hier gew�hlten Grenzen             //
// -1/sqrt(topology[i]) und 1 / sqrt(topology[i]) entsprechen der                       //
// "Xavier-Initialisierung" und sind abh�ngig von der Spaltenanzahl der Gewichtungsmatrix.  //
// Diese Technik f�hrt zu einem effizienteren Lernen.                                       //
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
    for (len i = 0; i < weights.size(); i++) {
        std::cout << i + 1 << "te Gewichtungsmatrix: " << topology[i + 1] << "x" << topology[i] << "\n\n";
        weights[i].print();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Netzfunktionen ////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion feed_forward() bekommt einen Inputvektor als Argument, l�sst diesen einmal  //
// durch das neuronale Netz laufen und gibt dann einen Outputvektor zur�ck. Im trainierten  //
// Zustand des Netzes erh�lt man mit dieser Funktion eine L�sung f�r eine Regressions- oder //
// Klassifikationsaufgabe.                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////

Matrix<double> NeuralNetwork::feed_forward(const Matrix<double>& input) const {
    Matrix<double> output = input;
    for (len i = 0; i < weights.size(); i++) {
        output = (weights[i] * output) + biases[i];
        output.map(ACTIVATION);
    }
    return  output;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion train() f�hrt einmal die Funktion feed_forward() aus, vergleicht den        //
// Outputvektor mit dem Label des Datensatzes, berechnet daraus den Fehler E und passt dann //
// mit Backpropagation die Gewichtungen und den Bias an.                                    //
//////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetwork::train(const Matrix<double>& input, const Matrix<double>& training_data) {

    WeightMatrices outputs(topology.size());      // Pro Layer, ein Output
    WeightMatrices errors(weights.size());          // Pro Gewichtungsmatrix, ein Fehler
    outputs[0] = input;                             // Der erste Output ist der Input-Vektor;
    for (len i = 0; i < outputs.size()-1; i++) {    // Feedforward, wobei die alle Outputs 
                                                    // zwischengespeichert werden
        outputs[i + 1] = (weights[i] * outputs[i]) + biases[i];
        outputs[i + 1].map(ACTIVATION);
    }

    errors[errors.size() - 1] = training_data - outputs[outputs.size()-1]; 
    //der letzte Fehler ist E = Zielwerte minus dem letzten Output
    for (len i = errors.size()-2; i >= 0; i--) {
        errors[i] = weights[i + 1].transpose() * errors[i + 1]; //TODO:: .* activation'(z(i+1)) ????
        // Error_i-1 = Gewichtungen_i^T * Error_i (Fehler-Backpropagation)
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Fehler in vorhergehenden Schichten wird berechnet, indem der Fehler aus der Schicht  //
// davor den Gewichtungen entsprechend aufgeteilt wird. L�sst man die Normierungskonstante  //
// weg erh�lt man den Ausdruck: Error_(i-1) = Gewichtungen_(i)^T * Error_(i)                //
//////////////////////////////////////////////////////////////////////////////////////////////

    for (len i = weights.size() - 1; i >= 0; i--) {
        
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

Topology NeuralNetwork::get_dimensions() const {
    return topology;
}

Biases NeuralNetwork::get_biases() const {
    return biases;
}