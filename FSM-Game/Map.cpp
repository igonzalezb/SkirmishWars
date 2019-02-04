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


	//randomMap();

	//mapFile = new csvFile(mapName, FILA, COLUMNA);
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

	
	
	// get length of file:
	/*lectura.seekg(0, lectura.end);
	int length = lectura.tellg();
	lectura.seekg(0, lectura.beg);

	char * buffer = new char[length];*/


	for (int i = 0; (i < FILA) && lectura.good(); i++) {
		for (int j = 0; (j < COLUMNA) && lectura.good(); j++) {
			
			getline(lectura, temp, ' ');
			archivo += temp;
			temp = archivo;
		}
	}




	////lectura.read(buffer, length);

	unsigned int* index = new unsigned int[archivo.length()];

	//lectura.read(buffer, length);


	unsigned int Tabla[] = {
		98, 6, 85,150, 36, 23,112,164,135,207,169, 5, 26, 64,165,219, // 1
		61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, // 2
		90,168,156,203,177,120, 2,190,188, 7,100,185,174,243,162, 10, // 3
		237, 18,253,225, 8,208,172,244,255,126,101, 79,145,235,228,121, // 4
		123,251, 67,250,161, 0,107, 97,241,111,181, 82,249, 33, 69, 55, // 5
		59,153, 29, 9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, // 6
		197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, // 7
		39,158,178,187,131,136, 1, 49, 50, 17,141, 91, 47,129, 60, 99, // 8
		154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, // 9
		133,232,196,144,198,124, 53, 4,108, 74,223,234,134,230,157,139, // 10
		189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
		183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
		221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
		3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
		238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
		43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239 // 16
	};

	index[0] = 0;
	unsigned int m = 0;
	for (unsigned int n = 1; n < archivo.length(); n++)
	{
		m = index[n - 1] ^ archivo.at(n);
		index[n] = Tabla[m];
	}

	////cout << "m: " << m << endl;
	checksum = index[archivo.length()-1];
	//cout << "Checksum: " << checksum << endl;
	//isMapReceivedOk = true;

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

	//mapName = MAP_9;		//VOVLER A CAMBIAR!!!!!

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


	// A PARTIR DE LA INFO DEL .CSV DIVIDO LA INFO EN DOS MATRICES.... LA DE TERRENOS O FACILITIES Y LA DE EQUIPOS QUE CORRESPONDE A LAS FACILITIES
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			//cout << "hola" << endl;
			//cout << mapFile->getMatrix()[i][j] << endl;
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

			//CARGO LOS TERRENOS EN TILES ARRAY
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool encontroTerrain = false;
list<Terrain>::iterator it = terrains.begin();
for (bool k = true; k && (it != terrains.end()); ++it) {

	if (strcmp(it->getType().c_str(), matrixDeTerrenoOrFacility[i][j].c_str()) == false) {
		k = false;
#ifdef DEBUG
		//printf("Encontre: %s\n", it->getName().c_str());
#endif // DEBUG
		Terrain *currTerrain = new Terrain(it->getName(), it->getPath(), it->getType());
		tilesArray[i][j]->addTerrain(currTerrain);
		encontroTerrain = true;
	}
	else
		tilesArray[i][j]->addTerrain(NULL);	//es un string NULL (no esta vacio)
}
// CARGO LOS BUILDINGS EN TILES ARRAY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (!encontroTerrain) {
	list<Building>::iterator it2 = buildings.begin();
	for (bool k = true; k && (it2 != buildings.end()); ++it2) {

		if (strcmp(it2->getType().c_str(), matrixDeTerrenoOrFacility[i][j].c_str()) == false) {
			k = false;
			//printf("Encontre: %s\n", it2->getName().c_str());
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
						//printf("Encontre: %s\n", it3->getName().c_str());
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
	//canMove[i][j] = true;	//Seteo el lugar donde estoy en true
}

//void Map::checkPossibleMoves(int matrixCost[FILA][COLUMNA], int i, int j, int MP) {
//	if ((0 <= i) && (i < FILA) && (0 <= j) && (j < COLUMNA) && (MP >= 0))
//	{
//		MP -= matrixCost[i][j];
//		if (MP >= 0) {
//			canMove[i][j] = true;
//			checkPossibleMoves(matrixCost, i - 1, j, MP);
//			checkPossibleMoves(matrixCost, i + 1, j, MP);
//			checkPossibleMoves(matrixCost, i, j + 1, MP);
//			checkPossibleMoves(matrixCost, i, j - 1, MP);
//		}
//	}
//}

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
		//if (RangeMax >= 0) {
			Range -= matrixCost[i][j];
			
			if ((Range >= 0) && (getTile(i, j)->getUnit() != NULL) && (getTile(i, j)->getUnit()->getTeam() != myTeam))
			{
				canAttack[i][j] = _canmove;
			}
			checkPossibleAttacks(matrixCost, i - 1, j, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i + 1, j, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i, j + 1, Range, myTeam, _canmove);
			checkPossibleAttacks(matrixCost, i, j - 1, Range, myTeam, _canmove);
		//}
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

/*
//void Map::attack(coordenadas attacker, coordenadas defender) //ESTA FUNCION HABRIA QUE PONERLA EN OTRO ARCHIVO
void Map::attack()
{
	string symbol = tilesArray[defender.i][defender.j]->getUnit()->getSymbol();
	int firepower, inicialDamage, die, finalDamage, dieOnChart;
	//if (stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getHp()) < 5)
	if (tilesArray[attacker.i][attacker.j]->getUnit()->getHp() < 5) //menor a 5 significa REDUCED
	{
		if (symbol == "moon")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpReduced().moon);
		else if(symbol == "star")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpReduced().star);
		else if (symbol == "square")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpReduced().square);
		else if (symbol == "triangle")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpReduced().triangle);
		else if (symbol == "circle")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpReduced().circle);
	}
	else
	{
		if (symbol == "moon")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpNormal().moon);
		else if (symbol == "star")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpNormal().star);
		else if (symbol == "square")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpNormal().square);
		else if (symbol == "triangle")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpNormal().triangle);
		else if (symbol == "circle")
			firepower = stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getFpNormal().circle);
	}


	inicialDamage = firepower - stoi(tilesArray[defender.i][defender.j]->getUnit()->getdefense());

	// HACER aca el crossreference entre el inicial damage y el terreno en el que esta el defender!!!!!!!!!!!!!!!
	// finalDamage = ...
	// dieOnChart =.... (ESTAS DOS VARIABLES SALEN DE ENTRAR A LA TABLA ESA CON EL FINAL DAMAGE Y EL TERRENO DEL DEFENDER)

	die = rand() % 7 + 1; //VERIFICAR si esto tira un valor random entre 1 y 6.

	int columna;
	string defenderTerrain = getTile(attacker.i, attacker.j)->getTerrain()->getType();
	if (((getTile(attacker.i, attacker.j)->getBuilding()->getType()).compare("HQ"))|| (defenderTerrain.compare("h") == 0))
	{
		columna = 0;
	}
	else if (getTile(attacker.i, attacker.j)->getBuilding()!=NULL)
	{
		columna = 1;
	}
	else if (defenderTerrain.compare("f")==0)
	{
		columna = 2;
	}
	else if (defenderTerrain.compare("t") == 0)
	{
		columna = 3;

	}
	else if ((defenderTerrain.compare("a") == 0) || (defenderTerrain.compare("r") == 0))
	{
		columna = 4;
	}
	
	finalDamage = tableMatrix[13 - inicialDamage][columna].golpe; 
	dieOnChart = tableMatrix[13 - inicialDamage][columna].dado;

	if (die <= dieOnChart)
	{
		finalDamage++;
	}

	tilesArray[defender.i][defender.j]->getUnit()->setHp((tilesArray[defender.i][defender.j]->getUnit()->getHp()) - finalDamage);

	//mostrar la carta que tenga arriba el HP nuevo del defender, porque cambio su HP.
	//if HP < 5 : dar vuelta la carta y ahora esta REDUCED.

	attacker.i = NULL;
	attacker.j = NULL;
	defender.i = NULL;
	defender.j = NULL;
}


void Map::generateDefenseModifiersTable()
{
	string temp;

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 5; j++) {
			
			temp = defenseModifiers->getMatrix()[i][j].front();
			tableMatrix[i][j].golpe = stoi(temp.c_str());
			temp = defenseModifiers->getMatrix()[i][j].back();
			tableMatrix[i][j].dado = stoi(temp.c_str());
		}
	}
}*/

Map::~Map()
{
	for (int i = 0; i < (FILA); i++) {
		for (int j = 0; j < (COLUMNA); j++) {
			delete tilesArray[i][j];
		}
	}
	delete mapFile;
	//delete defenseModifiers;
}


//////////////////////
//void Map::setAttacker(int tile)
//{
//	/*switch (tile)
//	{
//	case A1: attacker.i = 0; attacker.j = 0; break;
//	case A2: attacker.i = 0; attacker.j = 1; break;
//	case A3: attacker.i = 0; attacker.j = 2; break;
//	case A4: attacker.i = 0; attacker.j = 3; break;
//	case A5: attacker.i = 0; attacker.j = 4; break;
//	case A6: attacker.i = 0; attacker.j = 5; break;
//	case A7: attacker.i = 0; attacker.j = 6; break;
//	case A8: attacker.i = 0; attacker.j = 7; break;
//	case A9: attacker.i = 0; attacker.j = 8; break;
//	case A10: attacker.i = 0; attacker.j = 9; break;
//	case A11: attacker.i = 0; attacker.j = 10; break;
//	case A12: attacker.i = 0; attacker.j = 11; break;
//	case A13: attacker.i = 0; attacker.j = 12; break;
//	case A14: attacker.i = 0; attacker.j = 13; break;
//	case A15: attacker.i = 0; attacker.j = 14; break;
//	case A16: attacker.i = 0; attacker.j = 15; break;
//
//	case B1: attacker.i = 1; attacker.j = 0; break;
//	case B2: attacker.i = 1; attacker.j = 1; break;
//	case B3: attacker.i = 1; attacker.j = 2; break;
//	case B4: attacker.i = 1; attacker.j = 3; break;
//	case B5: attacker.i = 1; attacker.j = 4; break;
//	case B6: attacker.i = 1; attacker.j = 5; break;
//	case B7: attacker.i = 1; attacker.j = 6; break;
//	case B8: attacker.i = 1; attacker.j = 7; break;
//	case B9: attacker.i = 1; attacker.j = 8; break;
//	case B10: attacker.i = 1; attacker.j = 9; break;
//	case B11: attacker.i = 1; attacker.j = 10; break;
//	case B12: attacker.i = 1; attacker.j = 11; break;
//	case B13: attacker.i = 1; attacker.j = 12; break;
//	case B14: attacker.i = 1; attacker.j = 13; break;
//	case B15: attacker.i = 1; attacker.j = 14; break;
//	case B16: attacker.i = 1; attacker.j = 15; break;
//
//	case C1: attacker.i = 2; attacker.j = 0; break;
//	case C2: attacker.i = 2; attacker.j = 1; break;
//	case C3: attacker.i = 2; attacker.j = 2; break;
//	case C4: attacker.i = 2; attacker.j = 3; break;
//	case C5: attacker.i = 2; attacker.j = 4; break;
//	case C6: attacker.i = 2; attacker.j = 5; break;
//	case C7: attacker.i = 2; attacker.j = 6; break;
//	case C8: attacker.i = 2; attacker.j = 7; break;
//	case C9: attacker.i = 2; attacker.j = 8; break;
//	case C10: attacker.i = 2; attacker.j = 9; break;
//	case C11: attacker.i = 2; attacker.j = 10; break;
//	case C12: attacker.i = 2; attacker.j = 11; break;
//	case C13: attacker.i = 2; attacker.j = 12; break;
//	case C14: attacker.i = 2; attacker.j = 13; break;
//	case C15: attacker.i = 2; attacker.j = 14; break;
//	case C16: attacker.i = 2; attacker.j = 15; break;
//
//	case D1: attacker.i = 3; attacker.j = 0; break;
//	case D2: attacker.i = 3; attacker.j = 1; break;
//	case D3: attacker.i = 3; attacker.j = 2; break;
//	case D4: attacker.i = 3; attacker.j = 3; break;
//	case D5: attacker.i = 3; attacker.j = 4; break;
//	case D6: attacker.i = 3; attacker.j = 5; break;
//	case D7: attacker.i = 3; attacker.j = 6; break;
//	case D8: attacker.i = 3; attacker.j = 7; break;
//	case D9: attacker.i = 3; attacker.j = 8; break;
//	case D10: attacker.i = 3; attacker.j = 9; break;
//	case D11: attacker.i = 3; attacker.j = 10; break;
//	case D12: attacker.i = 3; attacker.j = 11; break;
//	case D13: attacker.i = 3; attacker.j = 12; break;
//	case D14: attacker.i = 3; attacker.j = 13; break;
//	case D15: attacker.i = 3; attacker.j = 14; break;
//	case D16: attacker.i = 3; attacker.j = 15; break;
//
//	case E1: attacker.i = 4; attacker.j = 0; break;
//	case E2: attacker.i = 4; attacker.j = 1; break;
//	case E3: attacker.i = 4; attacker.j = 2; break;
//	case E4: attacker.i = 4; attacker.j = 3; break;
//	case E5: attacker.i = 4; attacker.j = 4; break;
//	case E6: attacker.i = 4; attacker.j = 5; break;
//	case E7: attacker.i = 4; attacker.j = 6; break;
//	case E8: attacker.i = 4; attacker.j = 7; break;
//	case E9: attacker.i = 4; attacker.j = 8; break;
//	case E10: attacker.i = 4; attacker.j = 9; break;
//	case E11: attacker.i = 4; attacker.j = 10; break;
//	case E12: attacker.i = 4; attacker.j = 11; break;
//	case E13: attacker.i = 4; attacker.j = 12; break;
//	case E14: attacker.i = 4; attacker.j = 13; break;
//	case E15: attacker.i = 4; attacker.j = 14; break;
//	case E16: attacker.i = 4; attacker.j = 15; break;
//
//	case F1: attacker.i = 5; attacker.j = 0; break;
//	case F2: attacker.i = 5; attacker.j = 1; break;
//	case F3: attacker.i = 5; attacker.j = 2; break;
//	case F4: attacker.i = 5; attacker.j = 3; break;
//	case F5: attacker.i = 5; attacker.j = 4; break;
//	case F6: attacker.i = 5; attacker.j = 5; break;
//	case F7: attacker.i = 5; attacker.j = 6; break;
//	case F8: attacker.i = 5; attacker.j = 7; break;
//	case F9: attacker.i = 5; attacker.j = 8; break;
//	case F10: attacker.i = 5; attacker.j = 9; break;
//	case F11: attacker.i = 5; attacker.j = 10; break;
//	case F12: attacker.i = 5; attacker.j = 11; break;
//	case F13: attacker.i = 5; attacker.j = 12; break;
//	case F14: attacker.i = 5; attacker.j = 13; break;
//	case F15: attacker.i = 5; attacker.j = 14; break;
//	case F16: attacker.i = 5; attacker.j = 15; break;
//
//	case G1: attacker.i = 6; attacker.j = 0; break;
//	case G2: attacker.i = 6; attacker.j = 1; break;
//	case G3: attacker.i = 6; attacker.j = 2; break;
//	case G4: attacker.i = 6; attacker.j = 3; break;
//	case G5: attacker.i = 6; attacker.j = 4; break;
//	case G6: attacker.i = 6; attacker.j = 5; break;
//	case G7: attacker.i = 6; attacker.j = 6; break;
//	case G8: attacker.i = 6; attacker.j = 7; break;
//	case G9: attacker.i = 6; attacker.j = 8; break;
//	case G10: attacker.i = 6; attacker.j = 9; break;
//	case G11: attacker.i = 6; attacker.j = 10; break;
//	case G12: attacker.i = 6; attacker.j = 11; break;
//	case G13: attacker.i = 6; attacker.j = 12; break;
//	case G14: attacker.i = 6; attacker.j = 13; break;
//	case G15: attacker.i = 6; attacker.j = 14; break;
//	case G16: attacker.i = 6; attacker.j = 15; break;
//
//	case H1: attacker.i = 7; attacker.j = 0; break;
//	case H2: attacker.i = 7; attacker.j = 1; break;
//	case H3: attacker.i = 7; attacker.j = 2; break;
//	case H4: attacker.i = 7; attacker.j = 3; break;
//	case H5: attacker.i = 7; attacker.j = 4; break;
//	case H6: attacker.i = 7; attacker.j = 5; break;
//	case H7: attacker.i = 7; attacker.j = 6; break;
//	case H8: attacker.i = 7; attacker.j = 7; break;
//	case H9: attacker.i = 7; attacker.j = 8; break;
//	case H10: attacker.i = 7; attacker.j = 9; break;
//	case H11: attacker.i = 7; attacker.j = 10; break;
//	case H12: attacker.i = 7; attacker.j = 11; break;
//	case H13: attacker.i = 7; attacker.j = 12; break;
//	case H14: attacker.i = 7; attacker.j = 13; break;
//	case H15: attacker.i = 7; attacker.j = 14; break;
//	case H16: attacker.i = 7; attacker.j = 15; break;
//
//	case I1: attacker.i = 8; attacker.j = 0; break;
//	case I2: attacker.i = 8; attacker.j = 1; break;
//	case I3: attacker.i = 8; attacker.j = 2; break;
//	case I4: attacker.i = 8; attacker.j = 3; break;
//	case I5: attacker.i = 8; attacker.j = 4; break;
//	case I6: attacker.i = 8; attacker.j = 5; break;
//	case I7: attacker.i = 8; attacker.j = 6; break;
//	case I8: attacker.i = 8; attacker.j = 7; break;
//	case I9: attacker.i = 8; attacker.j = 8; break;
//	case I10: attacker.i = 8; attacker.j = 9; break;
//	case I11: attacker.i = 8; attacker.j = 10; break;
//	case I12: attacker.i = 8; attacker.j = 11; break;
//	case I13: attacker.i = 8; attacker.j = 12; break;
//	case I14: attacker.i = 8; attacker.j = 13; break;
//	case I15: attacker.i = 8; attacker.j = 14; break;
//	case I16: attacker.i = 8; attacker.j = 15; break;
//
//	case J1: attacker.i = 9; attacker.j = 0; break;
//	case J2: attacker.i = 9; attacker.j = 1; break;
//	case J3: attacker.i = 9; attacker.j = 2; break;
//	case J4: attacker.i = 9; attacker.j = 3; break;
//	case J5: attacker.i = 9; attacker.j = 4; break;
//	case J6: attacker.i = 9; attacker.j = 5; break;
//	case J7: attacker.i = 9; attacker.j = 6; break;
//	case J8: attacker.i = 9; attacker.j = 7; break;
//	case J9: attacker.i = 9; attacker.j = 8; break;
//	case J10: attacker.i = 9; attacker.j = 9; break;
//	case J11: attacker.i = 9; attacker.j = 10; break;
//	case J12: attacker.i = 9; attacker.j = 11; break;
//	case J13: attacker.i = 9; attacker.j = 12; break;
//	case J14: attacker.i = 9; attacker.j = 13; break;
//	case J15: attacker.i = 9; attacker.j = 14; break;
//	case J16: attacker.i = 9; attacker.j = 15; break;
//
//	case K1: attacker.i = 10; attacker.j = 0; break;
//	case K2: attacker.i = 10; attacker.j = 1; break;
//	case K3: attacker.i = 10; attacker.j = 2; break;
//	case K4: attacker.i = 10; attacker.j = 3; break;
//	case K5: attacker.i = 10; attacker.j = 4; break;
//	case K6: attacker.i = 10; attacker.j = 5; break;
//	case K7: attacker.i = 10; attacker.j = 6; break;
//	case K8: attacker.i = 10; attacker.j = 7; break;
//	case K9: attacker.i = 10; attacker.j = 8; break;
//	case K10: attacker.i = 10; attacker.j = 9; break;
//	case K11: attacker.i = 10; attacker.j = 10; break;
//	case K12: attacker.i = 10; attacker.j = 11; break;
//	case K13: attacker.i = 10; attacker.j = 12; break;
//	case K14: attacker.i = 10; attacker.j = 13; break;
//	case K15: attacker.i = 10; attacker.j = 14; break;
//	case K16: attacker.i = 10; attacker.j = 15; break;
//
//	case L1: attacker.i = 11; attacker.j = 0; break;
//	case L2: attacker.i = 11; attacker.j = 1; break;
//	case L3: attacker.i = 11; attacker.j = 2; break;
//	case L4: attacker.i = 11; attacker.j = 3; break;
//	case L5: attacker.i = 11; attacker.j = 4; break;
//	case L6: attacker.i = 11; attacker.j = 5; break;
//	case L7: attacker.i = 11; attacker.j = 6; break;
//	case L8: attacker.i = 11; attacker.j = 7; break;
//	case L9: attacker.i = 11; attacker.j = 8; break;
//	case L10: attacker.i = 11; attacker.j = 9; break;
//	case L11: attacker.i = 11; attacker.j = 10; break;
//	case L12: attacker.i = 11; attacker.j = 11; break;
//	case L13: attacker.i = 11; attacker.j = 12; break;
//	case L14: attacker.i = 11; attacker.j = 13; break;
//	case L15: attacker.i = 11; attacker.j = 14; break;
//	case L16: attacker.i = 11; attacker.j = 15; break;
//
//	default: break;
//	}*/
//}
//
//void Map::setDefender(int tile)
//{
//	/*switch (tile)
//	{
//	case A1: defender.i = 0; defender.j = 0; break;
//	case A2: defender.i = 0; defender.j = 1; break;
//	case A3: defender.i = 0; defender.j = 2; break;
//	case A4: defender.i = 0; defender.j = 3; break;
//	case A5: defender.i = 0; defender.j = 4; break;
//	case A6: defender.i = 0; defender.j = 5; break;
//	case A7: defender.i = 0; defender.j = 6; break;
//	case A8: defender.i = 0; defender.j = 7; break;
//	case A9: defender.i = 0; defender.j = 8; break;
//	case A10: defender.i = 0; defender.j = 9; break;
//	case A11: defender.i = 0; defender.j = 10; break;
//	case A12: defender.i = 0; defender.j = 11; break;
//	case A13: defender.i = 0; defender.j = 12; break;
//	case A14: defender.i = 0; defender.j = 13; break;
//	case A15: defender.i = 0; defender.j = 14; break;
//	case A16: defender.i = 0; defender.j = 15; break;
//
//	case B1: defender.i = 1; defender.j = 0; break;
//	case B2: defender.i = 1; defender.j = 1; break;
//	case B3: defender.i = 1; defender.j = 2; break;
//	case B4: defender.i = 1; defender.j = 3; break;
//	case B5: defender.i = 1; defender.j = 4; break;
//	case B6: defender.i = 1; defender.j = 5; break;
//	case B7: defender.i = 1; defender.j = 6; break;
//	case B8: defender.i = 1; defender.j = 7; break;
//	case B9: defender.i = 1; defender.j = 8; break;
//	case B10: defender.i = 1; defender.j = 9; break;
//	case B11: defender.i = 1; defender.j = 10; break;
//	case B12: defender.i = 1; defender.j = 11; break;
//	case B13: defender.i = 1; defender.j = 12; break;
//	case B14: defender.i = 1; defender.j = 13; break;
//	case B15: defender.i = 1; defender.j = 14; break;
//	case B16: defender.i = 1; defender.j = 15; break;
//
//	case C1: defender.i = 2; defender.j = 0; break;
//	case C2: defender.i = 2; defender.j = 1; break;
//	case C3: defender.i = 2; defender.j = 2; break;
//	case C4: defender.i = 2; defender.j = 3; break;
//	case C5: defender.i = 2; defender.j = 4; break;
//	case C6: defender.i = 2; defender.j = 5; break;
//	case C7: defender.i = 2; defender.j = 6; break;
//	case C8: defender.i = 2; defender.j = 7; break;
//	case C9: defender.i = 2; defender.j = 8; break;
//	case C10: defender.i = 2; defender.j = 9; break;
//	case C11: defender.i = 2; defender.j = 10; break;
//	case C12: defender.i = 2; defender.j = 11; break;
//	case C13: defender.i = 2; defender.j = 12; break;
//	case C14: defender.i = 2; defender.j = 13; break;
//	case C15: defender.i = 2; defender.j = 14; break;
//	case C16: defender.i = 2; defender.j = 15; break;
//
//	case D1: defender.i = 3; defender.j = 0; break;
//	case D2: defender.i = 3; defender.j = 1; break;
//	case D3: defender.i = 3; defender.j = 2; break;
//	case D4: defender.i = 3; defender.j = 3; break;
//	case D5: defender.i = 3; defender.j = 4; break;
//	case D6: defender.i = 3; defender.j = 5; break;
//	case D7: defender.i = 3; defender.j = 6; break;
//	case D8: defender.i = 3; defender.j = 7; break;
//	case D9: defender.i = 3; defender.j = 8; break;
//	case D10: defender.i = 3; defender.j = 9; break;
//	case D11: defender.i = 3; defender.j = 10; break;
//	case D12: defender.i = 3; defender.j = 11; break;
//	case D13: defender.i = 3; defender.j = 12; break;
//	case D14: defender.i = 3; defender.j = 13; break;
//	case D15: defender.i = 3; defender.j = 14; break;
//	case D16: defender.i = 3; defender.j = 15; break;
//
//	case E1: defender.i = 4; defender.j = 0; break;
//	case E2: defender.i = 4; defender.j = 1; break;
//	case E3: defender.i = 4; defender.j = 2; break;
//	case E4: defender.i = 4; defender.j = 3; break;
//	case E5: defender.i = 4; defender.j = 4; break;
//	case E6: defender.i = 4; defender.j = 5; break;
//	case E7: defender.i = 4; defender.j = 6; break;
//	case E8: defender.i = 4; defender.j = 7; break;
//	case E9: defender.i = 4; defender.j = 8; break;
//	case E10: defender.i = 4; defender.j = 9; break;
//	case E11: defender.i = 4; defender.j = 10; break;
//	case E12: defender.i = 4; defender.j = 11; break;
//	case E13: defender.i = 4; defender.j = 12; break;
//	case E14: defender.i = 4; defender.j = 13; break;
//	case E15: defender.i = 4; defender.j = 14; break;
//	case E16: defender.i = 4; defender.j = 15; break;
//
//	case F1: defender.i = 5; defender.j = 0; break;
//	case F2: defender.i = 5; defender.j = 1; break;
//	case F3: defender.i = 5; defender.j = 2; break;
//	case F4: defender.i = 5; defender.j = 3; break;
//	case F5: defender.i = 5; defender.j = 4; break;
//	case F6: defender.i = 5; defender.j = 5; break;
//	case F7: defender.i = 5; defender.j = 6; break;
//	case F8: defender.i = 5; defender.j = 7; break;
//	case F9: defender.i = 5; defender.j = 8; break;
//	case F10: defender.i = 5; defender.j = 9; break;
//	case F11: defender.i = 5; defender.j = 10; break;
//	case F12: defender.i = 5; defender.j = 11; break;
//	case F13: defender.i = 5; defender.j = 12; break;
//	case F14: defender.i = 5; defender.j = 13; break;
//	case F15: defender.i = 5; defender.j = 14; break;
//	case F16: defender.i = 5; defender.j = 15; break;
//
//	case G1: defender.i = 6; defender.j = 0; break;
//	case G2: defender.i = 6; defender.j = 1; break;
//	case G3: defender.i = 6; defender.j = 2; break;
//	case G4: defender.i = 6; defender.j = 3; break;
//	case G5: defender.i = 6; defender.j = 4; break;
//	case G6: defender.i = 6; defender.j = 5; break;
//	case G7: defender.i = 6; defender.j = 6; break;
//	case G8: defender.i = 6; defender.j = 7; break;
//	case G9: defender.i = 6; defender.j = 8; break;
//	case G10: defender.i = 6; defender.j = 9; break;
//	case G11: defender.i = 6; defender.j = 10; break;
//	case G12: defender.i = 6; defender.j = 11; break;
//	case G13: defender.i = 6; defender.j = 12; break;
//	case G14: defender.i = 6; defender.j = 13; break;
//	case G15: defender.i = 6; defender.j = 14; break;
//	case G16: defender.i = 6; defender.j = 15; break;
//
//	case H1: defender.i = 7; defender.j = 0; break;
//	case H2: defender.i = 7; defender.j = 1; break;
//	case H3: defender.i = 7; defender.j = 2; break;
//	case H4: defender.i = 7; defender.j = 3; break;
//	case H5: defender.i = 7; defender.j = 4; break;
//	case H6: defender.i = 7; defender.j = 5; break;
//	case H7: defender.i = 7; defender.j = 6; break;
//	case H8: defender.i = 7; defender.j = 7; break;
//	case H9: defender.i = 7; defender.j = 8; break;
//	case H10: defender.i = 7; defender.j = 9; break;
//	case H11: defender.i = 7; defender.j = 10; break;
//	case H12: defender.i = 7; defender.j = 11; break;
//	case H13: defender.i = 7; defender.j = 12; break;
//	case H14: defender.i = 7; defender.j = 13; break;
//	case H15: defender.i = 7; defender.j = 14; break;
//	case H16: defender.i = 7; defender.j = 15; break;
//
//	case I1: defender.i = 8; defender.j = 0; break;
//	case I2: defender.i = 8; defender.j = 1; break;
//	case I3: defender.i = 8; defender.j = 2; break;
//	case I4: defender.i = 8; defender.j = 3; break;
//	case I5: defender.i = 8; defender.j = 4; break;
//	case I6: defender.i = 8; defender.j = 5; break;
//	case I7: defender.i = 8; defender.j = 6; break;
//	case I8: defender.i = 8; defender.j = 7; break;
//	case I9: defender.i = 8; defender.j = 8; break;
//	case I10: defender.i = 8; defender.j = 9; break;
//	case I11: defender.i = 8; defender.j = 10; break;
//	case I12: defender.i = 8; defender.j = 11; break;
//	case I13: defender.i = 8; defender.j = 12; break;
//	case I14: defender.i = 8; defender.j = 13; break;
//	case I15: defender.i = 8; defender.j = 14; break;
//	case I16: defender.i = 8; defender.j = 15; break;
//
//	case J1: defender.i = 9; defender.j = 0; break;
//	case J2: defender.i = 9; defender.j = 1; break;
//	case J3: defender.i = 9; defender.j = 2; break;
//	case J4: defender.i = 9; defender.j = 3; break;
//	case J5: defender.i = 9; defender.j = 4; break;
//	case J6: defender.i = 9; defender.j = 5; break;
//	case J7: defender.i = 9; defender.j = 6; break;
//	case J8: defender.i = 9; defender.j = 7; break;
//	case J9: defender.i = 9; defender.j = 8; break;
//	case J10: defender.i = 9; defender.j = 9; break;
//	case J11: defender.i = 9; defender.j = 10; break;
//	case J12: defender.i = 9; defender.j = 11; break;
//	case J13: defender.i = 9; defender.j = 12; break;
//	case J14: defender.i = 9; defender.j = 13; break;
//	case J15: defender.i = 9; defender.j = 14; break;
//	case J16: defender.i = 9; defender.j = 15; break;
//
//	case K1: defender.i = 10; defender.j = 0; break;
//	case K2: defender.i = 10; defender.j = 1; break;
//	case K3: defender.i = 10; defender.j = 2; break;
//	case K4: defender.i = 10; defender.j = 3; break;
//	case K5: defender.i = 10; defender.j = 4; break;
//	case K6: defender.i = 10; defender.j = 5; break;
//	case K7: defender.i = 10; defender.j = 6; break;
//	case K8: defender.i = 10; defender.j = 7; break;
//	case K9: defender.i = 10; defender.j = 8; break;
//	case K10: defender.i = 10; defender.j = 9; break;
//	case K11: defender.i = 10; defender.j = 10; break;
//	case K12: defender.i = 10; defender.j = 11; break;
//	case K13: defender.i = 10; defender.j = 12; break;
//	case K14: defender.i = 10; defender.j = 13; break;
//	case K15: defender.i = 10; defender.j = 14; break;
//	case K16: defender.i = 10; defender.j = 15; break;
//
//	case L1: defender.i = 11; defender.j = 0; break;
//	case L2: defender.i = 11; defender.j = 1; break;
//	case L3: defender.i = 11; defender.j = 2; break;
//	case L4: defender.i = 11; defender.j = 3; break;
//	case L5: defender.i = 11; defender.j = 4; break;
//	case L6: defender.i = 11; defender.j = 5; break;
//	case L7: defender.i = 11; defender.j = 6; break;
//	case L8: defender.i = 11; defender.j = 7; break;
//	case L9: defender.i = 11; defender.j = 8; break;
//	case L10: defender.i = 11; defender.j = 9; break;
//	case L11: defender.i = 11; defender.j = 10; break;
//	case L12: defender.i = 11; defender.j = 11; break;
//	case L13: defender.i = 11; defender.j = 12; break;
//	case L14: defender.i = 11; defender.j = 13; break;
//	case L15: defender.i = 11; defender.j = 14; break;
//	case L16: defender.i = 11; defender.j = 15; break;
//
//	default: break;
//	}*/
//}