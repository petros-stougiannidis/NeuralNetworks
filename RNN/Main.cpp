#include <iostream>
#include "Matrix.h"
#include <vector>



int f(const int& val) {
	return (val+25) * 1000 / 3;
}

int main(int argc, char** argv) {
	Matrix<int> m1(1, 5, 10);
	Matrix<int> m2(5, 4, 2);
	Matrix<int> m3(std::vector<std::vector<int>>(0, std::vector<int>(2, 1)));
	
	m1 *= m2;


	
	
	//m1.map( [](const int &i) { return 3; });
	//m1.map(f);
	m3.print();
}
