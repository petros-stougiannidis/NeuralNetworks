#include "NeuralNetwork.h"
#include "Matrix.h"
#include "Timer.h"
#include "DataConverter.h"

using WeightMatrices = std::vector<Matrix<double>>;
//using namespace std;
int main(int argc, char** argv) {


	//DataConverter data1("C:\\Users\\petro\\c++\\datasets\\mnist_train_100.csv");
	//std::vector<std::string> v1 = data1.read_csv();
	//std::cout << v1[0];
	
	//***********************************************************
	//Max Testing:
	// DataConverter data1("mini_test.csv");
	// std::vector<std::string> v1 = data1.read_csv();
	// std::cout << v1[1] << std::endl;

	//Timer t;
	//NeuralNetwork n1(0.3, { 3, 4, 3 });
	//n1.print();
	//std::cout << "took " << t.elapsed_time<ms>() << " milliseconds to initialize.\n\n" << std::endl;

	//Matrix<double> input(3, 1, 0);
	//Matrix<double> data(3, 1, 1);
	////input.randomize_double(0,1);
	//t.reset();
	//for (int i = 0; i < 1000; i++) {
	//	n1.train(input, data);
	//	//std::cout << i << std::endl;
	//	//n1.print();
	//}	
	//std::cout << "trained for " << t.elapsed_time<s>() << " seconds.\n\n";
	//
	//std::cout << "Ergebnis: ";
	//input.print();
	//n1.feed_forward(input).print();
	////std::vector<NeuralNetwork>(10, NeuralNetwork(0.5, { 8,2,2,3,4,5,6,7,8 }));
}
