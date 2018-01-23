#include "Terrain.h"

Terrain::Terrain(string pathName, string type)
{
	this->pathName = pathName;
	this->type = type;

	connections = { false, false, false, false }; //Esto no me acuerdo si se hacia así
	fogOfWar = true;
}

void Terrain::setConnections()
{
}

void Terrain::removeFog()
{
	fogOfWar = false;
}
