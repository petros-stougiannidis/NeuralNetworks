#include "NeuralNetwork.h"
#include "Matrix.h"

using WeightMatrices = std::vector<Matrix<double>>;
int main(int argc, char** argv) {



	NeuralNetwork n1(0.5, { 8,2,2,3,4,5,6,7,8 });
	WeightMatrices ws = n1.get_weights();
	for (auto& matrix : ws) {
		matrix.print();
		
	}
	Matrix<double> matrix(8, 1, 0);
	matrix.randomize_double(0,1);
	Matrix<double> m1 = n1.feed_forward(matrix);
	m1.print();


	//std::vector<NeuralNetwork>(10, NeuralNetwork(0.5, { 8,2,2,3,4,5,6,7,8 }));
}
