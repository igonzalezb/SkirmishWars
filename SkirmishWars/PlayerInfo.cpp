#include "PlayerInfo.h"


Player::Player()
{
	money = 5;	//El juego se empieza con $5
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

void Player::setTeam(int team)
{
	this->team = team;
}

int Player::getTeam()
{
	return team;
}

bool Player::doIStart()
{
	return (rand() % MAX_PLAYERS);
}
