#include <iostream>
#include<fstream>
#include <string>
#include <cstdio>
#include <ctime>

#define FILA 12
#define COLUMNA 16

void funcion(int matrix [FILA][COLUMNA], bool (&matrix2)[FILA][COLUMNA], int i, int j, int MP);



using namespace std;


int main() {

	/*ifstream lectura;
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
	lectura.close();*/


	int matrix[FILA][COLUMNA];
	bool matrix2[FILA][COLUMNA];

	int i = 5; //[i][j]=posicion de la nave
	int j = 5;
	int n = 3; //n=MP de la nave
	int TMC = 1;
	int count = 0;

	srand(time(NULL));

	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
			matrix[p][q] = rand() % 3 + 1;
			matrix2[p][q] = false;
		}
	}
	matrix[i - 1][j] = 100;
	matrix[i][j] = 0;


	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
			printf("%i||", matrix[p][q]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	funcion(matrix, matrix2, i, j, 3);
	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
			printf("%i||", matrix2[p][q]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	return EXIT_SUCCESS;
}



void funcion(int matrix[FILA][COLUMNA], bool(&matrix2)[FILA][COLUMNA], int i, int j, int MP) {
	if ((i < FILA) && (j < COLUMNA) && (MP >= 0))
	{
		MP -= matrix[i][j];
		if (MP >= 0) {
			matrix2[i][j] = true;
			funcion(matrix, matrix2, i - 1, j, MP);
			funcion(matrix, matrix2, i + 1, j, MP);
			funcion(matrix, matrix2, i, j + 1, MP);
			funcion(matrix, matrix2, i, j - 1, MP);
		}	
	}
}