#include "DataConverter.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum: ParseConvention																										//
// Für vereinfachte Auswahl von verschiedenen Zeilen-Parser-Funktionen; beliebig erweiterba										//	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Hey Max, hab die zwei Funktionen in der Headerdatei definiert, get_labels() und get_values(). Da das Einlesen der Datensätze tatsächlich
etwas länger dauert, dachte ich mir wir programmieren diese Klasse so, dass input.open(path) im Konstruktor aufgerufen wird, dort geparsed
und die Vektoren dann in zwei Klassenvariablen abgespeichert werden (diese hab ich auch schon in der Headerdatei deklariert). Dadurch sparen
wir uns, dass input.open(path) zwei mal aufgerufen werden muss.

 - std::vector<double> labels
 - std::vector < std::vector<double> values

Die Funktionen get_labels() und get_values() müssen dann nur gewöhnliche Getter sein.

std::vector<std::string> DataConverter::get_labels() const {
	 return labels;
}
std::vector<std::string> DataConverter::get_values() const {
	return values;
}

Falls dann in Zukunft andere Formate von Datensätzen dazukommen, können wir einfach einen weiteren Konstruktor dazu definieren, der 
dann dementsprechend parsed. Oder man übergibt dem Konstruktor eine Flag, die dann entscheidet wie geparsed werden soll (also so 
wie du es bisher gemacht hast nur im Konstruktor).

Zum Format das wir jetzt brauchen:

std::vector<double> labels enthält in jedem Vektorelement das erste Element jeder Zeile
std::vector<std::vector< double>> values enthält in jedem Vektorelement eine ganze Zeile, nur ohne das erste Element, also das Label
und ohne die Kommata.

Beispiel : Bei folgenden Zeilen aus dem Datensatz

7, 0, 0, 0, 0, 343, 56, 0, 0, 0, 345, 4353
5, 0, 0, 0, 2, 4, 5, 6, 0, 0, 0, 3, 4, 5, 6
1, 0, 0, 0, 4, 0, 5, 7, 8, 8, 0, 0, 3, 3

Dann ist labels = { 7,5,1... };
und values = { {0,0,0,0,343,56,0,0,0,345,4353},
				{0,0,0,2,4,5,6,0,0,0,3,4,5,6},
				{0,0,0,4,0,5,7,8,8,0,0,3,3}... };





//enum class ParseConvention {
//	WholeRows, //default: liest die ganze Reihe ein
//	LabelandInput //Label und Input getrennt
//};
//
//DataConverter::DataConverter(const std::string& path) : path(path) {}
//
////liest Label und Input jeweils getrennt ein -> Form: [label, input]
//std::tuple<std::string, std::string> labelandInput (const std::string &row) {
//	return std::make_tuple(row.substr(0,1), row.substr(2, row.length()));
//}
//
////liest ganze Zeile ein
//std::string wholeRows (const std::string &row) {
//	return row;
//}





////Modularisierte Haupt-Parsing Funktion. Abhängig von ParseConvention erhält man verschieden geparste Zeilen zurück.
//std::vector<std::string> DataConverter::read_csv() const {
//	ParseConvention parsing=ParseConvention::LabelandInput; //TODO: ParseConvention als Paramter für read_csv()
//	//Einlesen des Files
//	std::ifstream input;
//	input.open(path);
//
//	if (!input.is_open()) {
//		std::cout << "Could not open!" << std::endl;
//		exit(0);
//	}
//
//	//Parsing entsprechend der ParsingConvention
//	std::string string;
//	std::vector<std::string> lines;
//
//	switch (parsing) {
//		case ParseConvention::WholeRows :
//				while(std::getline(input, string)) {
//				auto fields = wholeRows(string);
//				lines.push_back(fields);
//			}
//			break;
//		case ParseConvention::LabelandInput :
//			while(std::getline(input, string)) {
//				std::string label, value;
//				std::tie(label, value) = labelandInput(string);
//				lines.push_back(label);
//				lines.push_back(value);
//			}
//			break;
//		default:
//			lines = {""}; //leerer String
//	}
//
//	
//	input.close();
//	return lines;	
//}