#include "Terrain.h"

Terrain::Terrain()
{
	fogOfWar = true;
	connections = { false, false, false, false };
}

Terrain::~Terrain()
{
}
void Terrain::setName(string name)
{
	this->name = name;
}

void Terrain::setType(string type)
{
	this->type = type;
}

void Terrain::setPath(string path)
{
	this->path = path;
}

string Terrain::getPath()
{
	return path;
}

string Terrain::getName()
{
	return name;
}

string Terrain::getType()
{
	return type;
}

void Terrain::setConnections()
{
}

void Terrain::removeFog()
{
	fogOfWar = false;
}