#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include "Matrix.h"

class DataConverter
{
private:

	const std::string path;
	const int& dataset_size;
	const int& input_dimension;
	const int& output_dimension;
	const int& batch_size;
	std::vector<Matrix<float>> labels;
	std::vector<Matrix<float>> values;


public:

	DataConverter(const std::string& path, const int& dataset_size, const int& input_dimension, const int& output_dimension);
	DataConverter(const std::string& path, const int& dataset_size, const int& input_dimension, const int& output_dimension, const int& batch_size);
	const std::vector<Matrix<float>>& data_set;
	const std::vector<Matrix<float>>& label_set;


};

