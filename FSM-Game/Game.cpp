
#include "Game.h"
#include "PlayerInfo.h"

Game::Game()
{

}

Game::~Game()
{
//destruir los players;
}


void Game::IcaptureProperty()
{
	if (((myMap->getTile(attacker.i, attacker.j)->getUnit()->getTeam()) == (playerMe->getTeam())) &&
		(((myMap->getTile(attacker.i, attacker.j)->getUnit()->getType().compare("infantry")) == 0) || //VER si esto y la linea de abajo estan bien o no
		((myMap->getTile(attacker.i, attacker.j)->getUnit()->getType().compare("mech")) == 0))&&
		((myMap->getTile(defender.i,defender.j)->getBuilding())!= NULL))
	{

	}
}

string building("city");
int iguales = building.compare("city");

/////////////////////////////////// PASAR LAS SIGUIENTES FUNCIONES ACA
void setAttacker();
void setDefender();
coordenadas getAttacker();
coordenadas getDefender();