#include "NeuralNetwork.h"


using vec = std::vector<Matrix<double>>;
int main(int argc, char** argv) {

	NeuralNetwork n1(0.5, { 1,2,3,4 });
	vec v1 = n1.get_weights();
	for (auto& val : v1) {
		val.print();
	}


}
