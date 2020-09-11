#include <iostream>
#include "Matrix.h"
#include <string>
#include <functional>
#include <random>

int main() {
	Matrix<double> m1({	{0,1,2},
						{3,4,5},
						{6,7,8}	});

	Matrix<int> m2(4, 4, 5);


	//m1.randomize_double(0, 1);
	m1.print();

	m2.randomize_int(0, 10);
	m2.print();

	
}