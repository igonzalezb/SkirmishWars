#include "Building.h"


Building::Building()
{
	fogOfWar = true;
	team = WHITE;
}

Building::Building(string hp, string name, string path, string type, string team)
{
	fogOfWar = true;
	this->hp = hp;
	this->name = name;
	this->type = type;

	this->team = TeamColor(stoi(team));

	char temp[50];
	sprintf(temp, path.c_str(), this->team);
	this->path = temp;
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
	/*char temp[50];
	sprintf(temp, path.c_str(),  this->team);
	this->path = temp;*/
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