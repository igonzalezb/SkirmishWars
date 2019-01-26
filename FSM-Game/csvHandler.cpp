#include "csvHandler.h"


csvFile::csvFile()
{
}

csvFile::csvFile(string fileName, int rows, int cols)
{
	this->fileName = fileName;
	this->rows = rows;
	this->cols = cols;
	matrix = new string*[rows];
	for (int p = 0; p<rows; p++) {
		matrix[p] = new string[cols];
	}

	readFile();
}

void csvFile::readFile()
{
	ifstream lectura;
	lectura.open(fileName, ios::in);
	//matrix2
	if (!lectura.is_open()) std::cout << "ERROR: File Open" << '\n';
	for (int i = 0; (i < rows) && lectura.good(); i++) {
		for (int j = 0; (j < cols) && lectura.good(); j++) {
			if ((j == (cols - 1)) && (i != (rows - 1))) {
				getline(lectura, matrix[i][j], '\n');
				matrix[i][j].erase(matrix[i][j].size() - 1);
				if ((matrix[i][j].find(';') != string::npos) || (matrix[i][j].find(' ') != string::npos))
					matrix[i][j].erase(matrix[i][j].size() - 1);

			}
			else {
				getline(lectura, matrix[i][j], ';');
			}
		}
	}

	lectura.close();
}

string ** csvFile::getMatrix()
{
	return matrix;
}

csvFile::~csvFile()
{
	for (int i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete[] matrix;
}