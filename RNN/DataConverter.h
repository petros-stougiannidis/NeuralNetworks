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
public:
	DataConverter(const std::string& path);
	const std::vector<Matrix<double>>& get_labels() const;
	const std::vector<Matrix<double>>& get_values() const;
private:
	std::string path;
	std::vector<Matrix<double>> labels;
	std::vector<Matrix<double>> values;
};

