#include "Building.h"


Building::Building()
{
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