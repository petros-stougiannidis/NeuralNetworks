#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>

template<typename T>
class Matrix
{
	static_assert(std::is_arithmetic_v<T>, "Unzulässiger Typ für die Matrixinstanz");
public:
	//Konstruktoren
	Matrix<T>(const std::vector<std::vector<T>>& matrix);
	Matrix<T>(const unsigned int& row, const unsigned int& col);
	Matrix<T>(const unsigned int& row, const unsigned int& col, const T& val);
	//Funktionen auf Matrizen
	void print() const;
	Matrix<T> transpose() const;
	//Getter
	size_t get_rowdim() const;
	size_t get_coldim() const;
	T get_value(const unsigned int& row, const unsigned int& col) const;
	//Setter
	Matrix<T>& set_value(const unsigned int& row, const unsigned int& col, const T& val);
	//Operatoren
	bool operator==(const Matrix<T>& m2);
	Matrix<T>& operator=(const Matrix<T>& m2);
	T operator()(const unsigned int& row, const unsigned int& col);
	Matrix<T>& operator()(const unsigned int& row, const unsigned int& col, const T& val);
	Matrix<T> operator+(const Matrix<T>& m2);
	Matrix<T>& operator+=(const Matrix<T>& m2);
	Matrix<T> operator-(const Matrix<T>& m2);
	Matrix<T>& operator-=(const Matrix<T>& m2);
	Matrix<T> operator*(const T& scalar);
	Matrix<T>& operator*=(const T& scalar);
	Matrix<T> operator*(const Matrix<T>& m2);
	Matrix<T>& operator*=(const Matrix<T>& m2);
	/*Matrix<T> operator/(const Matrix<T>& m2);
	Matrix<T>& operator/=(const Matrix<T>& m2);*/



private:
	size_t rowdim;
	size_t coldim;
	std::vector<std::vector<T>> matrix;
};

/********************************************************************************************/
/*                               KONSTRUKTOR/DESTRUKTOR                                     */
/********************************************************************************************/

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec) : rowdim(vec.size()), coldim(rowdim > 0 ? vec[0].size() : 0), matrix(vec) {
	for (int i = 0; i < rowdim; i++) {
		for (int j = 0; j < coldim; j++) {
			matrix[i][j] = vec[i][j];
		}
	}
}
template<typename T>
Matrix<T>::Matrix(const unsigned int& row, const unsigned int& col) : rowdim(row), coldim(col), matrix(std::vector<std::vector<T>>(row, std::vector<T>(col))) {}
template<typename T>
Matrix<T>::Matrix(const unsigned int& row, const unsigned int& col, const T& val) : rowdim(row), coldim(col), matrix(std::vector<std::vector<T>>(row, std::vector<T>(col, val))) {}

/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/

template<typename T>
void Matrix<T>::print() const {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
template<typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> result(get_coldim(), get_rowdim(), 0);
	for (int i = 0; i < get_rowdim(); i++) {
		for (int j = 0; j < get_coldim(); j++) {
			result.set_value(j, i, matrix[i][j]);
		}
	}
	return result;
}



/********************************************************************************************/
/*                                       GETTER & SETTER                                    */
/********************************************************************************************/

template<typename T>
size_t Matrix<T>::get_rowdim() const {
	return matrix.size();
}
template<typename T>
size_t Matrix<T>::get_coldim() const {
	return matrix[0].size();
}
template<typename T>
Matrix<T>& Matrix<T>::set_value(const unsigned int& row, const unsigned int& col, const T& val) {
	matrix[row][col] = val;
	return *this;
}
template<typename T>
T Matrix<T>::get_value(const unsigned int& row, const unsigned int& col) const {
	return matrix[row][col];
}


/********************************************************************************************/
/*                                       OPERATOREN                                         */
/********************************************************************************************/

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m2) {
	this->rowdim = m2.get_rowdim();
	this->coldim = m2.get_coldim();
	this->matrix = m2.matrix;
	return *this;
}
template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& m2) {
	return matrix == m2.matrix;
}
template<typename T>
T Matrix<T>::operator()(const unsigned int& row, const unsigned int& col) {
	return matrix[row][col];
}
template<typename T>
Matrix<T>& Matrix<T>::operator()(const unsigned int& row, const unsigned int& col, const T& val) {
	matrix[row][col] = val;
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m2) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),				//from
			matrix[i].end(),				//to
			m2.matrix[i].begin(),			//and
			result.matrix[i].begin(),		//in
			std::plus<T>());				//with
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m2) {
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			m2.matrix[i].begin(),							//and
			matrix[i].begin(),								//in
			std::plus<T>());	//with
	}
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m2) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),			//from
			matrix[i].end(),				//to
			m2.matrix[i].begin(),		//and
			result.matrix[i].begin(),	//in
			std::minus<T>());				//with
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m2) {
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			m2.matrix[i].begin(),							//and
			matrix[i].begin(),								//in
			std::minus<T>());								//with
	}
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			result.matrix[i].begin(),						//in
			[scalar](T value) {return value * scalar; });	//with
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			matrix[i].begin(),								//in
			[scalar](T value) {return value * scalar; });	//with
	}
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m2) {
	Matrix<T> result(get_rowdim(), m2.get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		for (int j = 0; j < m2.get_coldim(); j++) {
			for (int k = 0; k < get_coldim(); k++) {
				result.matrix[i][j] += this->matrix[i][k] * m2.matrix[k][j];
			}
		}
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m2) {
	*this = (*this) * m2;
	return *this;
}
/*template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& m2) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		for (int j = 0; j < get_coldim(); j++) {
			result.matrix[i][j] = matrix[i][j] + m2.matrix[i][j];
		}
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& m2) {
	for (int i = 0; i < get_rowdim(); i++) {
		for (int j = 0; j < get_coldim(); j++) {
			matrix[i][j] += m2.matrix[i][j];
		}
	}
	return *this;
} */