#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <exception>
#include <random>
#include <typeinfo>

template<typename T>
class Matrix
{
	static_assert(std::is_arithmetic_v<T>, "Unzulaessiger Typ fuer die Matrixinstanz\n");
public:
	//Konstruktoren
	Matrix<T>(const std::vector<std::vector<T>>& matrix);
	Matrix<T>(const size_t& row, const size_t& col);
	Matrix<T>(const size_t& row, const size_t& col, const T& val);
	//Funktionen auf Matrizen
	void print() const;
	Matrix<T> transpose() const;
	Matrix<T>& map(T function (T&));
	Matrix<T>& randomize_int(int min, int max);
	Matrix<T>& randomize_double(double min, double max);
	//Getter
	size_t get_rowdim() const;
	size_t get_coldim() const;
	T get_value(const size_t& row, const size_t& col) const;
	//Setter
	Matrix<T>& set_value(const size_t& row, const size_t& col, const T& val);
	//Operatoren
	bool operator==(const Matrix<T>& m2);
	Matrix<T>& operator=(const Matrix<T>& m2);
	T operator()(const size_t& row, const size_t& col);
	Matrix<T>& operator()(const size_t& row, const size_t& col, const T& val);
	Matrix<T> operator+(const Matrix<T>& m2);
	Matrix<T>& operator+=(const Matrix<T>& m2);
	Matrix<T> operator+(const T& scalar);
	Matrix<T>& operator+=(const T& scalar);
	Matrix<T> operator-(const Matrix<T>& m2);
	Matrix<T>& operator-=(const Matrix<T>& m2);
	Matrix<T> operator-(const T& scalar);
	Matrix<T>& operator-=(const T& scalar);
	Matrix<T> operator*(const T& scalar);
	Matrix<T>& operator*=(const T& scalar);
	Matrix<T> operator*(const Matrix<T>& m2);
	Matrix<T>& operator*=(const Matrix<T>& m2);
	Matrix<T> operator/(const T& scalar);
	Matrix<T>& operator/=(const T& scalar);

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
Matrix<T>::Matrix(const size_t& row, const size_t& col) : rowdim(row), coldim(col), matrix(std::vector<std::vector<T>>(row, std::vector<T>(col))) {}
template<typename T>
Matrix<T>::Matrix(const size_t& row, const size_t& col, const T& val) : rowdim(row), coldim(col), matrix(std::vector<std::vector<T>>(row, std::vector<T>(col, val))) {}

/********************************************************************************************/
/*                                       FUNKTIONEN                                         */
/********************************************************************************************/

// TODO: PROBLEM BEHEBEN BEI R_VALUE-EXCEPTION
template<typename T>
void Matrix<T>::print() const {
	try {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	catch (std::exception &error) {
		std::cerr << error.what() << std::endl;
	}
	
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
template<typename T>
Matrix<T>& Matrix<T>::map(T function (T&)) {  // :: a -> a
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),				//from
			matrix[i].end(),				//to
			matrix[i].begin(),				//in
			function);						//with
	}
	return *this;
}
Matrix<int>& Matrix<int>::randomize_int(int min, int max) {
	std::random_device rd;
	std::mt19937 seed(rd());
	std::uniform_int_distribution<int> dist(min, max);
	for (int i = 0; i < rowdim; i++) {
		for (int j = 0; j < coldim; j++) {
			matrix[i][j] = dist(seed);
		}
		
	}
	return *this;
}

Matrix<double>& Matrix<double>::randomize_double(double min, double max) {
	std::random_device rd;
	std::mt19937 seed(rd());
	std::uniform_real_distribution<double> dist(min, max);
	for (int i = 0; i < rowdim; i++) {
		for (int j = 0; j < coldim; j++) {
			matrix[i][j] = dist(seed);
		}

	}
	return *this;
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
Matrix<T>& Matrix<T>::set_value(const size_t& row, const size_t& col, const T& val) {
	try {
		matrix.at(row).at(col) = val;
		return *this;
	}
	catch (std::exception &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
T Matrix<T>::get_value(const size_t& row, const size_t& col) const {
	try {
		return matrix.at(row).at(col);
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
}


/********************************************************************************************/
/*                                       OPERATOREN                                         */
/********************************************************************************************/

// TODO: PROBLEM BEHEBEN BEI R_VALUE-EXCEPTION
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
T Matrix<T>::operator()(const size_t& row, const size_t& col) {
	try {
		return matrix.at(row).at(col);
	}
	catch (std::exception& error) {
		std::cerr << error.what() << std::endl;
	}
}
// TODO: mit at(); probieren
template<typename T>
Matrix<T>& Matrix<T>::operator()(const size_t& row, const size_t& col, const T& val) { 
	try {
		if (rowdim <= row || coldim <= col) throw std::out_of_range("Index ueberschreitet Matrixdimension\n");
		matrix[row][col] = val;
		return *this;
	}
	catch(std::out_of_range &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m2) {
	try {
		if (rowdim != m2.rowdim || coldim != m2.coldim) throw std::invalid_argument("Matrixdimensionen muessen uebereinstimmen\n");
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
	catch(std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m2) {
	try {
		if (rowdim != m2.rowdim || coldim != m2.coldim) throw std::invalid_argument("Matrixdimensionen muessen uebereinstimmen\n");
		*this = *this + m2;
		return *this;
	}
	catch (std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const T& scalar) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			result.matrix[i].begin(),						//in
			[scalar](T value) {return value + scalar; });	//with
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T& scalar) {
	*this = *this + scalar;
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m2) {
	try {
		if (rowdim != m2.rowdim || coldim != m2.coldim) throw std::invalid_argument("Matrixdimensionen muessen uebereinstimmen\n");
		Matrix<T> result(get_rowdim(), get_coldim());
		for (int i = 0; i < get_rowdim(); i++) {
			std::transform(
				matrix[i].begin(),			//from
				matrix[i].end(),			//to
				m2.matrix[i].begin(),		//and
				result.matrix[i].begin(),	//in
				std::minus<T>());			//with
		}
		return result;
	} catch (std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m2) {
	try {
		if (rowdim != m2.rowdim || coldim != m2.coldim) throw std::invalid_argument("Matrixdimensionen muessen uebereinstimmen\n");
		*this = *this - m2;
		return *this;
	}
	catch (std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const T& scalar) {
	Matrix<T> result(get_rowdim(), get_coldim());
	for (int i = 0; i < get_rowdim(); i++) {
		std::transform(
			matrix[i].begin(),								//from
			matrix[i].end(),								//to
			result.matrix[i].begin(),						//in
			[scalar](T value) {return value - scalar; });	//with
	}
	return result;
}
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const T& scalar) {
	*this = *this - scalar;
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
	*this = *this * scalar;
	return *this;
}
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m2) {
	try {
		if (coldim != m2.rowdim) throw std::invalid_argument("Spaltendimension der ersten Matrix stimmt nicht mit der Zeilendimension der zweiten Matrix �berein.\n");
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
	catch (std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m2) {
	try {
		if (coldim != m2.rowdim) throw std::invalid_argument("Spaltendimension der ersten Matrix stimmt nicht mit der Zeilendimension der zweiten Matrix ueberein.\n");
		*this = (*this) * m2;
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator/(const T& scalar) {
	try {
		if (scalar == 0) throw std::invalid_argument("Division durch 0\n");
		Matrix<T> result(get_rowdim(), get_coldim());
		for (int i = 0; i < get_rowdim(); i++) {
			std::transform(
				matrix[i].begin(),								//from
				matrix[i].end(),								//to
				result.matrix[i].begin(),						//in
				[scalar](T value) {return value / scalar; });	//with
		}
		return result;	
	}
	catch (std::invalid_argument &error) {
		std::cerr << error.what() << std::endl;
	}
}
template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T& scalar) {
	try {
		if (scalar == 0) throw std::invalid_argument("Division durch 0\n");
		*this = *this / scalar;
		return *this;
	}
	catch (std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
}
