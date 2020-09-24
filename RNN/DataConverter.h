#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <tuple>

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
	DataConverter(const std::string& path);
	std::vector<std::string> read_csv() const;
private:
	std::string path;
	
};

