
#include "Game.h"
#include "PlayerInfo.h"
#include "Terrain.h"

Game::Game(ALLEGRO_DISPLAY* display)
{
	char * xml_path = XML_PATH;
	XML_Parser P = XML_ParserCreate(NULL);
	FILE * fp = fopen(xml_path, "rb");


	data = new Resources;

	XML_SetStartElementHandler(P, startTagCallback);	
	XML_SetEndElementHandler(P, endTagCallback);		
	XML_SetCharacterDataHandler(P, chararacterDataCallback);
	XML_SetUserData(P, data);
	readFileToBuffer(P, fp);
	fclose(fp);

	playerMe = new Player;
	playerYou = new Player;
	myMap = new Map;
	graphics = new MapGraphics(display);
	youWinning = false;
	IWantToPlayAgain = false;
	youWantToPlayAgain = false;
	analysePlayAgain = false;
	
	
	defenseModifiers = new csvFile(ATTACK_TABLE, 14, 5);
	generateDefenseModifiersTable();
	iAmPlaying = false;
	playerChosen = false;
	Istart = false;
	endPlaying = false;
	analyseVictory = false;
	moving = false;
	attacking = false;
	purchasing = false;
	boardingAPC = false;
	unboardingAPC = false;

	error = false;
	quit = false;
}

Game::~Game()
{
	delete defenseModifiers;
	delete playerMe;
	delete playerYou;
	delete myMap;
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

	if (myMap->getTile(getDefender().i, getDefender().j)->getBuilding() != NULL)
	{
		myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().road)));
	}
	else
	{
		if (myMap->getTile(getDefender().i, getDefender().j)->getTerrain()->getType().compare("a") == 0)
		{
			myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().road)));
		}
		else if (myMap->getTile(getDefender().i, getDefender().j)->getTerrain()->getType().compare("r") == 0)
		{
			myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().river)));
		}
		else if (myMap->getTile(getDefender().i, getDefender().j)->getTerrain()->getType().compare("f") == 0)
		{
			myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().forest)));
		}
		else if (myMap->getTile(getDefender().i, getDefender().j)->getTerrain()->getType().compare("h") == 0)
		{
			myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().hills)));
		}
		else if (myMap->getTile(getDefender().i, getDefender().j)->getTerrain()->getType().compare("t") == 0)
		{
			myMap->getTile(getDefender().i, getDefender().j)->getUnit()->setCurrMp(to_string(stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getCurrMp()) - stoi(myMap->getTile(getDefender().i, getDefender().j)->getUnit()->getMc().plain)));
		}
	}
	myMap->getTile(getDefender().i, getDefender().j)->toogleIsSelected(false);
}


void Game::attack()
{
	string symbol = myMap->getTile(defender.i,defender.j)->getUnit()->getSymbol();
	int firepower, inicialDamage, finalDamage, dieOnChart;

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

	myMap->getTile(defender.i, defender.j)->getUnit()->setHp((myMap->getTile(defender.i, defender.j)->getUnit()->getHp()) - finalDamage);

	if ((myMap->getTile(defender.i, defender.j)->getUnit()->getHp())<=0)
	{
		myMap->getTile(defender.i, defender.j)->removeUnit();
	}
}

//antes de llamar a esta funcion debo setear el attacker con la unidad que este encima de un building que no es propio 
void Game::captureProperty(Player* pAttacker)
{
		if ((myMap->getTile(attacker.i, attacker.j)->getUnit()->getHp()) < 5)//Si la unidad que conquista esta reducida
		{
			myMap->getTile(attacker.i, attacker.j)->getBuilding()->setCp((myMap->getTile(attacker.i, attacker.j)->getBuilding()->getCp()) - 1);
		}
		else//Si la que conquista NO esta reducida
		{
			myMap->getTile(attacker.i, attacker.j)->getBuilding()->setCp((myMap->getTile(attacker.i, attacker.j)->getBuilding()->getCp()) - 2);
		}

	attacker.i = NULL;
	attacker.j = NULL;
	defender.i = NULL;
	defender.j = NULL;
}

void Game::purchase(Player* player) //!!!PREVIAMENTE tienen que haber guardado en defender.i y defender.j las coordenadas del lugar al que quieren poner la unidad nueva.
{
	myMap->getTile(defender.i, defender.j)->setUnit(newUnit);
	player->setMoney((player->getMoney())-(stoi(newUnit->getCost())));
	cout << "SE COMPRO Y SE ESTA COMPARANDO CONNNN:" << newUnit->getType() << endl;
	if (newUnit->getType().compare("ap1") == 0 || newUnit->getType().compare("ap2") == 0)
	{
		myMap->getTile(defender.i, defender.j)->getUnit()->arregloNaveAPC[0] = NULL;
		myMap->getTile(defender.i, defender.j)->getUnit()->arregloNaveAPC[1] = NULL;
	}
}

bool Game::didHeWin() 
{
	int hq = 0, units = 0;
	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			if (((myMap->getTile(i,j)->getUnit()) != NULL) &&
				((myMap->getTile(i, j)->getUnit()->getTeam()) == (playerMe->getTeam())))
			{
				units++;
			}
			if ((myMap->getTile(i,j)->getBuilding()!=NULL)&&
				((((myMap->getTile(i, j)->getBuilding()->getType()).compare("q") == 0) || (myMap->getTile(i, j)->getBuilding()->getType()).compare("q1")==0) || ((myMap->getTile(i, j)->getBuilding()->getType()).compare("q2")==0)) &&
				((myMap->getTile(i,j)->getBuilding()->getTeam())==playerMe->getTeam()))
			{
				hq++;
			}
		}
	}
#ifdef DEBUG
	cout << "Cantidad de HQ: " << hq << endl;
	cout << "Cantidad de units: " << units << endl;
#endif // DEBUG

	if((units == 0)||(hq == 0))		//Si no tengo mas unidades o no tengo mas HQ, significa que el otro gana.
	{
#ifdef DEBUG
		cout << "Entro al if de he won" << endl;
#endif // DEBUG

		youWinning = true;
	}

	return youWinning;
}

void Game::setYouWinning(bool youWinning_)
{
	youWinning = youWinning_;
}

bool Game::getYouWinning()
{
	return youWinning;
}


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

void Game::setIamPlaying(bool now)
{
	iAmPlaying = now;
}

bool Game::getIamPlaying()
{
	return iAmPlaying;
}

void Game::chooseWhoStarts()
{
#ifdef DEBUG
	cout << "Entra al random de who starts" << endl;
#endif // DEBUG

	Istart = rand() % 2;
	//Istart = true;
	if (Istart)
	{
		iAmPlaying = true;
	}
	playerChosen = true;
}

void Game::setEndPlaying(bool endPlaying_)
{
	endPlaying = endPlaying_;
}

bool Game::getEndPlaying()
{
	return endPlaying;
}

void Game::setIWantToPlayAgain(bool playAgain)
{
	IWantToPlayAgain = playAgain;
}

bool Game::getIWantToPlayAgain()
{
	return IWantToPlayAgain;
}

void Game::setYouWantToPlayAgain(bool playAgain)
{
	youWantToPlayAgain = playAgain;
}

bool Game::getYouWantToPlayAgain()
{
	return youWantToPlayAgain;
}

void Game::setAnalysePlayAgain(bool yes_no)
{
	this->analysePlayAgain = yes_no;
}

bool Game::getAnalysePlayAgain()
{
	return analysePlayAgain;
}

void Game::setAnalyseVictory(bool analyse)
{
	analyseVictory = analyse;
}

bool Game::getAnalyseVictory()
{
	return analyseVictory;
}

void Game::boardUnit()
{
	cout << "ENTRA A BOARDUNITTTTTT!!" << endl;
	if (myMap->getTile((getDefender().i),getDefender().j)->getUnit()->arregloNaveAPC[0] == NULL)
	{
		cout << "ENTRA AL PRIMER IFFFFFFF!!!!!!!!" << endl;
		//el arreglo en 0 esta vacio asiq cargo la unidad ahi
		myMap->getTile(getDefender().i,getDefender().j)->getUnit()->arregloNaveAPC[0] = myMap->getTile(getAttacker().i, getAttacker().j)->getUnit();
		myMap->getTile(getAttacker().i, getAttacker().j)->setUnit(NULL);
	

	}

	else if(myMap->getTile((getDefender().i), getDefender().j)->getUnit()->arregloNaveAPC[1] == NULL)
	{
		cout << "ENTRA AL SEGUNDO IFFFFFFFFFFFF" << endl;
		//el arreglo en 1 esta vacio asiq cargo la unidad ahi
		myMap->getTile(getDefender().i, getDefender().j)->getUnit()->arregloNaveAPC[1] = myMap->getTile(getAttacker().i, getAttacker().j)->getUnit();
		myMap->getTile(getAttacker().i, getAttacker().j)->setUnit(NULL);

	}

}

void Game::unboardUnit()
{
	cout << "ENTRA A unBOARDUNITTTTTT!!" << endl;
	if (myMap->getTile(getAttacker().i, getAttacker().j)->getUnit()->arregloNaveAPC[1] != NULL)
	{
		//esta cargado el arreglo en 1 asiq descargo esa unidad
		cout << "DESCARGA LA UNIDAD EN [1]" << endl;
		myMap->getTile(getDefender().i, getDefender().j)->setUnit(myMap->getTile(getAttacker().i, getAttacker().j)->getUnit()->arregloNaveAPC[1]);
		myMap->getTile(getAttacker().i, getAttacker().j)->getUnit()->arregloNaveAPC[1] = NULL;
	}
	else
	{
		cout << "DESCARGA LA UNIDAD EN [0]" << endl;
		//esta cargardo el arreglo en 0 asiq descargo esa unidad
		myMap->getTile(getDefender().i, getDefender().j)->setUnit(myMap->getTile(getAttacker().i, getAttacker().j)->getUnit()->arregloNaveAPC[0]);
		myMap->getTile(getAttacker().i, getAttacker().j)->getUnit()->arregloNaveAPC[0] = NULL;
	}
		
		
}