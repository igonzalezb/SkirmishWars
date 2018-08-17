#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class csvFile
{
public:
	csvFile();
	csvFile(string fileName, int i, int j);
	~csvFile();
	void readFile();
	string** getMatrix();

private:
	string fileName;
	string **matrix;
	int rows;
	int cols;

};
