#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <tuple>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum: ParseConvention																										//
// Für vereinfachte Auswahl von verschiedenen Zeilen-Parser-Funktionen; beliebig erweiterba										//	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class ParseConvention {
	LabelandInput //Label und Input getrennt
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Klasse: DataConverter																	//
// Bereitet Datens�tze und/oder andere externe Date0 f�r eine Verarbeitung in einem neuro-  //
// nalen Netzvor.																			//
// TODO::	- Funktion zum Einlesen von Daten												//
//			- Funktionen zum Formatieren der Daten (Verktor mit Input, Vektor mit Labels)	//
//			- Funktion zum Exportieren der Daten											//		
//////////////////////////////////////////////////////////////////////////////////////////////
class DataConverter
{
public:
	DataConverter(const std::string& path, ParseConvention);
	std::vector<double> get_labels() const;
	std::vector<std::vector< double>> get_values() const;
private:
	std::string path;
	std::vector<double> labels;
	std::vector<std::vector<double>> values;
	
};

