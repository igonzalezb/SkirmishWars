#include "Map.h"

using namespace std;

Map::Map()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j] = new GenericTile;
			canMove[i][j] = false;
		}
	}
	isMapReceivedOk = false; //DESPUES PONER EN FALSE
}

void Map::verifyMapReceived()
{
#ifdef DEBUG
	cout << "Entro a verifymapreceived" << endl;
#endif // DEBUG

	setChecksum();
	if (checksum == checksumReceived)
	{
		isMapReceivedOk = true;
	}
	else
	{
		isMapReceivedOk = false;
	}
}

void Map::setChecksum()
{
	ifstream lectura;
	string archivo, temp;
	lectura.open(mapName, ios::in);
	if (!lectura.is_open()) std::cout << "ERROR: File Open" << '\n';

	for (int i = 0; (i < FILA) && lectura.good(); i++) {
		for (int j = 0; (j < COLUMNA) && lectura.good(); j++) {
			
			getline(lectura, temp, ' ');
			archivo += temp;
			temp = archivo;
		}
	}

	unsigned int* index = new unsigned int[archivo.length()];

	unsigned int Tabla[] = {
		98, 6, 85,150, 36, 23,112,164,135,207,169, 5, 26, 64,165,219,		// 1
		61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,		// 2
		90,168,156,203,177,120, 2,190,188, 7,100,185,174,243,162, 10,		// 3
		237, 18,253,225, 8,208,172,244,255,126,101, 79,145,235,228,121,		// 4
		123,251, 67,250,161, 0,107, 97,241,111,181, 82,249, 33, 69, 55,		// 5
		59,153, 29, 9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,		// 6
		197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,	// 7
		39,158,178,187,131,136, 1, 49, 50, 17,141, 91, 47,129, 60, 99,		// 8
		154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,	// 9
		133,232,196,144,198,124, 53, 4,108, 74,223,234,134,230,157,139,		// 10
		189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,	// 11
		183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,	// 12
		221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,	// 13
		3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,		// 14
		238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,	// 15
		43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239		// 16
	};

	index[0] = 0;
	unsigned int m = 0;
	for (unsigned int n = 1; n < archivo.length(); n++)
	{
		m = index[n - 1] ^ archivo.at(n);
		index[n] = Tabla[m];
	}

	checksum = index[archivo.length()-1];

	lectura.close();
}

unsigned char Map::getChecksum()
{
	return checksum;
}

void Map::setChecksumReceived(unsigned char checksumReceived_)
{
	checksumReceived = checksumReceived_;
}

unsigned char Map::getChecksumReceived()
{
	return checksumReceived;
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


#ifdef DEBUG
	printf("%s\n", mapName.c_str());
#endif // DEBUG

	mapFile = new csvFile(mapName, FILA, COLUMNA);
	
}

void Map::generateTilesArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units)
{

	int pos;
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j]->removeTerrain();
			tilesArray[i][j]->removeBuilding();
			tilesArray[i][j]->removeUnit();
			tilesArray[i][j]->addFog();
		}
	}

	string matrixEquipoOfFacility[FILA][COLUMNA];
	string matrixEquipoNave[FILA][COLUMNA];
	string matrixNave[FILA][COLUMNA];


	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			pos = mapFile->getMatrix()[i][j].find('+');
			if (pos != string::npos) {
				matrixDeTerrenoOrFacility[i][j] = mapFile->getMatrix()[i][j].substr(0, pos);
			}
			else
			{
				matrixDeTerrenoOrFacility[i][j] = mapFile->getMatrix()[i][j];
			}

			if ((matrixDeTerrenoOrFacility[i][j].length()) > 1)
			{
				matrixEquipoOfFacility[i][j] = matrixDeTerrenoOrFacility[i][j].back();
				matrixDeTerrenoOrFacility[i][j].erase(1);
			}

bool encontroTerrain = false;
list<Terrain>::iterator it = terrains.begin();
for (bool k = true; k && (it != terrains.end()); ++it) {

	if (strcmp(it->getType().c_str(), matrixDeTerrenoOrFacility[i][j].c_str()) == false) {
		k = false;
#ifdef DEBUG
		printf("Encontre: %s\n", it->getName().c_str());
#endif // DEBUG
		Terrain *currTerrain = new Terrain(it->getName(), it->getPath(), it->getType());
		tilesArray[i][j]->addTerrain(currTerrain);
		encontroTerrain = true;
	}
	else
		tilesArray[i][j]->addTerrain(NULL);	//es un string NULL (no esta vacio)
}

if (!encontroTerrain) {
	list<Building>::iterator it2 = buildings.begin();
	for (bool k = true; k && (it2 != buildings.end()); ++it2) {

		if (strcmp(it2->getType().c_str(), matrixDeTerrenoOrFacility[i][j].c_str()) == false) {
			k = false;
			Building *currBuilding = new Building(it2->getCp(), it2->getName(), it2->getPath(), it2->getType(), matrixEquipoOfFacility[i][j]);
			tilesArray[i][j]->addBuilding(currBuilding);
		}
		else
		{
			tilesArray[i][j]->addBuilding(NULL);
		}
	}
}
		}
	}

	for (int i = 0; i < FILA; i++) {
		for (int j = 0; j < COLUMNA; j++)
		{
			pos = mapFile->getMatrix()[i][j].find('+');
			if (pos != -1) {
				matrixNave[i][j] = mapFile->getMatrix()[i][j].substr(pos + 1);
			}
			else
			{
				matrixNave[i][j] = " ";

			}

			if ((matrixNave[i][j].length()) > 2)
			{
				matrixEquipoNave[i][j] = matrixNave[i][j].back();
				matrixNave[i][j].erase(2);
			}



			if (!(matrixNave[i][j] == " ")) {
				list<Unit>::iterator it3 = units.begin();
				for (bool k = true; k && (it3 != units.end()); ++it3) {

					if (strcmp(it3->getType().c_str(), matrixNave[i][j].c_str()) == false) {
						k = false;
						Unit *currUnit = new Unit(it3);
						currUnit->setTeam(TeamNumber(stoi(matrixEquipoNave[i][j])));
						tilesArray[i][j]->addUnit(currUnit);
					}
					else
					{
						tilesArray[i][j]->addUnit(NULL);
					}
				}
			}

		}
	}

	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			tilesArray[i][j]->getTerrain()->setConnections(i, j, matrixDeTerrenoOrFacility);
		}
	}



}

void Map::possibleMoves(Unit * currUnit, int i, int j)
{

	int matrixCost[FILA][COLUMNA];

	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
#ifndef NOFOG
			if (getTile(p, q)->getFog())
#endif // !NOFOG
			{
				matrixCost[p][q] = CANNOT_MOVE;
			}
			else if(((tilesArray[p][q]->getUnit()) != NULL) &&
				(tilesArray[p][q]->getUnit()->getType().compare("ap1")!=0) &&
				(tilesArray[p][q]->getUnit()->getType().compare("ap2") != 0))
			{
				matrixCost[p][q] = CANNOT_MOVE;
			}
			else if ((tilesArray[p][q]->getBuilding()) != NULL)
			{
				matrixCost[p][q] = stoi(currUnit->getMc().road);
			}
			else 
			{
				if (matrixDeTerrenoOrFacility[p][q].compare("a") == 0)
				{
					matrixCost[p][q] = stoi(currUnit->getMc().road);
				}
				else if (matrixDeTerrenoOrFacility[p][q].compare("r") == 0)
				{
					matrixCost[p][q] = stoi(currUnit->getMc().river);
				}
				else if (matrixDeTerrenoOrFacility[p][q].compare("f") == 0)
				{
					matrixCost[p][q] = stoi(currUnit->getMc().forest);
				}
				else if (matrixDeTerrenoOrFacility[p][q].compare("h") == 0)
				{
					matrixCost[p][q] = stoi(currUnit->getMc().hills);
				}
				else if (matrixDeTerrenoOrFacility[p][q].compare("t") == 0)
				{
					matrixCost[p][q] = stoi(currUnit->getMc().plain);
				}
			}

			canMove[p][q] = false;	//La seteo toda en false al principio
		}
	}
	
	matrixCost[i][j] = 0;	//Seteo el lugar donde estoy en 0 (VER!! - es para la recursiva)
	checkPossibleMoves(matrixCost, i, j, stoi(currUnit->getCurrMp()));
}


void Map::checkPossibleMoves(int matrixCost[FILA][COLUMNA], int i, int j, int MP) {
	
	if ((MP - matrixCost[i - 1][j]) >= 0)
	{
		canMove[i -1][j] = true;
	}
	if ((MP - matrixCost[i+1][j]) >= 0)
	{
		canMove[i + 1][j] = true;
	}
	if ((MP - matrixCost[i][j-1]) >= 0)
	{
		canMove[i][j-1] = true;
	}
	if ((MP - matrixCost[i][j+1]) >= 0)
	{
		canMove[i][j+1] = true;
	}
}

void Map::possibleAttack(Unit * currUnit, int i, int j, TeamNumber myTeam)
{

	int matrixCost[FILA][COLUMNA];

	for (int p = 0; p < FILA; p++)
	{
		for (int q = 0; q < COLUMNA; q++)
		{
			if (getTile(p, q)->getFog())
			{
				matrixCost[p][q] = CANNOT_MOVE;
			}
			else
			{
				matrixCost[p][q] = 1;
			}
			canAttack[p][q] = false;
		}
			
	}

	matrixCost[i][j] = 0;
	
	checkPossibleAttacks(matrixCost, i, j, stoi(currUnit->getRange().max), myTeam, true);
	matrixCost[i][j] = 1;
	checkPossibleAttacks(matrixCost, i, j, stoi(currUnit->getRange().min), myTeam, false);
	canAttack[i][j] = false;
}


void Map::checkPossibleAttacks(int matrixCost[FILA][COLUMNA], int i, int j, int Range, TeamNumber myTeam, bool _canmove) {
	if ((0 <= i) && (i < FILA) && (0 <= j) && (j < COLUMNA) && (Range >= 0))
	{
			Range -= matrixCost[i][j];
			
			if ((Range >= 0) && (getTile(i, j)->getUnit() != NULL) && (getTile(i, j)->getUnit()->getTeam() != myTeam))
			{
				canAttack[i][j] = _canmove;
			}
			checkPossibleAttacks(matrixCost, i - 1, j, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i + 1, j, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i, j + 1, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i, j - 1, Range, myTeam, _canmove);
	}
}

string Map::getMapName()
{
	return mapName;
}

void Map::setMapName(string mapName_)
{
	this->mapName = mapName_;
	
	mapFile = new csvFile(mapName, FILA, COLUMNA);
}

GenericTile* Map::getTile(int i, int j)
{
	return tilesArray[i][j];
}

void Map::updateFogOfWar(int myTeam)
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			if ((tilesArray[i][j]->getUnit() != NULL) && (tilesArray[i][j]->getUnit()->getTeam() == myTeam)) 
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
			if ((tilesArray[i][j]->getBuilding() != NULL) && (tilesArray[i][j]->getBuilding()->getTeam() == myTeam))
			{
				tilesArray[i][j]->removeFog();
			}
			
		}
	}
}


Map::~Map()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			delete tilesArray[i][j];
		}
	}
	delete mapFile;
}

