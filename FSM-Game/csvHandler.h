#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class csvFile
{
public:
	csvFile();
	csvFile(string fileName, int rows, int cols);
	~csvFile();
	void readFile();
	string** getMatrix();

private:
	string fileName;
	string **matrix;
	int rows;
	int cols;

};
