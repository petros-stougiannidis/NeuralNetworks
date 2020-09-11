#include <iostream>
#include "Matrix.h"
#include <vector>



int f(const int& val) {
	return (val+25) * 1000 / 3;
}

int main(int argc, char** argv) {
	Matrix<int> m1(3, 3);
	m1.iota(10);
	Matrix<int> m2(3, 3, 2);

	Matrix<int> m3 = m1 / 2;
	m3 /= 100;


	
	
	//m1.map( [](const int &i) { return 3; });
	//m1.map(f);
	m3.print();
}
