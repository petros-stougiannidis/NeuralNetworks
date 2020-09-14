// Test Git_Username
#include "NeuralNetwork.h"
#include <algorithm>
#define ACTIVATION sigmoid // Zur Verf�gung stehen bisher "id", "sigmoid", "ReLU", "tanh" und "softsign".
#define ACTIVATION_DERIVATIVE sigmoid_derivative
//TODO: simoid-He-Initialisation; tanh-Xavier-Initialisation
using Dimensions = std::vector<size_t>;
using WeightMatrices = std::vector<Matrix<double>>;
using Biases = std::vector < Matrix<double>>;
/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Konstruktor bekommt zwei Argumente: die Lernrate und einen double-Vektoren, der die  //
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
            weights[i].randomize_double(-1 / sqrt(dimensions[i]), 1 / sqrt(dimensions[i]));
        }

        for (int i = 0; i < weights.size(); i++) {
            biases[i] = Matrix<double>(dimensions[i + 1], 1);
        }

    } catch (std::invalid_argument& error) { std::cerr << error.what() << std::endl; }

//////////////////////////////////////////////////////////////////////////////////////////////
// Da eine Gewichtsmatrix die Gewichtungen zwischen zwei Neuronenschichten darstellt, gibt  //
// es bei n Neuronenschichten immer n-1 Gewichtungsmatrizen. Deshalb wurde weights mit der  //
// L�nge dimensions.size() - 1 initialisiert. Die Zeilenanzahl einer Gewichtungsmatrix ent- //
// spricht der Neuronenanzahl der Schicht in die sie f�hrt und die Spaltenanzahl entspricht //
// der Neuronenanzahl der Schicht aus der sie stammt, daher wird die Matrix an der Stelle   //
// i, also weights[i],  mit einer Matrix mit Zeilenanzahl dimensions[i + 1] und Spaltenan-  //
// zahl dimensions[i] initialisiert. Die Matrizen werden dann mit zuf�lligen double-Werten  //
// besetzt.                                                                                 //
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion randomize_double(double a, double b) besetzt eine Matrix mit zuf�lligen     //
// double-Werten innerhalb des Intervalls [a,b)/{0}. Die hier gew�hlten Grenzen             //
// -1/sqrt(dimensions[i]) und 1 / sqrt(dimensions[i]) entsprechen der                       //
// "Xavier-Initialisierung" und sind abh�ngig von der Spaltenanzahl der Gewichtungsmatrix.  //
// Diese Technik f�hrt zu einem effizienteren Lernen.                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/
// mathematisch //////////////////////////////////////////////////////////////////////////////
double id(const double& x) {
    return x;
}
double id_derivative(const double& x) {
    return 1;
}
double sigmoid(const double& x) {
    return 1 / (1 + exp(-x));
}
double sigmoid_derivative(const double& x) {
    return sigmoid(1 - sigmoid(x));
}
double ReLU(const double& x) {
    return (0 <= x) ? x : 0;
}
double ReLU_derivative(const double& x) {
    return (0 <= x) ? 1 : 0;
}
//double tanh(const double& x) In cmath definiert
double tanh_derivative(const double& x) {
    return 1 - pow(tanh(x), 2);
}
double softsign(const double& x) {
    return x / (1 + abs(x));
}
double softsign_derivative(const double& x) {
    return 1 / pow((1 + abs(x)), 2);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Netzfunktionen ////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion feed_forward() bekommt einen Inputvektor als Argument, l�sst diesen einmal   //
// durch das neuronale Netz laufen und gibt dann einen Outputvektor zur�ck. Im trainierten  //
// Zustand des Netzes erh�lt man mit dieser Funktion eine L�sung f�r eine Regressions- oder //
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
// Die Funktion train() f�hrt einmal die Funktion feed_forward() aus, vergleicht den        //
// Outputvektor mit den Label des Datensatzes, berechnet daraus den Fehler E und passt dann //
// mit Backpropagation die Gewichtungen und den Bias an.                                    //
//////////////////////////////////////////////////////////////////////////////////////////////
void NeuralNetwork::train(const Matrix<double>& input, const Matrix<double>& training_data) {
    Matrix<double> E_0 = (feed_forward(input) - training_data);
    E_0.map(ACTIVATION_DERIVATIVE);
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





