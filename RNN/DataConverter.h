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
	const len& dataset_size;
	const len& input_dimension;
	const len& output_dimension;
	std::vector<Matrix<double>> labels;
	std::vector<Matrix<double>> values;


public:

	DataConverter(const std::string& path, const len& dataset_size, const len& input_dimension, const len& output_dimension);
	DataConverter(const std::string& path, const len& dataset_size, const len& input_dimension, const len& output_dimension, const len& batch_size);
	const std::vector<Matrix<double>>& data_set;
	const std::vector<Matrix<double>>& label_set;


};

