#include "DataConverter.h"


std::tuple<double, std::vector<double> > labelandInput (const std::string &row) {
	std::string s_label, s_values;
	std::tie(s_label, s_values) = std::make_tuple(row.substr(0,1), row.substr(1, row.length()));

	std::vector<double> values;
	for(char c : s_values) {
		if (c != ',') values.push_back(c - '0');
	}

	double label = 100.0;
	for(char c : s_label) {
		if (c != ',') label = c - '0';
	}

	return std::make_tuple(label,values);
}


std::vector<double> DataConverter::get_labels() const {
	 return labels;
}
std::vector<std::vector< double> > DataConverter::get_values() const {
	return values;
}

DataConverter::DataConverter(const std::string& path, ParseConvention parsing=ParseConvention::LabelandInput) {
	std::ifstream input;
	input.open(path);

	if (!input.is_open()) {
		std::cout << "Could not open!" << std::endl;
		exit(0);
	}

	//Parsing entsprechend der ParsingConvention
	std::string string;
	std::vector<std::string> lines;

	switch (parsing) {
		case ParseConvention::LabelandInput :
			while(std::getline(input, string)) {
				double label;
				std::vector<double> value;
				std::tie(label, value) = labelandInput(string);
				labels.push_back(label);
				values.push_back(value);
			}
			break;
		default:
			labels = {}; //leerer vector
			values = {};
			break;
	}
	input.close();
}
