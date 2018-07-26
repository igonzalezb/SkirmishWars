#include "Map.h"

using namespace std;

Map::Map(string mapName)
{
	this->mapName = mapName;
}

void Map::csvReader()
{
	ifstream lectura;
	lectura.open(mapName, ios::in);

	if (!lectura.is_open()) std::cout << "ERROR: File Open" << '\n';
	for (int i = 0; (i < FILA) && lectura.good(); i++) {
		for (int j = 0; (j < COLUMNA) && lectura.good(); j++) {
			if (j == (COLUMNA - 1)) {
				getline(lectura, matrix[i][j], '\n');
				matrix[i][j].erase(matrix[i][j].size() - 1);
			}
			else {
				getline(lectura, matrix[i][j], ';');
			}
		}
	}
	lectura.close();
}
