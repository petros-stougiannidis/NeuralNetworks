//#include "DataConverter.h"
//
//using String = std::string;
//DataConverter::DataConverter(const std::string& path) {
//	this->path = path;
//	std::ifstream file;
//	file.open(path);
//	if (file.is_open()) {
//		String temp_line;
//		String temp_val;
//		std::vector<std::vector<String>> data;
//		std::vector<String> labels;
//		std::vector<String> vals;
//
//		while (file.good()) {
//			std::getline(file, temp_line);
//			std::stringstream sstream(temp_line);
//			String label;
//			std::getline(sstream, label, ',');
//			labels.emplace_back(label);
//			while (sstream.good()) {
//				std::getline(sstream, temp_val, ',');
//				vals.emplace_back(temp_val);
//			}
//			data.emplace_back(vals);
//			/*vals.clear();*/
//		}
//		file.close();
//		labels.pop_back();
//		data.pop_back();
//
//		std::vector<Matrix<double>> erg_data;
//		std::vector<Matrix<double>> erg_labels;
//
//		for (int i = 0; i < data.size(); i++) {
//			std::vector<double> temp;
//			for (int j = 0; j < data[i].size(); j++) {
//				temp.emplace_back(std::stod(data[i][j]));
//			}
//			erg_data.emplace_back(temp);
//		}
//	
//		for (int i = 0; i < labels.size(); i++) {
//			erg_labels.emplace_back(Matrix<double>(10,1).set_value(std::stod(labels[i]), 0, 1));
//		}
//
//
//		this->values = erg_data;
//		this->labels = erg_labels;
//	}
//	else {
//		std::cout << "FAILURE";
//		exit(0);
//	}
//}
//
//const std::vector<Matrix<double>>& DataConverter::get_labels() const {
//	return labels;
//}
//const std::vector<Matrix<double>>& DataConverter::get_values() const {
//	return values;
//}