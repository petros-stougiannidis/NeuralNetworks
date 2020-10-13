#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"
#include "PercentageBar.h"
#include "DataConverter.h"  
//
#define TRAINSIZE 60000
#define TESTSIZE 10000
#define EPOCHS 20
#define BATCHSIZE 10 // preferably divisor of data_set_size 
#define INPUTSIZE 784
#define OUTPUTSIZE 10
#define TOPOLOGY {784,20,10}
#define LEARNINGRATE 0.1
#define ACTIVATION {"relu", "sigmoid"}
#define PATH_TRAIN "mnist_train.csv"
#define PATH_TEST "mnist_test.csv"

//#define TRAINSIZE 100
//#define TESTSIZE 10
//#define EPOCHS 3
//#define BATCHSIZE 1 // preferably divisor of data_set_size 
//#define INPUTSIZE 784
//#define OUTPUTSIZE 10
//#define TOPOLOGY {784,20,10}
//#define LEARNINGRATE 0.5
//#define ACTIVATION {"relu", "relu"}
//#define PATH_TRAIN "mnist_train_100.csv"
//#define PATH_TEST "mnist_test_10.csv"

void log(const std::string& msg) {
	std::cout << msg << std::endl;
}
int count_matches_in_batch(const std::vector<int>& a, const std::vector<int>& b) {
	int success = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) success++;
	}
	return success;
}

int main(int argc, char** argv) {	


	//read and parse datasets
	DataConverter training(PATH_TRAIN, TRAINSIZE, INPUTSIZE, OUTPUTSIZE, BATCHSIZE);
	DataConverter test(PATH_TEST, TESTSIZE, INPUTSIZE, OUTPUTSIZE, BATCHSIZE);

	//initialze neural network
	NeuralNetwork n1(LEARNINGRATE, ACTIVATION, TOPOLOGY, BATCHSIZE);
		
	Timer timer;
	PercentageBar percentage_bar;

	log("training progress"); 
	timer.reset();

	int training_iteration = 0;
	for (int epochs = 0; epochs < EPOCHS; epochs++) {
		for (int i = 0; i < TRAINSIZE / BATCHSIZE; i++) {

			n1.train(training.data_set[i], training.label_set[i]);

			percentage_bar.print_progress(training_iteration, (TRAINSIZE * EPOCHS) / BATCHSIZE);
			training_iteration++;
		}
	}
	timer.print_time<s>();
	percentage_bar.reset();

	log("testing progress");
	timer.reset();

	float success = 0;
	int test_iteration = 0;
	for (int i = 0; i < TESTSIZE / BATCHSIZE; i++) {
		Matrix<float> output = n1.feed_forward(test.data_set[i]);
		success += count_matches_in_batch(
						output.argmax_batch(),
						test.label_set[i].argmax_batch());

		percentage_bar.print_progress(test_iteration, TESTSIZE / BATCHSIZE);
		test_iteration++;

		

	}
	timer.print_time<s>();
	std::cout << "successrate = " << (success * 100 / TESTSIZE) << "%" << std::endl;
	n1.feed_forward(test.data_set[0]).print();
}


