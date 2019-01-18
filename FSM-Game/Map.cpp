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

	mapFile = new csvFile(mapName, FILA, COLUMNA);

}

void Map::setMapPath(string mapName)
{
	this->mapName = mapName;
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

#ifdef DEBUG
	printf("%s\n", mapName.c_str());
#endif // DEBUG


	
}

void Map::generate
sArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units)
{

	int pos;
	
	string matrixEquipoOfFacility[FILA][COLUMNA];
	string matrixEquipoNave[FILA][COLUMNA];
	string matrixNave[FILA][COLUMNA];


	// A PARTIR DE LA INFO DEL .CSV DIVIDO LA INFO EN DOS MATRICES.... LA DE TERRENOS O FACILITIES Y LA DE EQUIPOS QUE CORRESPONDE A LAS FACILITIES
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

			//CARGO LOS TERRENOS EN TILES ARRAY
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool encontroTerrain = false;
list<Terrain>::iterator it = terrains.begin();
for (bool k = true; k && (it != terrains.end()); ++it) {

	if (strcmp(it->getType().c_str(), matrixDeTerrenoOrFacility[i][j].c_str()) == false) {
		k = false;
		printf("Encontre: %s\n", it->getName().c_str());
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
						currUnit->setTeam(TeamColor(stoi(matrixEquipoNave[i][j])));
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

void Map::possibleMoves(Unit * currUnit, int i, int j)//, bool (&canMove)[FILA][COLUMNA])
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
			else if ((tilesArray[p][q]->getBuilding()) != NULL)
			{
				matrixCost[p][q] = stoi(currUnit->getMc().road);
			}
			else 
			{
				if (matrixDeTerrenoOrFacility[p][q] == "a")
				{
					matrixCost[p][q] = stoi(currUnit->getMc().road);
				}
				else if (matrixDeTerrenoOrFacility[p][q] == "r")
				{
					matrixCost[p][q] = stoi(currUnit->getMc().river);
				}
				else if (matrixDeTerrenoOrFacility[p][q] == "f")
				{
					matrixCost[p][q] = stoi(currUnit->getMc().forest);
				}
				else if (matrixDeTerrenoOrFacility[p][q] == "h")
				{
					matrixCost[p][q] = stoi(currUnit->getMc().hills);
				}
				else if (matrixDeTerrenoOrFacility[p][q] == "t")
				{
					matrixCost[p][q] = stoi(currUnit->getMc().plain);
				}
			}
			canMove[p][q] = false;	//La seteo toda en false al principio
		}
	}
	matrixCost[i][j] = 0;	//Seteo el lugar donde estoy en 0 (VER!!)
	checkPossibleMoves(matrixCost, i, j, stoi(currUnit->getMp()));
}

void Map::checkPossibleMoves(int matrixCost[FILA][COLUMNA], int i, int j, int MP) {
	if ((0 <= i) && (i < FILA) && (0 <= j) && (j < COLUMNA) && (MP >= 0))
	{
		if (MP >= 0) {
			MP -= matrixCost[i][j];
			if ((MP >= 0)&&((getTile(i,j)->getFog())==false)&&((getTile(i,j)->getUnit())==NULL)) 
			{
				canMove[i][j] = true;
			}
			funcion(matrixCost, i - 1, j, MP);
			funcion(matrixCost, i + 1, j, MP);
			funcion(matrixCost, i, j + 1, MP);
			funcion(matrixCost, i, j - 1, MP);
		}
	}
}

string Map::getMapName()
{
	return mapName;
}

void Map::setMapName(string mapName_)
{
	this->mapName = mapName_;
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
void Map::setAttacker(int tile)
{
	switch (tile)
	{
	case A1: attacker.i = 0; attacker.j = 0; break;
	case A2: attacker.i = 0; attacker.j = 1; break;
	case A3: attacker.i = 0; attacker.j = 2; break;
	case A4: attacker.i = 0; attacker.j = 3; break;
	case A5: attacker.i = 0; attacker.j = 4; break;
	case A6: attacker.i = 0; attacker.j = 5; break;
	case A7: attacker.i = 0; attacker.j = 6; break;
	case A8: attacker.i = 0; attacker.j = 7; break;
	case A9: attacker.i = 0; attacker.j = 8; break;
	case A10: attacker.i = 0; attacker.j = 9; break;
	case A11: attacker.i = 0; attacker.j = 10; break;
	case A12: attacker.i = 0; attacker.j = 11; break;
	case A13: attacker.i = 0; attacker.j = 12; break;
	case A14: attacker.i = 0; attacker.j = 13; break;
	case A15: attacker.i = 0; attacker.j = 14; break;
	case A16: attacker.i = 0; attacker.j = 15; break;

	case B1: attacker.i = 1; attacker.j = 0; break;
	case B2: attacker.i = 1; attacker.j = 1; break;
	case B3: attacker.i = 1; attacker.j = 2; break;
	case B4: attacker.i = 1; attacker.j = 3; break;
	case B5: attacker.i = 1; attacker.j = 4; break;
	case B6: attacker.i = 1; attacker.j = 5; break;
	case B7: attacker.i = 1; attacker.j = 6; break;
	case B8: attacker.i = 1; attacker.j = 7; break;
	case B9: attacker.i = 1; attacker.j = 8; break;
	case B10: attacker.i = 1; attacker.j = 9; break;
	case B11: attacker.i = 1; attacker.j = 10; break;
	case B12: attacker.i = 1; attacker.j = 11; break;
	case B13: attacker.i = 1; attacker.j = 12; break;
	case B14: attacker.i = 1; attacker.j = 13; break;
	case B15: attacker.i = 1; attacker.j = 14; break;
	case B16: attacker.i = 1; attacker.j = 15; break;

	case C1: attacker.i = 2; attacker.j = 0; break;
	case C2: attacker.i = 2; attacker.j = 1; break;
	case C3: attacker.i = 2; attacker.j = 2; break;
	case C4: attacker.i = 2; attacker.j = 3; break;
	case C5: attacker.i = 2; attacker.j = 4; break;
	case C6: attacker.i = 2; attacker.j = 5; break;
	case C7: attacker.i = 2; attacker.j = 6; break;
	case C8: attacker.i = 2; attacker.j = 7; break;
	case C9: attacker.i = 2; attacker.j = 8; break;
	case C10: attacker.i = 2; attacker.j = 9; break;
	case C11: attacker.i = 2; attacker.j = 10; break;
	case C12: attacker.i = 2; attacker.j = 11; break;
	case C13: attacker.i = 2; attacker.j = 12; break;
	case C14: attacker.i = 2; attacker.j = 13; break;
	case C15: attacker.i = 2; attacker.j = 14; break;
	case C16: attacker.i = 2; attacker.j = 15; break;

	case D1: attacker.i = 3; attacker.j = 0; break;
	case D2: attacker.i = 3; attacker.j = 1; break;
	case D3: attacker.i = 3; attacker.j = 2; break;
	case D4: attacker.i = 3; attacker.j = 3; break;
	case D5: attacker.i = 3; attacker.j = 4; break;
	case D6: attacker.i = 3; attacker.j = 5; break;
	case D7: attacker.i = 3; attacker.j = 6; break;
	case D8: attacker.i = 3; attacker.j = 7; break;
	case D9: attacker.i = 3; attacker.j = 8; break;
	case D10: attacker.i = 3; attacker.j = 9; break;
	case D11: attacker.i = 3; attacker.j = 10; break;
	case D12: attacker.i = 3; attacker.j = 11; break;
	case D13: attacker.i = 3; attacker.j = 12; break;
	case D14: attacker.i = 3; attacker.j = 13; break;
	case D15: attacker.i = 3; attacker.j = 14; break;
	case D16: attacker.i = 3; attacker.j = 15; break;

	case E1: attacker.i = 4; attacker.j = 0; break;
	case E2: attacker.i = 4; attacker.j = 1; break;
	case E3: attacker.i = 4; attacker.j = 2; break;
	case E4: attacker.i = 4; attacker.j = 3; break;
	case E5: attacker.i = 4; attacker.j = 4; break;
	case E6: attacker.i = 4; attacker.j = 5; break;
	case E7: attacker.i = 4; attacker.j = 6; break;
	case E8: attacker.i = 4; attacker.j = 7; break;
	case E9: attacker.i = 4; attacker.j = 8; break;
	case E10: attacker.i = 4; attacker.j = 9; break;
	case E11: attacker.i = 4; attacker.j = 10; break;
	case E12: attacker.i = 4; attacker.j = 11; break;
	case E13: attacker.i = 4; attacker.j = 12; break;
	case E14: attacker.i = 4; attacker.j = 13; break;
	case E15: attacker.i = 4; attacker.j = 14; break;
	case E16: attacker.i = 4; attacker.j = 15; break;

	case F1: attacker.i = 5; attacker.j = 0; break;
	case F2: attacker.i = 5; attacker.j = 1; break;
	case F3: attacker.i = 5; attacker.j = 2; break;
	case F4: attacker.i = 5; attacker.j = 3; break;
	case F5: attacker.i = 5; attacker.j = 4; break;
	case F6: attacker.i = 5; attacker.j = 5; break;
	case F7: attacker.i = 5; attacker.j = 6; break;
	case F8: attacker.i = 5; attacker.j = 7; break;
	case F9: attacker.i = 5; attacker.j = 8; break;
	case F10: attacker.i = 5; attacker.j = 9; break;
	case F11: attacker.i = 5; attacker.j = 10; break;
	case F12: attacker.i = 5; attacker.j = 11; break;
	case F13: attacker.i = 5; attacker.j = 12; break;
	case F14: attacker.i = 5; attacker.j = 13; break;
	case F15: attacker.i = 5; attacker.j = 14; break;
	case F16: attacker.i = 5; attacker.j = 15; break;

	case G1: attacker.i = 6; attacker.j = 0; break;
	case G2: attacker.i = 6; attacker.j = 1; break;
	case G3: attacker.i = 6; attacker.j = 2; break;
	case G4: attacker.i = 6; attacker.j = 3; break;
	case G5: attacker.i = 6; attacker.j = 4; break;
	case G6: attacker.i = 6; attacker.j = 5; break;
	case G7: attacker.i = 6; attacker.j = 6; break;
	case G8: attacker.i = 6; attacker.j = 7; break;
	case G9: attacker.i = 6; attacker.j = 8; break;
	case G10: attacker.i = 6; attacker.j = 9; break;
	case G11: attacker.i = 6; attacker.j = 10; break;
	case G12: attacker.i = 6; attacker.j = 11; break;
	case G13: attacker.i = 6; attacker.j = 12; break;
	case G14: attacker.i = 6; attacker.j = 13; break;
	case G15: attacker.i = 6; attacker.j = 14; break;
	case G16: attacker.i = 6; attacker.j = 15; break;

	case H1: attacker.i = 7; attacker.j = 0; break;
	case H2: attacker.i = 7; attacker.j = 1; break;
	case H3: attacker.i = 7; attacker.j = 2; break;
	case H4: attacker.i = 7; attacker.j = 3; break;
	case H5: attacker.i = 7; attacker.j = 4; break;
	case H6: attacker.i = 7; attacker.j = 5; break;
	case H7: attacker.i = 7; attacker.j = 6; break;
	case H8: attacker.i = 7; attacker.j = 7; break;
	case H9: attacker.i = 7; attacker.j = 8; break;
	case H10: attacker.i = 7; attacker.j = 9; break;
	case H11: attacker.i = 7; attacker.j = 10; break;
	case H12: attacker.i = 7; attacker.j = 11; break;
	case H13: attacker.i = 7; attacker.j = 12; break;
	case H14: attacker.i = 7; attacker.j = 13; break;
	case H15: attacker.i = 7; attacker.j = 14; break;
	case H16: attacker.i = 7; attacker.j = 15; break;

	case I1: attacker.i = 8; attacker.j = 0; break;
	case I2: attacker.i = 8; attacker.j = 1; break;
	case I3: attacker.i = 8; attacker.j = 2; break;
	case I4: attacker.i = 8; attacker.j = 3; break;
	case I5: attacker.i = 8; attacker.j = 4; break;
	case I6: attacker.i = 8; attacker.j = 5; break;
	case I7: attacker.i = 8; attacker.j = 6; break;
	case I8: attacker.i = 8; attacker.j = 7; break;
	case I9: attacker.i = 8; attacker.j = 8; break;
	case I10: attacker.i = 8; attacker.j = 9; break;
	case I11: attacker.i = 8; attacker.j = 10; break;
	case I12: attacker.i = 8; attacker.j = 11; break;
	case I13: attacker.i = 8; attacker.j = 12; break;
	case I14: attacker.i = 8; attacker.j = 13; break;
	case I15: attacker.i = 8; attacker.j = 14; break;
	case I16: attacker.i = 8; attacker.j = 15; break;

	case J1: attacker.i = 9; attacker.j = 0; break;
	case J2: attacker.i = 9; attacker.j = 1; break;
	case J3: attacker.i = 9; attacker.j = 2; break;
	case J4: attacker.i = 9; attacker.j = 3; break;
	case J5: attacker.i = 9; attacker.j = 4; break;
	case J6: attacker.i = 9; attacker.j = 5; break;
	case J7: attacker.i = 9; attacker.j = 6; break;
	case J8: attacker.i = 9; attacker.j = 7; break;
	case J9: attacker.i = 9; attacker.j = 8; break;
	case J10: attacker.i = 9; attacker.j = 9; break;
	case J11: attacker.i = 9; attacker.j = 10; break;
	case J12: attacker.i = 9; attacker.j = 11; break;
	case J13: attacker.i = 9; attacker.j = 12; break;
	case J14: attacker.i = 9; attacker.j = 13; break;
	case J15: attacker.i = 9; attacker.j = 14; break;
	case J16: attacker.i = 9; attacker.j = 15; break;

	case K1: attacker.i = 10; attacker.j = 0; break;
	case K2: attacker.i = 10; attacker.j = 1; break;
	case K3: attacker.i = 10; attacker.j = 2; break;
	case K4: attacker.i = 10; attacker.j = 3; break;
	case K5: attacker.i = 10; attacker.j = 4; break;
	case K6: attacker.i = 10; attacker.j = 5; break;
	case K7: attacker.i = 10; attacker.j = 6; break;
	case K8: attacker.i = 10; attacker.j = 7; break;
	case K9: attacker.i = 10; attacker.j = 8; break;
	case K10: attacker.i = 10; attacker.j = 9; break;
	case K11: attacker.i = 10; attacker.j = 10; break;
	case K12: attacker.i = 10; attacker.j = 11; break;
	case K13: attacker.i = 10; attacker.j = 12; break;
	case K14: attacker.i = 10; attacker.j = 13; break;
	case K15: attacker.i = 10; attacker.j = 14; break;
	case K16: attacker.i = 10; attacker.j = 15; break;

	case L1: attacker.i = 11; attacker.j = 0; break;
	case L2: attacker.i = 11; attacker.j = 1; break;
	case L3: attacker.i = 11; attacker.j = 2; break;
	case L4: attacker.i = 11; attacker.j = 3; break;
	case L5: attacker.i = 11; attacker.j = 4; break;
	case L6: attacker.i = 11; attacker.j = 5; break;
	case L7: attacker.i = 11; attacker.j = 6; break;
	case L8: attacker.i = 11; attacker.j = 7; break;
	case L9: attacker.i = 11; attacker.j = 8; break;
	case L10: attacker.i = 11; attacker.j = 9; break;
	case L11: attacker.i = 11; attacker.j = 10; break;
	case L12: attacker.i = 11; attacker.j = 11; break;
	case L13: attacker.i = 11; attacker.j = 12; break;
	case L14: attacker.i = 11; attacker.j = 13; break;
	case L15: attacker.i = 11; attacker.j = 14; break;
	case L16: attacker.i = 11; attacker.j = 15; break;

	default: break;
	}
}

void Map::setDefender(int tile)
{
	switch (tile)
	{
	case A1: defender.i = 0; defender.j = 0; break;
	case A2: defender.i = 0; defender.j = 1; break;
	case A3: defender.i = 0; defender.j = 2; break;
	case A4: defender.i = 0; defender.j = 3; break;
	case A5: defender.i = 0; defender.j = 4; break;
	case A6: defender.i = 0; defender.j = 5; break;
	case A7: defender.i = 0; defender.j = 6; break;
	case A8: defender.i = 0; defender.j = 7; break;
	case A9: defender.i = 0; defender.j = 8; break;
	case A10: defender.i = 0; defender.j = 9; break;
	case A11: defender.i = 0; defender.j = 10; break;
	case A12: defender.i = 0; defender.j = 11; break;
	case A13: defender.i = 0; defender.j = 12; break;
	case A14: defender.i = 0; defender.j = 13; break;
	case A15: defender.i = 0; defender.j = 14; break;
	case A16: defender.i = 0; defender.j = 15; break;

	case B1: defender.i = 1; defender.j = 0; break;
	case B2: defender.i = 1; defender.j = 1; break;
	case B3: defender.i = 1; defender.j = 2; break;
	case B4: defender.i = 1; defender.j = 3; break;
	case B5: defender.i = 1; defender.j = 4; break;
	case B6: defender.i = 1; defender.j = 5; break;
	case B7: defender.i = 1; defender.j = 6; break;
	case B8: defender.i = 1; defender.j = 7; break;
	case B9: defender.i = 1; defender.j = 8; break;
	case B10: defender.i = 1; defender.j = 9; break;
	case B11: defender.i = 1; defender.j = 10; break;
	case B12: defender.i = 1; defender.j = 11; break;
	case B13: defender.i = 1; defender.j = 12; break;
	case B14: defender.i = 1; defender.j = 13; break;
	case B15: defender.i = 1; defender.j = 14; break;
	case B16: defender.i = 1; defender.j = 15; break;

	case C1: defender.i = 2; defender.j = 0; break;
	case C2: defender.i = 2; defender.j = 1; break;
	case C3: defender.i = 2; defender.j = 2; break;
	case C4: defender.i = 2; defender.j = 3; break;
	case C5: defender.i = 2; defender.j = 4; break;
	case C6: defender.i = 2; defender.j = 5; break;
	case C7: defender.i = 2; defender.j = 6; break;
	case C8: defender.i = 2; defender.j = 7; break;
	case C9: defender.i = 2; defender.j = 8; break;
	case C10: defender.i = 2; defender.j = 9; break;
	case C11: defender.i = 2; defender.j = 10; break;
	case C12: defender.i = 2; defender.j = 11; break;
	case C13: defender.i = 2; defender.j = 12; break;
	case C14: defender.i = 2; defender.j = 13; break;
	case C15: defender.i = 2; defender.j = 14; break;
	case C16: defender.i = 2; defender.j = 15; break;

	case D1: defender.i = 3; defender.j = 0; break;
	case D2: defender.i = 3; defender.j = 1; break;
	case D3: defender.i = 3; defender.j = 2; break;
	case D4: defender.i = 3; defender.j = 3; break;
	case D5: defender.i = 3; defender.j = 4; break;
	case D6: defender.i = 3; defender.j = 5; break;
	case D7: defender.i = 3; defender.j = 6; break;
	case D8: defender.i = 3; defender.j = 7; break;
	case D9: defender.i = 3; defender.j = 8; break;
	case D10: defender.i = 3; defender.j = 9; break;
	case D11: defender.i = 3; defender.j = 10; break;
	case D12: defender.i = 3; defender.j = 11; break;
	case D13: defender.i = 3; defender.j = 12; break;
	case D14: defender.i = 3; defender.j = 13; break;
	case D15: defender.i = 3; defender.j = 14; break;
	case D16: defender.i = 3; defender.j = 15; break;

	case E1: defender.i = 4; defender.j = 0; break;
	case E2: defender.i = 4; defender.j = 1; break;
	case E3: defender.i = 4; defender.j = 2; break;
	case E4: defender.i = 4; defender.j = 3; break;
	case E5: defender.i = 4; defender.j = 4; break;
	case E6: defender.i = 4; defender.j = 5; break;
	case E7: defender.i = 4; defender.j = 6; break;
	case E8: defender.i = 4; defender.j = 7; break;
	case E9: defender.i = 4; defender.j = 8; break;
	case E10: defender.i = 4; defender.j = 9; break;
	case E11: defender.i = 4; defender.j = 10; break;
	case E12: defender.i = 4; defender.j = 11; break;
	case E13: defender.i = 4; defender.j = 12; break;
	case E14: defender.i = 4; defender.j = 13; break;
	case E15: defender.i = 4; defender.j = 14; break;
	case E16: defender.i = 4; defender.j = 15; break;

	case F1: defender.i = 5; defender.j = 0; break;
	case F2: defender.i = 5; defender.j = 1; break;
	case F3: defender.i = 5; defender.j = 2; break;
	case F4: defender.i = 5; defender.j = 3; break;
	case F5: defender.i = 5; defender.j = 4; break;
	case F6: defender.i = 5; defender.j = 5; break;
	case F7: defender.i = 5; defender.j = 6; break;
	case F8: defender.i = 5; defender.j = 7; break;
	case F9: defender.i = 5; defender.j = 8; break;
	case F10: defender.i = 5; defender.j = 9; break;
	case F11: defender.i = 5; defender.j = 10; break;
	case F12: defender.i = 5; defender.j = 11; break;
	case F13: defender.i = 5; defender.j = 12; break;
	case F14: defender.i = 5; defender.j = 13; break;
	case F15: defender.i = 5; defender.j = 14; break;
	case F16: defender.i = 5; defender.j = 15; break;

	case G1: defender.i = 6; defender.j = 0; break;
	case G2: defender.i = 6; defender.j = 1; break;
	case G3: defender.i = 6; defender.j = 2; break;
	case G4: defender.i = 6; defender.j = 3; break;
	case G5: defender.i = 6; defender.j = 4; break;
	case G6: defender.i = 6; defender.j = 5; break;
	case G7: defender.i = 6; defender.j = 6; break;
	case G8: defender.i = 6; defender.j = 7; break;
	case G9: defender.i = 6; defender.j = 8; break;
	case G10: defender.i = 6; defender.j = 9; break;
	case G11: defender.i = 6; defender.j = 10; break;
	case G12: defender.i = 6; defender.j = 11; break;
	case G13: defender.i = 6; defender.j = 12; break;
	case G14: defender.i = 6; defender.j = 13; break;
	case G15: defender.i = 6; defender.j = 14; break;
	case G16: defender.i = 6; defender.j = 15; break;

	case H1: defender.i = 7; defender.j = 0; break;
	case H2: defender.i = 7; defender.j = 1; break;
	case H3: defender.i = 7; defender.j = 2; break;
	case H4: defender.i = 7; defender.j = 3; break;
	case H5: defender.i = 7; defender.j = 4; break;
	case H6: defender.i = 7; defender.j = 5; break;
	case H7: defender.i = 7; defender.j = 6; break;
	case H8: defender.i = 7; defender.j = 7; break;
	case H9: defender.i = 7; defender.j = 8; break;
	case H10: defender.i = 7; defender.j = 9; break;
	case H11: defender.i = 7; defender.j = 10; break;
	case H12: defender.i = 7; defender.j = 11; break;
	case H13: defender.i = 7; defender.j = 12; break;
	case H14: defender.i = 7; defender.j = 13; break;
	case H15: defender.i = 7; defender.j = 14; break;
	case H16: defender.i = 7; defender.j = 15; break;

	case I1: defender.i = 8; defender.j = 0; break;
	case I2: defender.i = 8; defender.j = 1; break;
	case I3: defender.i = 8; defender.j = 2; break;
	case I4: defender.i = 8; defender.j = 3; break;
	case I5: defender.i = 8; defender.j = 4; break;
	case I6: defender.i = 8; defender.j = 5; break;
	case I7: defender.i = 8; defender.j = 6; break;
	case I8: defender.i = 8; defender.j = 7; break;
	case I9: defender.i = 8; defender.j = 8; break;
	case I10: defender.i = 8; defender.j = 9; break;
	case I11: defender.i = 8; defender.j = 10; break;
	case I12: defender.i = 8; defender.j = 11; break;
	case I13: defender.i = 8; defender.j = 12; break;
	case I14: defender.i = 8; defender.j = 13; break;
	case I15: defender.i = 8; defender.j = 14; break;
	case I16: defender.i = 8; defender.j = 15; break;

	case J1: defender.i = 9; defender.j = 0; break;
	case J2: defender.i = 9; defender.j = 1; break;
	case J3: defender.i = 9; defender.j = 2; break;
	case J4: defender.i = 9; defender.j = 3; break;
	case J5: defender.i = 9; defender.j = 4; break;
	case J6: defender.i = 9; defender.j = 5; break;
	case J7: defender.i = 9; defender.j = 6; break;
	case J8: defender.i = 9; defender.j = 7; break;
	case J9: defender.i = 9; defender.j = 8; break;
	case J10: defender.i = 9; defender.j = 9; break;
	case J11: defender.i = 9; defender.j = 10; break;
	case J12: defender.i = 9; defender.j = 11; break;
	case J13: defender.i = 9; defender.j = 12; break;
	case J14: defender.i = 9; defender.j = 13; break;
	case J15: defender.i = 9; defender.j = 14; break;
	case J16: defender.i = 9; defender.j = 15; break;

	case K1: defender.i = 10; defender.j = 0; break;
	case K2: defender.i = 10; defender.j = 1; break;
	case K3: defender.i = 10; defender.j = 2; break;
	case K4: defender.i = 10; defender.j = 3; break;
	case K5: defender.i = 10; defender.j = 4; break;
	case K6: defender.i = 10; defender.j = 5; break;
	case K7: defender.i = 10; defender.j = 6; break;
	case K8: defender.i = 10; defender.j = 7; break;
	case K9: defender.i = 10; defender.j = 8; break;
	case K10: defender.i = 10; defender.j = 9; break;
	case K11: defender.i = 10; defender.j = 10; break;
	case K12: defender.i = 10; defender.j = 11; break;
	case K13: defender.i = 10; defender.j = 12; break;
	case K14: defender.i = 10; defender.j = 13; break;
	case K15: defender.i = 10; defender.j = 14; break;
	case K16: defender.i = 10; defender.j = 15; break;

	case L1: defender.i = 11; defender.j = 0; break;
	case L2: defender.i = 11; defender.j = 1; break;
	case L3: defender.i = 11; defender.j = 2; break;
	case L4: defender.i = 11; defender.j = 3; break;
	case L5: defender.i = 11; defender.j = 4; break;
	case L6: defender.i = 11; defender.j = 5; break;
	case L7: defender.i = 11; defender.j = 6; break;
	case L8: defender.i = 11; defender.j = 7; break;
	case L9: defender.i = 11; defender.j = 8; break;
	case L10: defender.i = 11; defender.j = 9; break;
	case L11: defender.i = 11; defender.j = 10; break;
	case L12: defender.i = 11; defender.j = 11; break;
	case L13: defender.i = 11; defender.j = 12; break;
	case L14: defender.i = 11; defender.j = 13; break;
	case L15: defender.i = 11; defender.j = 14; break;
	case L16: defender.i = 11; defender.j = 15; break;

	default: break;
	}
}

coordenadas Map::getAttacker()
{
	return attacker;
}

coordenadas Map::getDefender()
{
	return defender;
}