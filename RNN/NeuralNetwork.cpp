#include "NeuralNetwork.h"
#define ACTIVATION sigmoid // Zur Verf�gung stehen bisher "id" und "sigmoid"
using WeightMatrices = std::vector<Matrix<double>>;
/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Konstruktor bekommt zwei Argumente: die Lernrate und einen double-Vektoren, der die  //
// Dimension des neuronales Netzes angibt. Ein Vektor der Form {10,20,30,15} initialisiert  //
// ein Netz mit 10 Inputneuronen, zwei Hidden Layer mit jeweils 20 und 30 Neuronen und 15   //
// Outputneuronen.                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
NeuralNetwork::NeuralNetwork(const double& learningrate, const std::vector<size_t>& dimensions) : learningrate(learningrate), dimensions(dimensions), weights(WeightMatrices(dimensions.size() - 1)) {
    try {
        if (dimensions.size() < 1) throw std::invalid_argument("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

        for (const size_t& val : dimensions) if (val <= 0) throw std::invalid_argument("Es wird mindestens ein Knoten pro Schicht benoetigt");

        for (int i = 0; i < weights.size(); i++) {
            weights[i] = Matrix<double>(dimensions[i + 1], dimensions[i], 0);
            weights[i].randomize_double(0.33, 0.66); //TODO: Spezielle Randomizefunktion unter Normalverteilung
        }
        // Da eine Gewichtsmatrix die Gewichtungen zwischen zwei Neuronenschichten darstellt, gibt es bei n Neuronenschichten immer n-1 Gewichtungsmatrizen.
        // Deshalb wurde weights mit der L�nge dimensions.size() - 1 initialisiert. Die Zeilenanzahl einer Gewichtungsmatrix entspricht der Neuronenanzahl 
        // der Schicht in die sie f�hrt und die Spaltenanzahl entspricht der Neuronenanzahl der Schicht aus der sie stammt, daher wird die Matrix an der Stelle
        // i, also weights[i],  mit einer Matrix mit Zeilenanzahl dimensions[i + 1] und Spaltenanzahl dimensions[i] initialisiert. Die Matrizen werden dann mit zu-
        // f�lligen double-Werten besetzt.
    }
    catch (std::invalid_argument& error) {std::cerr << error.what() << std::endl;}
}
/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion query() bekommt einen Inputvektor als Argument, l�sst diesen einmal durch   //
// das neuronale Netz laufen und gibt dann einen Outputvektor zur�ck. Im trainierten Zu-    //
// stand des Netzes erh�lt man mit dieser Funktion eine L�sung f�r eine Regressions- oder   //
// Klassifikationsaufgabe.                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////
// MATH //////////////////////////////////////////////////////////////////////////////////////
double id(const double& x) {
    return x;
}
double sigmoid(const double& x) {
    return 1 / (1 + exp(-x));
}
//////////////////////////////////////////////////////////////////////////////////////////////
//Netzfunktionen//////////////////////////////////////////////////////////////////////////////
Matrix<double> NeuralNetwork::query(const Matrix<double>& input) const {
    Matrix<double> output = input;
    for (int i = 0; i < weights.size(); i++) {
        output = (weights[i] * output).map(ACTIVATION);
    }
    return  output;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion train() f�hrt einmal die Funktion query() aus, vergleicht den Outputvektor  //
// mit den Label des Datensatzes, berechnet daraus den Fehler E und passt dann mit Back-    //
// propagation die Gewichtungen an.                                                         //
//////////////////////////////////////////////////////////////////////////////////////////////
void NeuralNetwork::train() {

}
/********************************************************************************************/
/*                                     GETTER & SETTER                                      */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Getter ////////////////////////////////////////////////////////////////////////////////////
std::vector<Matrix<double>> NeuralNetwork::get_weights() const {
    return weights;
}
std::vector<size_t> NeuralNetwork::get_dimensions() const {
    return dimensions;
}





