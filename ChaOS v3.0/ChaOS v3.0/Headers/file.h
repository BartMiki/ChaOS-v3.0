﻿#ifndef FILE__H
#define FILE__H
#include <string>
// Klasa file reprezentuje plik na ktorym pracuje OS.
// 
// 1. Wpisywanie do pliku (podany obiekt string)
// 2. Odczytywanie pliku (zwracany obiekt string)

using uShort = unsigned short;

class file final
{
	friend class ChaOS_filesystem;
public:
	file();
	uShort getID();
	~file();
	//void write(const std::string& text);
	//std::string read();
	//void append(const std::string& text);

private:
	std::string fileContent;
	char filename[5];
	unsigned int fileSize;
	uShort fileSizeInSectors;
	uShort firstSector;
	uShort fileDir;
};

#endif FILE__H