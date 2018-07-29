#include "Map.h"

using namespace std;

Map::Map(string mapName)
{
	this->mapName = mapName;
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j] = new GenericTile;
		}
	}

	csvReader();
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

void Map::setMapPath(string mapName)
{
	this->mapName = mapName;
	csvReader();
}

Map::~Map()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			delete tilesArray[i][j];
		}
	}
}

void Map::generateTilesArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units)
{
	string matrix2[FILA][COLUMNA];
	string terrainMatrix[FILA][COLUMNA];
	int pos;

	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			pos = matrix[i][j].find('+');
			if (pos != -1) {
				matrix2[i][j] = matrix[i][j].substr(0, pos);
			}
			else
			{
				matrix2[i][j] = matrix[i][j];
			}

			if ((matrix2[i][j].length()) > 1)
			{
				matrix2[i][j].erase(1);
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			bool encontroTerrain = false;
				list<Terrain>::iterator it = terrains.begin();
				for (bool k = true; k && (it != terrains.end()); ++it) {

					if (strcmp(it->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						printf("Encontre: %s\n", it->getName().c_str());
						Terrain *currTerrain = new Terrain;
						currTerrain->setName(it->getName());
						currTerrain->setPath(it->getPath());
						currTerrain->setType(it->getType());
						tilesArray[i][j]->addTerrain(currTerrain);
						encontroTerrain = true;
						terrainMatrix[i][j] = matrix2[i][j];
					}
					else
						terrainMatrix[i][j] = "NULL";
				}
			
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(!encontroTerrain) {
				list<Building>::iterator it2 = buildings.begin();
				for (bool k = true; k && (it2 != buildings.end()); ++it2) {

					if (strcmp(it2->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						printf("Encontre: %s\n", it2->getName().c_str());
						Building *currBuilding = new Building;
						currBuilding->setName(it2->getName());
						currBuilding->setPath(it2->getPath());
						currBuilding->setType(it2->getType());
						tilesArray[i][j]->addBuilding(currBuilding);
					}
				}
			}
		}
	}

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++)
		{
			//matrix[i][j] = "m1+ap0";
			pos = matrix[i][j].find('+');
			if (pos != -1) {
				matrix2[i][j] = matrix[i][j].substr(pos + 1);
			}
			else
			{
				matrix2[i][j] = " ";

			}

			if ((matrix2[i][j].length()) > 2)
			{
				matrix2[i][j].erase(2);
			}

			if (!(matrix2[i][j] == " ")) {
				list<Unit>::iterator it3 = units.begin();
				for (bool k = true; k && (it3 != units.end()); ++it3) {

					if (strcmp(it3->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						printf("Encontre: %s\n", it3->getName().c_str());
						Unit *currUnit = new Unit;
						currUnit->setName(it3->getName());
						currUnit->setPath(it3->getPath());
						currUnit->setType(it3->getType());
						tilesArray[i][j]->addUnit(currUnit);
					}
				}
			}

		}
	}
	
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j]->getTerrain()->setConnections(i, j, terrainMatrix);
		}
	}

}

GenericTile* Map::getTile(int i, int j)
{
	return tilesArray[i][j];
}
