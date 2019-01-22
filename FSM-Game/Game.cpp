
#include "Game.h"
#include "PlayerInfo.h"
#include "Terrain.h"

Game::Game()
{
	char * xml_path = XML_PATH;
	XML_Parser P = XML_ParserCreate(NULL);
	FILE * fp = fopen(xml_path, "rb");
	
	data = new Resources;

	XML_SetStartElementHandler(P, startTagCallback);	// Función que va a encontrar cuando aparece un Start tag;
	XML_SetEndElementHandler(P, endTagCallback);		//Función que va a encontrar cuando aparece un End tag;
	XML_SetCharacterDataHandler(P, chararacterDataCallback);
	XML_SetUserData(P, data);
	readFileToBuffer(P, fp);
	fclose(fp);

	playerMe = new Player;
	playerYou = new Player;
	myMap = new Map;
	//graphics = new MapGraphics;
	notWinning = true;
	myMap->generateTilesArray(data->getBuildingList(), data->getTerrainList(), data->getUnitList());
	
	//graphics->loadBitmaps(myMap);

	defenseModifiers = new csvFile(ATTACK_TABLE, 14, 5);
	generateDefenseModifiersTable();
	playing = false;
	playerChosen = false;
	Istart = false;
}

Game::~Game()
{
	delete defenseModifiers;
	delete playerMe;
	delete playerYou;
	delete myMap;
	//destruir los players;
}


void Game::generateDefenseModifiersTable()
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
}

void Game::move()
{
	myMap->getTile(getDefender().i, getDefender().j)->setUnit(myMap->getTile(getAttacker().i, getAttacker().j)->getUnit());
	myMap->getTile(getAttacker().i, getAttacker().j)->setUnit(NULL);
}

//void Map::attack(coordenadas attacker, coordenadas defender) 
void Game::attack()
{
	string symbol = myMap->getTile(defender.i,defender.j)->getUnit()->getSymbol();
	int firepower, inicialDamage, finalDamage, dieOnChart;
	//if (stoi(tilesArray[attacker.i][attacker.j]->getUnit()->getHp()) < 5)

	if (myMap->getTile(attacker.i, attacker.j)->getUnit() != NULL) {
		cout << "HP de UNIT attacker:" << myMap->getTile(attacker.i, attacker.j)->getUnit()->getHp() << endl;
	}

	if (myMap->getTile(attacker.i, attacker.j)->getUnit()->getHp() < 5) //menor a 5 significa REDUCED
	{
		if (symbol == "moon")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpReduced().moon);
		else if (symbol == "star")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpReduced().star);
		else if (symbol == "square")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpReduced().square);
		else if (symbol == "triangle")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpReduced().triangle);
		else if (symbol == "circle")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpReduced().circle);
	}
	else
	{
		if (symbol == "moon")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpNormal().moon);
		else if (symbol == "star")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpNormal().star);
		else if (symbol == "square")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpNormal().square);
		else if (symbol == "triangle")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpNormal().triangle);
		else if (symbol == "circle")
			firepower = stoi(myMap->getTile(attacker.i, attacker.j)->getUnit()->getFpNormal().circle);
	}


	inicialDamage = firepower - stoi(myMap->getTile(defender.i, defender.j)->getUnit()->getdefense());

	// HACER aca el crossreference entre el inicial damage y el terreno en el que esta el defender!!!!!!!!!!!!!!!
	// finalDamage = ...
	// dieOnChart =.... (ESTAS DOS VARIABLES SALEN DE ENTRAR A LA TABLA ESA CON EL FINAL DAMAGE Y EL TERRENO DEL DEFENDER)

	//die= rand() % 7 + 1; //VERIFICAR si esto tira un valor random entre 1 y 6.

	cout << "DADO: " << die << endl;

	int columna;
	string defenderTerrain = myMap->getTile(attacker.i, attacker.j)->getTerrain()->getType();

	if ((((myMap->getTile(attacker.i, attacker.j)->getBuilding()!=NULL) && (myMap->getTile(attacker.i, attacker.j)->getBuilding()->getType()).compare("q") == 0)) || (defenderTerrain.compare("h") == 0))
	{
		columna = 0;
	}
	else if (myMap->getTile(attacker.i, attacker.j)->getBuilding() != NULL)
	{
		columna = 1;
	}
	else if (defenderTerrain.compare("f") == 0)
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
	cout << "final damage = " << finalDamage << endl;

	myMap->getTile(defender.i, defender.j)->getUnit()->setHp((myMap->getTile(defender.i, defender.j)->getUnit()->getHp()) - finalDamage);

	cout << "HP luego del attack: " << myMap->getTile(defender.i, defender.j)->getUnit()->getHp() << endl;

	if ((myMap->getTile(defender.i, defender.j)->getUnit()->getHp())<=0)
	{
		myMap->getTile(defender.i, defender.j)->setUnit(NULL);
	}
	//mostrar la carta que tenga arriba el HP nuevo del defender, porque cambio su HP.
	//if HP < 5 : dar vuelta la carta y ahora esta REDUCED.

	attacker.i = NULL;
	attacker.j = NULL;
	defender.i = NULL;
	defender.j = NULL;
}


void Game::captureProperty(Player* pAttacker, Player* pDefender)
{
	if (((myMap->getTile(attacker.i, attacker.j)->getUnit()->getTeam()) == (pAttacker->getTeam())) && 
		(((myMap->getTile(attacker.i, attacker.j)->getUnit()->getType().compare("infantry")) == 0) || //VER si esto y la linea de abajo estan bien o no
		((myMap->getTile(attacker.i, attacker.j)->getUnit()->getType().compare("mech")) == 0))&&
		((myMap->getTile(defender.i,defender.j)->getBuilding())!= NULL)&&
		((myMap->getTile(defender.i, defender.j)->getBuilding()->getTeam()) != (pAttacker->getTeam())))
	{
		if ((myMap->getTile(attacker.i, attacker.j)->getUnit()->getHp()) < 5)//Si la unidad que conquista esta reducida
		{
			myMap->getTile(defender.i, defender.j)->getBuilding()->setCp((myMap->getTile(defender.i, defender.j)->getBuilding()->getCp()) - 1);
		}
		else//Si la que conquista NO esta reducida
		{
			myMap->getTile(defender.i, defender.j)->getBuilding()->setCp((myMap->getTile(defender.i, defender.j)->getBuilding()->getCp()) - 2);
		}
	}
	//HACER: Girar carta de la property o mostrar en algun  lado un contador con el valor nuevo del CP de la property atacada
	if ((myMap->getTile(defender.i, defender.j)->getBuilding()->getCp())<=0)
	{
		//en el tile donde estaba antes el building del oponente, poner el mismo building pero de mi equipo.
		myMap->getTile(defender.i, defender.j)->getBuilding()->setTeam(myMap->getTile(attacker.i, attacker.j)->getUnit()->getTeam());
	}
	attacker.i = NULL;
	attacker.j = NULL;
	defender.i = NULL;
	defender.j = NULL;
}

void Game::purchase(Player* player) //!!!PREVIAMENTE tienen que haber guardado en defender.i y defender.j las coordenadas del lugar al que quieren poner la unidad nueva.
{
	myMap->getTile(defender.i,defender.j)->setUnit(newUnit);
	myMap->getTile(defender.i, defender.j)->getUnit()->setTeam(player->getTeam());
	player->setMoney((player->getMoney())-(stoi(newUnit->getCost())));
}

bool Game::didHeWin() //LLAMARLA DESDE EL GENERADOR DE EVENTOS PROBABLEMENTE
{
	//int i, j;
	//for(i=0;i<FILA;i++)
	//{
	//	for (j = 0; j < COLUMNA; j++)
	//	{
	//		if (((myMap->getTile(i,j)->getUnit()) != NULL)&&
	//			((myMap->getTile(i, j)->getUnit()->getTeam())==(playerYou->getTeam())))
	//		{
	//			notWinning = false;
	//		}
	//		if ((myMap->getTile(i,j)->getBuilding()!=NULL)&&
	//			((myMap->getTile(i, j)->getBuilding()->getType()).compare("HQ"))&&
	//			((myMap->getTile(i,j)->getBuilding()->getTeam())==playerYou->getTeam()))//REVISAR como esta cargado el type del HQ 
	//		{
	//			notWinning = false;
	//		}
	//	}
	//}
	//if (!notWinning) //VER SI ESTE if VA AL GENERADOR DE EVENTOS!!!!!!!!!!!!!!
	//{
	//	return true;
	//	//GENERAR EL EVENTO YOU WON
	//}
	return false;
}

void Game::setNotWinning(bool nWinning)
{
	notWinning = nWinning;
}

bool Game::getNotWinning()
{
	return notWinning;
}

/////////////////////////////////// PASAR LAS SIGUIENTES FUNCIONES ACA
void Game::setAttacker(coordenadas newAttacker)
{
	attacker = newAttacker;
}

void Game::setAttacker(int i, int j)
{
	attacker.i = i;
	attacker.j = j;
}

void Game::setDefender(coordenadas newDefender)
{
	defender = newDefender;
}

void Game::setDefender(int _i, int _j)
{
	defender.i = _i;
	defender.j = _j;
}

//void Game::setTileSelected(coordenadas newTileSelected)
//{
//	tileSelected = newTileSelected;
//}

void Game::setTileSelected(int _i, int _j)
{
	tileSelected.i = _i;
	tileSelected.j = _j;
}

coordenadas Game::getAttacker()
{
	return attacker;
}

coordenadas Game::getDefender()
{
	return defender;
}

coordenadas Game::getTileSelected()
{
	return tileSelected;
} 

void Game::setNewUnit(Unit* unit) 
{
	newUnit = unit;
}

Unit* Game::getNewUnit()
{
	return newUnit;
}

int Game::getDie()
{
	return die;
}

void Game::setDie(int Dado_)
{
	this->die = Dado_;
}

void Game::setPlaying(bool now)
{
	playing = now;
}

bool Game::getPlaying()
{
	return playing;
}

void Game::chooseWhoStarts()
{
	//Istart = rand() % 2;
	Istart = true;
	playerChosen = true;
}

