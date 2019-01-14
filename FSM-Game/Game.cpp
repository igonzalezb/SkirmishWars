
#include "Game.h"
#include "PlayerInfo.h"

Game::Game()
{

}

Game::~Game()
{
//destruir los players;
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

void Game::purchase(Player* player,string newUnit) //!!!PREVIAMENTE tienen que haber guardado en defender.i y defender.j las coordenadas del lugar al que quieren poner la unidad nueva.
{
	if (((myMap->getTile(defender.i,defender.j)->getBuilding()->getType().compare("m"))==0)&& //VERIFICAR si el type de la factory es una m
		((myMap->getTile(defender.i,defender.j)->getBuilding()->getTeam())==(player->getTeam()))&&
		((myMap->getTile(defender.i,defender.j)->getUnit()) != NULL))//HACER:agregar que chequee si el player tiene plata suficiente para comprar la unit que quiere
	{
		//HACER:
		//si se cumple todo eso y le alcanza la plata:
		//poner la unit en ese tile del mapa y asignarle el equipo del comprador (player)
		//restarle el costo a la money del player
	}
}

/////////////////////////////////// PASAR LAS SIGUIENTES FUNCIONES ACA
void setAttacker();
void setDefender();
coordenadas getAttacker();
coordenadas getDefender();