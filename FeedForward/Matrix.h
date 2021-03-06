﻿#pragma once
#include <iostream>
#include <vector>
#include <random>

#define GENERIC template<typename T>

GENERIC class Matrix {
	static_assert(std::is_arithmetic_v<T>, "+++ ERROR: matrix must contain arithmetic datatype +++\n\n"); //matrix class for arithmetic datatypes (int, float, double etc.)

private:
	int rows;
	int columns;
	std::vector<T> elements;

public:
	//Constructors & Destructor
	Matrix<T>() = default;
	Matrix<T>(const int& rows, const int& columns); //construct Matrix and fill with 0
	Matrix<T>(const int& rows, const int& columns, const T& value); //construct Matrix and fill with start value
	Matrix<T>(const int& rows, const int& columns, const std::vector<T>& vector); //construct Matrix out of existing Vector by copying
	Matrix<T>(const int& rows, const int& columns, std::vector<T>&& to_be_moved); //construct Matrix out of existing Vector without copying and leaving the vector as hollow object
	~Matrix() = default;

	//Move & Copy Konstruktoren
	Matrix<T>(const Matrix<T>& to_be_copied);
	Matrix<T>(Matrix<T>&& to_be_moved);

	//Copy & Move Assignment
	Matrix<T>& operator=(const Matrix<T>& m2);
	Matrix<T>& operator=(Matrix<T>&& m2);

	//Getter & Setter
	int get_rows() const;
	int get_columns() const;
	T get_value(const int& row, const int& column) const;
	Matrix<T>& set_value(const int& row, const int& column, const T& value);

	//Operators
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

	//Functions
	void print() const;
	Matrix<T> transpose() const;
	Matrix<T> unit_matrix(const int& dimension) const;
	Matrix<T>& map(T function(const T&));
	Matrix<T>& iota();
	Matrix<T>& iota(const T& start);
	Matrix<T>& randomize(const T& min, const T& max);
	Matrix<T> hadamard(const Matrix<T>& m2);
	std::vector<int> argmax_batch() const;
	Matrix<T> mul(const Matrix<T>& m2) const;
	Matrix<T> column_concat(const Matrix& m2) const;
	Matrix<T> column_concat(const std::vector<Matrix<T>>& batch, const int& batch_size, const int& start) const;
	
};
//////////////////////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTORS   ///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


GENERIC Matrix<T>::Matrix(const int& rows, const int& columns)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	this->elements = std::move(std::vector<T>(rows * columns));
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const int& rows, const int& columns, const T& value)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	this->elements = std::move(std::vector<T>(rows * columns, value));
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const int& rows, const int& columns, const std::vector<T>& vector)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	if (rows * columns != vector.size()) throw std::invalid_argument("+++ ERROR: dimensions dont match vector length +++");
	this->elements = vector;
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}
GENERIC Matrix<T>::Matrix(const int& rows, const int& columns, std::vector<T>&& to_be_moved)
try : rows(rows), columns(columns) {
	if (rows < 1 || columns < 1) throw std::invalid_argument("+++ ERROR: invalid dimensions +++");
	if (rows * columns != to_be_moved.size()) throw std::invalid_argument("+++ ERROR: dimensions dont match vector length +++");
	this->elements = std::move(to_be_moved);
}
catch (std::invalid_argument& error) {
	std::cerr << error.what() << std::endl;
}

GENERIC Matrix<T>::Matrix(const Matrix<T>& to_be_copied)
	: rows(to_be_copied.rows), columns(to_be_copied.columns), elements(std::vector<T>(to_be_copied.elements)) {
}
GENERIC Matrix<T>::Matrix(Matrix<T>&& to_be_moved)
	: rows(std::move(to_be_moved.rows)), columns(std::move(to_be_moved.columns)), elements(std::move(to_be_moved.elements)) {
}
GENERIC Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m2) {
	rows = m2.rows;
	columns = m2.columns;
	elements = m2.elements;
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::operator=(Matrix<T>&& m2) {
	rows = std::move(m2.rows);
	columns = std::move(m2.columns);
	elements = std::move(m2.elements);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  GETTER & SETTER  /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC int Matrix<T>::get_rows() const {
	return rows;
}
GENERIC int Matrix<T>::get_columns() const {
	return columns;
}
GENERIC T Matrix<T>::get_value(const int& row, const int& column) const {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		return elements.at(row * columns + column);
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC Matrix<T>& Matrix<T>::set_value(const int& row, const int& column, const T& value) {
	try {
		if (row >= rows || column >= columns) throw std::out_of_range("+++ ERROR: Index out of bounds +++");
		elements[row * columns + column] = value;
	}
	catch (std::out_of_range& error) {
		std::cerr << error.what() << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  FUNCTIONS   //////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

GENERIC void Matrix<T>::print() const {
	if (!elements.empty()) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			transposed.elements[j * transposed.columns + i] = this->elements[i * columns + j];
		}
	}
	return transposed;
}
GENERIC Matrix<T> Matrix<T>::unit_matrix(const int& dimension) const {
	std::vector<T> result;
	result.reserve(dimension * dimension);
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
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
GENERIC Matrix<T>& Matrix<T>::map(T function(const T&)) { 
	for (int i = 0; i < rows * columns; i++) {
		elements[i] = function(elements[i]);
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::iota() {
	T value = 0;
	for (int i = 0; i < rows * columns; i++) {
		elements[i] = value++;
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::iota(const T& start) {
	T value = start;
	for (int i = 0; i < rows * columns; i++) {
		elements[i] = value++;
	}
	return *this;
}
GENERIC Matrix<T>& Matrix<T>::randomize(const T& min, const T& max) {
	std::random_device rd;
	std::mt19937 seed(rd());
	if(typeid(T) == typeid(float)){
		std::uniform_real_distribution<float> dist(min, max);
		for (int i = 0; i < rows * columns; i++) {
			elements[i] = (T)dist(seed);
			while (elements[i] == 0) {
				elements[i] = (T)dist(seed);
			}
		}
		return *this;
	}
	else if (typeid(T) == typeid(double)) {
		std::uniform_real_distribution<double> dist(min, max);
		for (int i = 0; i < rows * columns; i++) {
			elements[i] = (T)dist(seed);
			while (elements[i] == 0) {
				elements[i] = (T)dist(seed);
			}
		}
		return *this;
	}
	else if (typeid(T) == typeid(int)) {
		std::uniform_int_distribution<int> dist(min, max);
		for (int i = 0; i < rows * columns; i++) {
			elements[i] = (T)dist(seed);
		}
		return *this;
	}
	
}
GENERIC Matrix<T> Matrix<T>::hadamard(const Matrix<T>& m2) {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (int i = 0; i < rows * columns; i++) {
			result.emplace_back(elements[i] * m2.elements[i]);
		}
		return Matrix<T>(rows, columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
GENERIC std::vector<int> Matrix<T>::argmax_batch() const { // PROTOTYPE
	if (columns == 1) {
		int current_max_position = 0;
		float current_max_element = elements[0];
		for (int i = 1; i < rows * columns; i++) {
			if (elements[i] > current_max_element) {
				current_max_position = i;
				current_max_element = elements[i];
			}
		}
		std::vector<int> result;
		result.push_back(current_max_position);
		return result;
	}
	else {
		std::vector<int> result;
		result.reserve(columns);
		for (int j = 0; j < columns; j++) {
			int current_max_position = 0;
			float current_max_element = elements[0 * columns + j];
			for (int i = 1; i < rows; i++) {
				if (elements[i * columns + j] > current_max_element) {
					current_max_position = i;
					current_max_element = elements[i * columns + j];
				}
			}
			result.push_back(current_max_position);
		}
		return result;
	}

}
GENERIC Matrix<T> Matrix<T>::column_concat(const Matrix& m2) const {
	try {
		if (rows != m2.rows) throw std::invalid_argument("row number doesnt match");

		std::vector<T> result;
		result.reserve(rows * columns + m2.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				result.emplace_back(this->elements[i * columns + j]);
			}
			for (int j = 0; j < m2.columns; j++) {
				result.emplace_back(m2(i, j));
			}
		}
		return Matrix<T>(rows, columns + m2.columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what();
	}
}

GENERIC Matrix<T> Matrix<T>::column_concat(const std::vector<Matrix<T>>& batch, const int& batch_size, const int& start) const { // make static
	try {
		int rows_of_first = batch[start].get_rows();
		int all_columns = 0;
		for (int i = 0; i < batch_size; i++) {
			all_columns += batch[start + i].get_columns();
			if (batch[start + i].get_rows() != rows_of_first) throw std::invalid_argument("+++ ERROR: row numbers need to match for all Matrices +++");
		}
		std::vector<T> result;
		result.reserve(rows_of_first * all_columns);
		for (int i = 0; i < rows_of_first; i++) {
			for (int j = 0; j < batch_size; j++) {
				for (int k = 0; k < batch[start + j].get_columns(); k++) {
					result.emplace_back(batch[start + j](i, k));
				}
			}
		}
		return Matrix<T>(rows_of_first, all_columns, std::move(result));
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  OPERATORS   //////////////////////////////////////////////////////////////////////////////
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
	for (int i = 0; i < rows * columns; i++) {
		result.emplace_back(-elements[i]);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T> Matrix<T>::operator+(const Matrix<T>& m2) const {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (int i = 0; i < rows * columns; i++) {
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
		for (int i = 0; i < rows * columns; i++) {
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
	for (int i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] + scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator+=(const T& scalar) {
	for (int i = 0; i < rows * columns; i++) {
		elements[i] += scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator-(const Matrix<T>& m2) const {
	try {
		if (rows != m2.rows || columns != m2.columns) throw std::invalid_argument("+++ ERROR: Matrices need to have the same dimensions +++");
		std::vector<T> result;
		result.reserve(rows * columns);
		for (int i = 0; i < rows * columns; i++) {
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
		for (int i = 0; i < rows * columns; i++) {
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
	for (int i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] - scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator-=(const T& scalar) {
	for (int i = 0; i < rows * columns; i++) {
		elements[i] -= scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator*(const T& scalar) const {
	std::vector<T> result;
	result.reserve(rows * columns);
	for (int i = 0; i < rows * columns; i++) {
		result.emplace_back(elements[i] * scalar);
	}
	return Matrix<T>(rows, columns, std::move(result));
}
GENERIC Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
	for (int i = 0; i < rows * columns; i++) {
		elements[i] *= scalar;
	}
	return *this;
}
GENERIC Matrix<T> Matrix<T>::operator*(const Matrix<T>& m2) const {
	try {
		if (columns != m2.rows) throw std::invalid_argument("+++ ERROR: column dimension of Matrix A needs to match row dimension of Matrix B +++");
		std::vector<T> result;
		result.reserve(rows * m2.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < m2.columns; j++) {
				T m3_value = 0;
				for (int k = 0; k < columns; k++) {
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
		for (int i = 0; i < rows * columns; i++) {
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
		for (int i = 0; i < rows * columns; i++) {
			elements[i] /= scalar;
		}
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
