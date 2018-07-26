#include <iostream>
#include<fstream>
#include <string>

#define FILA 12
#define COLUMNA 16

using namespace std;


int main() {

	ifstream lectura;
	lectura.open("BalancedArena.csv", ios::in);
	string matrix[FILA][COLUMNA];

	if (!lectura.is_open()) std::cout << "ERROR: File Open" << '\n';
	for (int i = 0; (i < FILA) && lectura.good(); i++) {
		for (int j = 0; (j < COLUMNA) &&  lectura.good(); j++) {
			if (j == (COLUMNA-1)){
				getline(lectura, matrix[i][j], '\n');
				matrix[i][j].erase(matrix[i][j].size()-1);
			}
			else {
				getline(lectura, matrix[i][j], ';');
			}
		}
	}
	lectura.close();
	return 0;
}