#include "NeuralNetwork.h"

/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Der Konstruktor bekommt zwei Argumente: die Lernrate und einen double-Vektoren, der die  //
// Dimension des neuronales Netzes angibt. Ein Vektor der Form {10,20,30,15} initialisiert  //
// ein Netz mit 10 Inputneuronen, zwei Hidden Layer mit jeweils 20 und 30 Neuronen und 15   //
// Outputneuronen.                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

using WeightMatrices = std::vector<Matrix<double>>;
NeuralNetwork::NeuralNetwork(double learningrate, std::vector<int> dimensions) : learningrate(learningrate), dimensions(dimensions), weights(WeightMatrices(dimensions.size() - 1, Matrix<double>())) {
    try {
        if (dimensions.size() < 1) throw std::invalid_argument("Es werden mindestens ein Eingangs- und eine Ausgangsschicht benoetigt");

        for (const int& val : dimensions) if (val <= 0) throw std::invalid_argument("Es wird mindestens ein Knoten pro Schicht benoetigt");

        for (int i = 0; i < weights.size(); i++) {
            weights[i] = Matrix<double>(dimensions[i + 1], dimensions[i], 0);
            weights[i].randomize_double(0.33, 0.66); //TODO: Spezielle Randomizefunktion unter Normalverteilung
        }
    }
    catch (std::invalid_argument& error) {std::cerr << error.what() << std::endl;}
}
/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion query() bekommt einen Inputvektor als Argument, lässt diesen einmal durch   //
// das neuronale Netz laufen und gibt dann einen Outputvektor zurück. Im trainierten Zu-    //
// stand des Netzes erhält man mit dieser Funktion eine Lösung für eine Regressions- oder   //
// Klassifikationsaufgabe.                                                                  //
//////////////////////////////////////////////////////////////////////////////////////////////
void NeuralNetwork::query() const {

}
//////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion train() führt einmal die Funktion query() aus, vergleicht den Outputvektor  //
// mit den Label des Datensatzes, berechnet daraus den Fehler E und passt dann mit Back-    //
// propagation die Gewichtungen an.                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////
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





