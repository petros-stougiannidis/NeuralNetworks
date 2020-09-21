#include "NeuralNetwork.h"
#include "Matrix.h"

using WeightMatrices = std::vector<Matrix<double>>;
int main(int argc, char** argv) {


	
	NeuralNetwork n1(0.5, { 2, 3, 4 });
	WeightMatrices ws = n1.get_weights();
	for (auto& matrix : ws) {
		matrix.print();
		
	}
	Matrix<double> input(2, 1, 0);
	Matrix<double> data(4, 1, 1);
	input.randomize_double(0,1);
	n1.train(input,data);

	
	

	//std::vector<NeuralNetwork>(10, NeuralNetwork(0.5, { 8,2,2,3,4,5,6,7,8 }));
}
