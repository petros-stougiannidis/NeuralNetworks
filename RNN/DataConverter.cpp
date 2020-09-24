#include "DataConverter.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// Klasse: DataConverter																	//
// Bereitet Datens�tze und/oder andere externe Date0 f�r eine Verarbeitung in einem neuro-  //
// nalen Netzvor.																			//
// TODO::	- Funktion zum Einlesen von Daten												//
//			- Funktionen zum Formatieren der Daten (Vektor mit Input, Vektor mit Labels)	//
//			- Funktion zum Exportieren der Daten											//		
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum: ParseConvention																										//
// Für vereinfachte Auswahl von verschiedenen Zeilen-Parser-Funktionen; beliebig erweiterba										//	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class ParseConvention {
	WholeRows, //default: liest die ganze Reihe ein
	LabelandInput //Label und Input getrennt
};

DataConverter::DataConverter(const std::string& path) : path(path) {}

//liest Label und Input jeweils getrennt ein -> Form: [label, input]
std::tuple<std::string, std::string> labelandInput (const std::string &row) {
	return std::make_tuple(row.substr(0,1), row.substr(2, row.length()));
}

//liest ganze Zeile ein
std::string wholeRows (const std::string &row) {
	return row;
}

//Modularisierte Haupt-Parsing Funktion. Abhängig von ParseConvention erhält man verschieden geparste Zeilen zurück.
std::vector<std::string> DataConverter::read_csv() const {
	ParseConvention parsing=ParseConvention::LabelandInput; //TODO: ParseConvention als Paramter für read_csv()
	//Einlesen des Files
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
		case ParseConvention::WholeRows :
				while(std::getline(input, string)) {
				auto fields = wholeRows(string);
				lines.push_back(fields);
			}
			break;
		case ParseConvention::LabelandInput :
			while(std::getline(input, string)) {
				std::string label, value;
				std::tie(label, value) = labelandInput(string);
				lines.push_back(label);
				lines.push_back(value);
			}
			break;
		default:
			lines = {""}; //leerer String
	}

	
	input.close();
	return lines;	
}