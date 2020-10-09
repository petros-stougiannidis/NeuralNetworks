#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"
#include "PercentageBar.h"

#include "DataConverter.h "

#define TRAINSIZE 60000
#define TESTSIZE 10000
#define EPOCHS 1
#define INPUTSIZE 784
#define OUTPUTSIZE 10
#define TOPOLOGY {784,10,10}
#define LEARNINGRATE 0.1
#define PATH_TRAIN "mnist_train.csv"
#define PATH_TEST "mnist_test.csv"


#define training_data_set data_train.get_values()
#define training_labels data_train.get_labels()
#define test_data_set data_test.get_values()
#define test_labels data_test.get_labels()



void log(const std::string& msg) {
	std::cout << msg << std::endl;
}

int main(int argc, char** argv) {	

	DataConverter data_train(PATH_TRAIN, TRAINSIZE, INPUTSIZE, OUTPUTSIZE);
	DataConverter data_test(PATH_TEST, TESTSIZE, INPUTSIZE, OUTPUTSIZE);

	NeuralNetwork n1(LEARNINGRATE, TOPOLOGY);

	Timer timer;
	PercentageBar percentage_bar;

	log("training progress"); 
	timer.reset();

	int training_iterations = 0;
	for (int epochs = 0; epochs < EPOCHS; epochs++) {
		for (int i = 0; i < TRAINSIZE; i++) {
			n1.train(training_data_set[i], training_labels[i]);
			percentage_bar.print_progress(training_iterations, TRAINSIZE * EPOCHS);
			training_iterations++;
		}
	}
	timer.print_time<s>();
	percentage_bar.reset();

	log("testing progress");
	timer.reset();

	double success = 0;
	int test_iteration = 0;
	for (int i = 0; i < TESTSIZE; i++) {
		Matrix<double> erg = n1.feed_forward(test_data_set[i]);
		if (erg.max_position() == test_labels[i].max_position()) {
			success++;
		}
		percentage_bar.print_progress(test_iteration, TESTSIZE);
		test_iteration++;

	}
	timer.print_time<ms>();
	std::cout << "successrate = " << (success * 100 / TESTSIZE) << "%" << std::endl;

}


