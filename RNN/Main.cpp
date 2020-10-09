#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"

#include "DataConverter.h "

#define TRAINSIZE 60000
#define TESTSIZE 10000
#define EPOCHS 1
#define INPUTSIZE 784
#define OUTPUTSIZE 10
#define TOPOLOGY {784,400,200,10}
#define LEARNINGRATE 0.01
#define PATH_TRAIN "mnist_train.csv"
#define PATH_TEST "mnist_test.csv"


#define training_data_set data_train.get_values()
#define training_labels data_train.get_labels()
#define test_data_set data_test.get_values()
#define test_labels data_test.get_labels()

len max_pos(const Matrix<double>& vec) {
	if (vec.get_rows() == 0) return 0;
	if (vec.get_rows() == 1) return 0;
	len pos = 0;
	double elem = vec.get_value(0,0);
	for (int i = 1; i < vec.get_rows(); i++) {
		if (vec.get_value(i,0) > elem) {
			pos = i;
			elem = vec.get_value(i,0);
		}
	}
	return pos;
}

void log(const std::string& msg) {
	std::cout << msg << std::endl;
}

int main(int argc, char** argv) {

	log("read data"); Timer t;

	DataConverter data_train(PATH_TRAIN, TRAINSIZE, INPUTSIZE, OUTPUTSIZE);
	DataConverter data_test(PATH_TEST, TESTSIZE, INPUTSIZE, OUTPUTSIZE);

	std::cout << "~~ " << t.elapsed_time<ms>() << " in ms" << std::endl;

	NeuralNetwork n1(LEARNINGRATE, TOPOLOGY);

	log("start training"); t.reset();

	for (int epochs = 0; epochs < EPOCHS; epochs++) {
		for (int i = 0; i < TRAINSIZE; i++) {
			n1.train(training_data_set[i], training_labels[i]);
			//std::cout << i << std::endl;
		}
	}

	std::cout << "~~ " << t.elapsed_time<ms>() << " ms" << std::endl;
	std::cout << "\a";

	 int success = 0;

	for (int i = 0; i < TESTSIZE; i++) {
		Matrix<double> erg = n1.feed_forward(test_data_set[i]);
		if (max_pos(erg) == max_pos(test_labels[i])) {
			success++;
		}
		/*erg.print();
		test_labels[i].print();*/

	}



	std::cout << "successrate = " << (success*100/TESTSIZE)  << "%" << std::endl;

}

