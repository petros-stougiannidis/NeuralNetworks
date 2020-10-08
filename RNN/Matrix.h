#pragma once
#include <iostream>
#include <vector>
#include <random>

#define GENERIC template<typename T>

using len = int;

GENERIC class Matrix {
	static_assert(std::is_arithmetic_v<T>, "+++ ERROR: matrix must contain arithmetic datatype +++\n\n"); //Matrixklasse für arithmetische Datentypen (int, float, double etc.)

private:
	len rows;
	len columns;
	std::vector<T> elements;

public:
	//Konstruktoren
	Matrix<T>() = default;
	Matrix<T>(const len& rows, const len& columns); //construct Matrix and fill with 0
	Matrix<T>(const len& rows, const len& columns, const T& value); //construct Matrix and fill with start value
	Matrix<T>(const len& rows, const len& columns, const std::vector<T>& vector); //construct Matrix out if existing Vector by copying
	Matrix<T>(const len& rows, const len& columns, std::vector<T>&& to_be_moved); //construct Matrix out if existing Vector without copying and leaving the vector as hollow object
	Matrix<T>(const Matrix<T>& to_be_copied) = default;
	Matrix<T>(Matrix<T>&& to_be_moved) = default;
	~Matrix() = default;

	//Copy & Move Assignment
	Matrix<T>& operator=(const Matrix<T>& m2) = default;
	Matrix<T>& operator=(Matrix<T>&& m2) = default;

	//Getter & Setter
	len get_rows() const;
	len get_columns() const;
	T get_value(const len& row, const len& column) const;
	Matrix<T>& set_value(const len& row, const len& column, const T& value);

	//Operatoren
	bool operator==(const Matrix<T>& m2) const;
	T operator()(const size_t& row, const size_t& column) const;
	Matrix<T>& operator()(const size_t& row, const size_t& column, const T& value);
	Matrix<T> operator-() const;
	Matrix<T> operator+(const Matrix<T>& m2) const;
	Matrix<T>& operator+=(const Matrix<T>& m2);
	Matrix<T> operator+(const T& scalar) const;
	Matrix<T>& operator+=(const T& scalar);
	Matrix<T> operator-(const Matrix<T>& m2) const;
	Matrix<T>& operator-=(const Matrix<T>& m2);
	Matrix<T> operator-(const T& scalar) const;
	Matrix<T>& operator-=(const T& scalar);
	Matrix<T> operator*(const T& scalar) const;
	Matrix<T>& operator*=(const T& scalar);
	Matrix<T> operator*(const Matrix<T>& m2) const;
	Matrix<T>& operator*=(const Matrix<T>& m2);
	Matrix<T> operator/(const T& scalar) const;
	Matrix<T>& operator/=(const T& scalar);

	//Funktionen
	void print() const;
	Matrix<T> transpose() const;
	Matrix<T> unit_matrix(const len& dimension) const;
	Matrix<T>& map(T function(const T&));
	Matrix<T>& iota();
	Matrix<T>& iota(const T& start);
	Matrix<T>& randomize_int(const int min, const int max);
	Matrix<T>& randomize_double(double min, double max);
	Matrix<T> hadamard(const Matrix<T>& m2);
};
//////////////////////////////////////////////////////////////////////////////////////////////
//  KONSTRUKTOREN  ///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC Matrix<T>::Matrix(const len& rows, const len& columns)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	this->elements = std::move(std::vector<T>(rows * columns));
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const len& rows, const len& columns, const T& value)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	this->elements = std::move(std::vector<T>(rows * columns, value));
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const len& rows, const len& columns, const std::vector<T>& vector)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	if (rows * columns != vector.size()) throw std::invalid_argument("+++ ERROR: dimension dont match vector length +++");
	this->elements = vector;
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const len& rows, const len& columns, std::vector<T>&& to_be_moved)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	if (rows * columns != to_be_moved.size()) throw std::invalid_argument("+++ ERROR: dimension dont match vector length +++");
	this->elements = std::move(to_be_moved);
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  GETTER & SETTER  /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC len Matrix<T>::get_rows() const {
	return rows;
}
GENERIC len Matrix<T>::get_columns() const {
	return columns;
}
GENERIC T Matrix<T>::get_value(const len& row, const len& column) const {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		return elements.at(row * columns + column);
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::set_value(const len& row, const len& column, const T& value) {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		elements[row * columns + column] = value;
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  FUNKTIONEN  //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC void Matrix<T>::print() const {
	if (!elements.empty()) {
		for (len i = 0; i < rows; i++) {
			for (len j = 0; j < columns; j++) {
				std::cout << elements[i * columns + j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "()" << std::endl;
	}
}
GENERIC Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> transposed(columns, rows);
	for (len i = 0; i < rows; i++) {
		for (len j = 0; j < columns; j++) {
			transposed.elements[j * transposed.columns + i] = this->elements[i * columns + j];
		}
	}
	return transposed;
}
GENERIC Matrix<T> Matrix<T>::unit_matrix(const len& dimension) const {
	std::vector<T> result;
	result.reserve(dimension * dimension);
	for (len i = 0; i < dimension; i++) {
		for (len j = 0; j < dimension; j++) {
			if (i == j) {
				result.emplace_back(1);
			}
			else {
				result.emplace_back(0);
			}

		}
	}
	return Matrix<T>(dimension, dimension, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::map(T function(const T&)) {  // :: a -> a // BROKEN
	for (len i = 0; i < rows * columns; i++) {
		elements[i] = function(elements[i]);
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::iota() {
	T value = 0;
	for (len i = 0; i < rows * columns; i++) {
		elements[i] = value++;
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::iota(const T& start) {
	T value = start;
	for (len i = 0; i < rows * columns; i++) {
		elements[i] = value++;
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::randomize_int(const int min, const int max) {
	std::random_device rd;
	std::mt19937 seed(rd());
	std::uniform_int_distribution<int> dist(min, max);
	for (int i = 0; i < rows * columns; i++) {
		elements[i] = (T)dist(seed);
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::randomize_double(double min, double max) {
	std::random_device rd;
	std::mt19937 seed(rd());
	std::uniform_real_distribution<double> dist(min, max);
	for (int i = 0; i < rows * columns; i++) {
		elements[i] = (T)dist(seed);
		while (elements[i] == 0) {
			elements[i] = (T)dist(seed);
			std::cout << "Matrix Element wurde zufällig auf 0 gesetzt!" << std::endl; // TODO: Profen
		}
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::hadamard(const Matrix<T>& m2) {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (len i = 0; i < rows * columns; i++) {
			result.emplace_back(elements[i] * m2.elements[i]);
		}
		return Matrix<T>(rows, columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATOREN  //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC bool Matrix<T>::operator==(const Matrix<T>& m2) const {
	if (rows != m2.rows) {
		return false;
	}
	else if (columns != m2.columns) {
		return false;
	}
	else if (elements != m2.elements) {
		return false;
	}
	else {
		return true;
	}
}
GENERIC T Matrix<T>::operator()(const size_t& row, const size_t& column) const {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		return elements.at(row * columns + column);
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::operator()(const size_t& row, const size_t& column, const T& value) {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		elements[row * columns + column] = value;
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T> Matrix<T>::operator-() const {
	std::vector<T> result;
	result.reserve(rows * columns);
	for (len i = 0; i < rows * columns; i++) {
		result.emplace_back(-elements[i]);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T> Matrix<T>::operator+(const Matrix<T>& m2) const {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (len i = 0; i < rows * columns; i++) {
			result.emplace_back(elements[i] + m2.elements[i]);
		}
		return Matrix<T>(rows, columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m2) {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		for (len i = 0; i < rows * columns; i++) {
			elements[i] += m2.elements[i];
		}
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T> Matrix<T>::operator+(const T& scalar) const {
	std::vector<T> result;
	result.reserve(rows * columns);
	for (len i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] + scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator+=(const T& scalar) {
	for (len i = 0; i < rows * columns; i++) {
		elements[i] += scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator-(const Matrix<T>& m2) const {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (len i = 0; i < rows * columns; i++) {
			result.emplace_back(elements[i] - m2.elements[i]);
		}
		return Matrix<T>(rows, columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m2) {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		for (len i = 0; i < rows * columns; i++) {
			elements[i] -= m2.elements[i];
		}
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T> Matrix<T>::operator-(const T& scalar) const {
	std::vector<T> result;
	result.reserve(rows * columns);
	for (len i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] - scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator-=(const T& scalar) {
	for (len i = 0; i < rows * columns; i++) {
		elements[i] -= scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator*(const T& scalar) const {
	std::vector<T> result;
	result.reserve(rows * columns);
	for (len i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] * scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
	for (len i = 0; i < rows * columns; i++) {
		elements[i] *= scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator*(const Matrix<T>& m2) const {
	try {
		if (columns != m2.rows) throw std::invalid_argument("+++ ERROR: column dimension of Matrix A needs to match row dimension of Matrix B +++");
		std::vector<T> result;
		result.reserve(rows * m2.columns);
		for (len i = 0; i < rows; i++) {
			for (len j = 0; j < m2.columns; j++) {
				T m3_value = 0;
				for (len k = 0; k < columns; k++) {
					m3_value += elements[i * columns + k] * m2.elements[k * m2.columns + j];
				}
				result.emplace_back(m3_value);
			}
		}
		return Matrix<T>(rows, m2.columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m2) {
	try {
		if (columns != m2.rows) throw std::invalid_argument("+++ ERROR: column dimension of Matrix A needs to match row dimension of Matrix B +++");
		*this = *this * m2;
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T> Matrix<T>::operator/(const T& scalar) const {
	try {
		if (scalar == 0) throw std::invalid_argument("+++ ERROR: division by zero +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (len i = 0; i < rows * columns; i++) {
			result.emplace_back(elements[i] / scalar);
		}
		return Matrix<T>(rows, columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::operator/=(const T& scalar) {
	try {
		if (scalar == 0) throw std::invalid_argument("+++ ERROR: division by zero +++");
		for (len i = 0; i < rows * columns; i++) {
			elements[i] /= scalar;
		}
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
