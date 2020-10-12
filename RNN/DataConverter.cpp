#include "DataConverter.h"
#include "Timer.h"
#include "PercentageBar.h"

using String = std::string;
DataConverter::DataConverter(const std::string& path, const len& dataset_size, const len& input_dimension, const len& output_dimension) 
	:	path(path), 
		dataset_size(dataset_size),
		input_dimension(input_dimension),
		output_dimension(output_dimension){

	std::cout << "reading " << path << std::endl;
	Timer timer;
	std::ifstream file;
	file.open(path);
	if (file.is_open()) {

		int iteration = 0;
		PercentageBar percentage_bar;
		labels.reserve(dataset_size);
		values.reserve(dataset_size);

		String current_line;
		String current_data_point;

		std::vector<double> data_points;
		data_points.reserve(input_dimension);
		
		while (std::getline(file, current_line, '\n')) { 
			std::stringstream sstream(current_line);
			String label;
			std::getline(sstream, label, ','); 
			this->labels.emplace_back(output_dimension,1, 0.01);
			this->labels.back().set_value(std::stod(label), 0, 0.99);
			while (std::getline(sstream, current_data_point, ',')) { 
				data_points.emplace_back(std::stod(current_data_point)/255*0.99+0.01); 
			}
			this->values.emplace_back(input_dimension, 1, std::move(data_points));
			data_points.clear();
			percentage_bar.print_progress(iteration, dataset_size);
			iteration++;
		}
		file.close();
		timer.print_time<s>();
	}
	else {
		std::cout << "FAILED TO READ FILE";
		exit(0);
	}
}

DataConverter::DataConverter(const std::string& path, const len& dataset_size, const len& input_dimension, const len& output_dimension, const len& batch_size)
	: path(path),
	dataset_size(dataset_size),
	input_dimension(input_dimension),
	output_dimension(output_dimension) {

	std::cout << "reading " << path << std::endl;
	Timer timer;
	std::ifstream file;
	file.open(path);
	if (file.is_open()) {
		int iteration = 0;
		PercentageBar percentage_bar;

		labels.reserve(dataset_size);
		values.reserve(dataset_size);

		String current_line;
		String current_data_point;
		
		std::vector<double> data_points;
		data_points.reserve(input_dimension);

		while (std::getline(file, current_line, '\n')) {
			std::stringstream sstream(current_line);
			String label;
			std::getline(sstream, label, ',');
			this->labels.emplace_back(output_dimension, 1, 0.01);
			this->labels.back().set_value(std::stod(label), 0, 0.99);
			while (std::getline(sstream, current_data_point, ',')) {
				data_points.emplace_back(std::stod(current_data_point) / 255 * 0.99 + 0.01);
			}
			this->values.emplace_back(input_dimension, 1, std::move(data_points));
			data_points.clear();
			percentage_bar.print_progress(iteration, dataset_size);
			iteration++;
		}

		//////// BATCH
		Matrix<double> e;
		std::vector<Matrix<double>> batched_values;
		std::vector<Matrix<double>> batched_labels;
		batched_values.reserve(dataset_size / batch_size);
		batched_labels.reserve(dataset_size / batch_size);

		for (len i = 0; i < dataset_size / batch_size; i++) {
			batched_values.emplace_back(e.column_concat(this->values, batch_size, i * batch_size));
			batched_labels.emplace_back(e.column_concat(this->labels, batch_size, i * batch_size));
		}

		this->values = std::move(batched_values);
		this->labels = std::move(batched_labels);

		file.close();
		timer.print_time<s>();
	}
	else {
		std::cout << "FAILED TO READ FILE";
		exit(0);
	}
}

const std::vector<Matrix<double>>& DataConverter::get_labels() const {
	return labels;
}
const std::vector<Matrix<double>>& DataConverter::get_values() const {
	return values;
}

