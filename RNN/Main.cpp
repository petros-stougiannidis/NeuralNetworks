#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"
#include "DataConverter.h"
#define TRAINSIZE 60000
#define TESTSIZE 10000
#define EPOCHS 1
#define HIDDENLAYERS 10

using WeightMatrices = std::vector<Matrix<double>>;
using DATA = std::vector<Matrix<double>>;
void log(const std::string& msg) {
	std::cout << msg << std::endl;
}

int main(int argc, char** argv) {

	std::cout << "read data" << std::endl;
	Timer t;
	DataConverter training("mnist_train_100.csv");
	DataConverter test("mnist_test_10.csv");
	std::cout << "~~ " << t.elapsed_time<s>() << " s" << std::endl;

	std::cout << "trainingset size: " << training.get_values()[0].get_rowdim() << std::endl;


	std::cout << "\a";


///////////////////////////////////////////////////////////////////////
// Testdatensatz zur Erlernung der XOR Funktion
///////////////////////////////////////////////////////////////////////
// Initialisere Inputvektoren mit zwei zufälligen Bits
	//t.reset();
	//log("initialize training data");
	//std::vector<Matrix<double>> training_data_set(TRAINSIZE, Matrix<double>(2,1));
	//for (Matrix<double>& m : training_data_set) {
	//	m.randomize_int(0,1);
	//}
///////////////////////////////////////////////////////////////////////
// Berechne Labelvektoren mit der XOR-Operation
	//std::vector<Matrix<double>> training_labels(TRAINSIZE, Matrix<double>(1, 1));
	//for (int i = 0; i < training_labels.size(); i++) {
	//	int a = (int) training_data_set[i].get_value(0, 0);
	//	int b = (int) training_data_set[i].get_value(1, 0);
	//	training_labels[i].set_value(0, 0, a ^ b);
	//
	//}
	//std::cout << "~~ " << t.elapsed_time<ms>() << " ms" << std::endl;

///////////////////////////////////////////////////////////////////////
// Erstelle Testdatensatz nach dem selben Prinzip
	//t.reset();
	//log("initialize test data");
	//std::vector<Matrix<double>> test_data_set(TESTSIZE, Matrix<double>(2, 1));
	//for (Matrix<double>& m : test_data_set) {
	//	m.randomize_int(0, 1);
	//}
	//std::vector<Matrix<double>> test_labels(TESTSIZE, Matrix<double>(1, 1));
	//for (int i = 0; i < test_labels.size(); i++) {
	//	int a = (int)test_data_set[i].get_value(0, 0);
	//	int b = (int)test_data_set[i].get_value(1, 0);
	//	test_labels[i].set_value(0, 0, (double) (a ^ b));
	//
	//}
	//std::cout << "~~ " << t.elapsed_time<ms>() << " ms" << std::endl;
	
///////////////////////////////////////////////////////////////////////
// Initialisre Netz mit Lernrate 0.1, zwei Inputs und einem Ouput
	NeuralNetwork n1(0.1, { 784, 200, 10 });

///////////////////////////////////////////////////////////////////////
// Trainiere Netz EPOCHS mal am Trainingsdatensatz
	log("start training");
	t.reset();
	for (int epochs = 0; epochs < EPOCHS; epochs++) {
		for (int i = 0; i < TRAINSIZE; i++) {
			n1.train(training.get_values()[i], training.get_labels()[i]);
			//std::cout << i << std::endl;
		}
	}
	std::cout << "~~ " << t.elapsed_time<s>() << " s" << std::endl;
	std::cout << "\a";
///////////////////////////////////////////////////////////////////////
// Messung der Erfolgsrate am Testdatensatz
	int success = 0;
	for (int i = 0; i < TESTSIZE; i++) {
		Matrix<double> erg = n1.feed_forward(test.get_values()[i]);
		if (abs((erg.get_value(0, 0) - test.get_labels()[i].get_value(0, 0)) < 0.2)) {
			success++;
		}
	}
	std::cout << "successrate = " << success / TESTSIZE *100 << "%";
}
