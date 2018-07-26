#include "Building.h"


Building::Building()
{
	fogOfWar = true;
	team = WHITE;
}

Building::Building(string hp, string name, string path)
{
	fogOfWar = true;
	team = WHITE;
	this->hp = hp;
	this->name = name;
	this->path = path;
}

Building::~Building()
{
}

void Building::setName(string name)
{
	this->name = name;
}

void Building::setHp(string hp)
{
	this->hp = hp;
}

void Building::setPath(string path)
{
	this->path = path;
}

string Building::getPath()
{
	return path;
}

string Building::getHp()
{
	return hp;
}

string Building::getName()
{
	return name;
}

void Building::setTeam(TeamColor team)
{
	type += to_string(team);			//PROBAR!!!!
	this->team = team;
}

TeamColor Building::getTeam()
{
	return team;
}

string Building::getType()
{
	return type;
}

void Building::setType(string type)
{
	this->type = type;
}

void Building::removeFog()
{
	fogOfWar = false;
}
