#include "Terrain.h"

Terrain::Terrain(string pathName, string type)
{
	this->pathName = pathName;
	this->type = type;
	fogOfWar = true;
}

void Terrain::setConnection()
{
}

void Terrain::removeFog()
{
	fogOfWar = false;
}
