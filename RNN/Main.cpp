#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"
#include "PercentageBar.h"
#include "DataConverter.h "   // normal mul == 100 s, blocksize 4 = 110

#define TRAINSIZE 60000
#define TESTSIZE 10000
#define EPOCHS 1
#define BATCHSIZE 10 // preferably divisor of data_set_size 
#define INPUTSIZE 784
#define OUTPUTSIZE 10
#define TOPOLOGY {784,10,10}
#define LEARNINGRATE 0.1
#define PATH_TRAIN "mnist_train.csv"
#define PATH_TEST "mnist_test.csv"

//#define TRAINSIZE 100
//#define TESTSIZE 10
//#define EPOCHS 3
//#define BATCHSIZE 10
//#define INPUTSIZE 784
//#define OUTPUTSIZE 10
//#define TOPOLOGY {784,200,10}
//#define LEARNINGRATE 0.3
//#define PATH_TRAIN "mnist_train_100.csv"
//#define PATH_TEST "mnist_test_10.csv"





void log(const std::string& msg) {
	std::cout << msg << std::endl;
}

int count_matches_in_batch(const std::vector<len>& a, const std::vector<len>& b) {
	int success = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) success++;
	}
	return success;
}

int main(int argc, char** argv) {	
	
	DataConverter training(PATH_TRAIN, TRAINSIZE, INPUTSIZE, OUTPUTSIZE, BATCHSIZE);
	DataConverter test(PATH_TEST, TESTSIZE, INPUTSIZE, OUTPUTSIZE, BATCHSIZE);

	NeuralNetwork n1(LEARNINGRATE, TOPOLOGY, BATCHSIZE);


	Timer timer;
	PercentageBar percentage_bar;

	log("training progress"); 
	timer.reset();

	int training_iterations = 0;
	for (int epochs = 0; epochs < EPOCHS; epochs++) {
		for (int i = 0; i < TRAINSIZE / BATCHSIZE; i++) {
			n1.train(training.data_set[i], training.label_set[i]);
			percentage_bar.print_progress(training_iterations, (TRAINSIZE * EPOCHS) / BATCHSIZE);
			training_iterations++;
		}
	}
	timer.print_time<s>();
	percentage_bar.reset();

	log("testing progress");
	timer.reset();
	Matrix<double> e;
	double success = 0;
	int test_iteration = 0;
	for (int i = 0; i < TESTSIZE / BATCHSIZE; i++) {
		Matrix<double> output = n1.feed_forward(test.data_set[i]);
		success += count_matches_in_batch(
						output.evaluate_batch(),
						test.label_set[i].evaluate_batch());

		percentage_bar.print_progress(test_iteration, TESTSIZE / BATCHSIZE);
		test_iteration++;

	}
	timer.print_time<ms>();
	std::cout << "successrate = " << (success * 100 / TESTSIZE) << "%" << std::endl;

}


