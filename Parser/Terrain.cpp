#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}
void Terrain::setName(string name)
{
	this->name = name;
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