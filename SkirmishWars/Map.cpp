#include "Map.h"

using namespace std;

void funcion(int matrixCost[FILA][COLUMNA], bool(&canMove)[FILA][COLUMNA], int i, int j, int MP);


Map::Map()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j] = new GenericTile;
		}
	}

	randomMap();

	csvReader();
}

void Map::csvReader()
{
	ifstream lectura;
	lectura.open(mapName, ios::in);
	if (!lectura.is_open()) std::cout << "ERROR: File Open" << '\n';
	for (int i = 0; (i < FILA) && lectura.good(); i++) {
		for (int j = 0; (j < COLUMNA) && lectura.good(); j++) {
			if ((j == (COLUMNA - 1)) && (i != (FILA-1))) {
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

void Map::setMapPath(string mapName)
{
	this->mapName = mapName;
	csvReader();
}

void Map::randomMap()
{
	int map = rand() % MAX_MAPS;
	
	switch (map)
	{
	case 0:
		mapName = MAP_0;
		break;
	case 1:
		mapName = MAP_1;
		break;
	case 2:
		mapName = MAP_2;
		break;
	case 3:
		mapName = MAP_3;
		break;
	case 4:
		mapName = MAP_4;
		break;
	case 5:
		mapName = MAP_5;
		break;
//////////////////////////////////////////
	case 6:
		mapName = MAP_6;
		break;
	case 7:
		mapName = MAP_7;
		break;
	case 8:
		mapName = MAP_8;
		break;
	case 9:
		mapName = MAP_9;
		break;
	}

	printf("%s\n", mapName.c_str());
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

	int pos;
	string team;
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			pos = matrix[i][j].find('+');
			if (pos != string::npos) {
				matrix2[i][j] = matrix[i][j].substr(0, pos);
			}
			else
			{
				matrix2[i][j] = matrix[i][j];
			}

			if ((matrix2[i][j].length()) > 1)
			{
				team = matrix2[i][j].back();
				matrix2[i][j].erase(1);
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			bool encontroTerrain = false;
				list<Terrain>::iterator it = terrains.begin();
				for (bool k = true; k && (it != terrains.end()); ++it) {

					if (strcmp(it->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						//printf("Encontre: %s\n", it->getName().c_str());
						Terrain *currTerrain = new Terrain(it->getName(), it->getPath(), it->getType());
						tilesArray[i][j]->addTerrain(currTerrain);
						encontroTerrain = true;
						terrainMatrix[i][j] = matrix2[i][j];
					}
					else
						terrainMatrix[i][j] = "NULL";	//es un string NULL (no esta vacio)
				}
			
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(!encontroTerrain) {
				list<Building>::iterator it2 = buildings.begin();
				for (bool k = true; k && (it2 != buildings.end()); ++it2) {

					if (strcmp(it2->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						//printf("Encontre: %s\n", it2->getName().c_str());
						Building *currBuilding = new Building(it2->getHp(),it2->getName(), it2->getPath(), it2->getType(), team);
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
				team = matrix2[i][j].back();
				matrix2[i][j].erase(2);
			}

			if (!(matrix2[i][j] == " ")) {
				list<Unit>::iterator it3 = units.begin();
				for (bool k = true; k && (it3 != units.end()); ++it3) {

					if (strcmp(it3->getType().c_str(), matrix2[i][j].c_str()) == false) {
						k = false;
						//printf("Encontre: %s\n", it3->getName().c_str());
						Unit *currUnit = new Unit(it3);
						currUnit->setTeam(TeamColor(stoi(team)));
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

void Map::possibleMoves(Unit * currUnit, int i, int j, bool (&canMove)[FILA][COLUMNA])
{

	int matrixCost[FILA][COLUMNA];
	
	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
			if (getTile(p, q)->getFog()) {
				matrixCost[p][q] = CANNOT_MOVE;
			}
			else if (terrainMatrix[p][q] == "a")
				matrixCost[p][q] = stoi(currUnit->getMc().road);
			else if (terrainMatrix[p][q] == "r")
				matrixCost[p][q] = stoi(currUnit->getMc().river);
			else if (terrainMatrix[p][q] == "f")
				matrixCost[p][q] = stoi(currUnit->getMc().forest);
			else if (terrainMatrix[p][q] == "h")
				matrixCost[p][q] = stoi(currUnit->getMc().hills);
			else if (terrainMatrix[p][q] == "t")
				matrixCost[p][q] = stoi(currUnit->getMc().plain);
			else if (terrainMatrix[p][q] == "NULL")
				matrixCost[p][q] = 1;	//Quiere decir que hay un factory o city. LE PUSE 1 PERO NO ME ACUERDO

			canMove[p][q] = false;	//La seteo toda en false al principio
		}
	}



	matrixCost[i][j] = 0;	//Seteo el lugar donde estoy en 0 (VER!!)

	int mp = stoi(currUnit->getMp());
	funcion(matrixCost, canMove, i, j, mp);

}


void funcion(int matrixCost[FILA][COLUMNA], bool(&canMove)[FILA][COLUMNA], int i, int j, int MP) {
	if ((0 <= i) && (i < FILA) && (0 <= j) && (j < COLUMNA) && (MP >= 0))
	{
		MP -= matrixCost[i][j];
		if (MP >= 0) {
			canMove[i][j] = true;
			funcion(matrixCost, canMove, i - 1, j, MP);
			funcion(matrixCost, canMove, i + 1, j, MP);
			funcion(matrixCost, canMove, i, j + 1, MP);
			funcion(matrixCost, canMove, i, j - 1, MP);
		}
	}
}
GenericTile* Map::getTile(int i, int j)
{
	return tilesArray[i][j];
}

void Map::updateFogOfWar(int myTeam)
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			if (((tilesArray[i][j]->getUnit() != NULL) && (tilesArray[i][j]->getUnit()->getTeam() == myTeam)) || ((tilesArray[i][j]->getBuilding() != NULL) && (tilesArray[i][j]->getBuilding()->getTeam() == myTeam)))
			{
				tilesArray[i][j]->removeFog();

				if ((i - 1 >= 0))
				{
					tilesArray[i - 1][j]->removeFog();
				}
				if ((i + 1 < FILA))
				{
					tilesArray[i + 1][j]->removeFog();
				}
				if (((j - 1) >= 0))
				{
					tilesArray[i][j - 1]->removeFog();
				}
				if (((j + 1) < COLUMNA))
				{
					tilesArray[i][j + 1]->removeFog();
				}
			}
		}
	}
}
