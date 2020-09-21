#include "DataConverter.h"

//////////////////////////////////////////////////////////////////////////////////////////////
// Klasse: DataConverter																	//
// Bereitet Datensätze und/oder andere externe Date0 für eine Verarbeitung in einem neuro-  //
// nalen Netzvor.																			//
// TODO::	- Funktion zum Einlesen von Daten												//
//			- Funktionen zum Formatieren der Daten (Verktor mit Input, Vektor mit Labels)	//
//			- Funktion zum Exportieren der Daten											//		
//////////////////////////////////////////////////////////////////////////////////////////////

DataConverter::DataConverter(const std::string& path) : path(path) {}
std::vector<std::string> DataConverter::read_csv() const {
	//try {
	//	std::ifstream input;
	//	input.open(path);
	//	if (!input.is_open()) {
	//		throw std::invalid_argument("Datei konnte nicht geoeffnet werden");
	//	}
	//	else {
	//		std::string string;
	//		std::vector<std::string> lines;
	//		while (std::getline(input, string)) {
	//			lines.push_back(string);
	//		}
	//		input.close();
	//		return lines;
	//	}
	//}
	//catch (std::invalid_argument& error) {
	//	std::cerr << error.what() << std::endl;
	//}
	
}