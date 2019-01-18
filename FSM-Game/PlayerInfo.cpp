#include "PlayerInfo.h"


Player::Player()
{
	money = 5;	//El juego se empieza con $5
	team = TeamColor(rand() % MAX_PLAYERS + 1);
	cities = 0;
}

Player::~Player()
{
}

void Player::setMoney(int money)
{
	this->money = money;
}

int Player::getMoney()
{
	return money;
}

void Player::setTeam(TeamColor team)
{
	this->team = team;
}

TeamColor Player::getTeam()
{
	return team;
}

bool Player::doIStart()
{
	return (rand() % MAX_PLAYERS);
}

void Player::setAmmountOfCities(Map* myMap)
{
	cities = 0;
	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((myMap->getTile(i, j)->getBuilding()) != NULL) &&						//Chequeo si hay building
				((myMap->getTile(i, j)->getBuilding()->getType()).compare("c")==0) &&	//Chequeo si es una city
				((myMap->getTile(i, j)->getUnit()->getTeam()) == (getTeam())))			//Chequeo si es del player que busco
			{
				cities++;
			}
		}
	}
}

int Player::getAmmountOfCities()
{
	return cities;
}

string Player::getName()
{
	return name;
}

void Player::setName(string Name_)
{
	this->name = Name_;
}

