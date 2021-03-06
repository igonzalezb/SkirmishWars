#include "PlayerInfo.h"


Player::Player()
{
	money = 5;	//El juego se empieza con $5
	teamcolor = TeamColor(rand() % MAX_PLAYERS + 1);
	team = NEUTRO;
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

void Player::setTeam(TeamNumber team)
{
	this->team = team;
}

TeamNumber Player::getTeam()
{
	return this->team;
}

bool Player::doIStart()
{
	return (rand() % MAX_PLAYERS);
}

void Player::setAmmountOfCities(Map* myMap)
{
	cities = 0;
	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			if (((myMap->getTile(i, j)->getBuilding()) != NULL) && (myMap->getTile(i, j)->getUnit() != NULL) &&		//Chequeo si hay building
				(((myMap->getTile(i, j)->getBuilding()->getType()).compare("c1")==0) || 
				((myMap->getTile(i, j)->getBuilding()->getType()).compare("c2") == 0)) &&							//Chequeo si es una city
				((myMap->getTile(i, j)->getUnit()->getTeam()) == (team))&&
				(myMap->getTile(i, j)->getBuilding()->getTeam()==(team)))											//Chequeo si es del player que busco
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

