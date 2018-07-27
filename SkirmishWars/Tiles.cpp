#include "Tiles.h"


GenericTile::GenericTile()
{
	fogOfWar = true;
}

GenericTile::~GenericTile()
{
}

void GenericTile::addUnit(Unit *currUnit)
{
	this->currUnit = currUnit;
}

void GenericTile::removeUnit(Unit *currUnit)
{
}

void GenericTile::addBuilding(Building *currBuilding)
{
	this->currBuilding = currBuilding;
}

void GenericTile::removeBuilding(Building *currBuilding)
{
}

void GenericTile::addFog()
{
	fogOfWar = true;
}

void GenericTile::removeFog()
{
	fogOfWar = false;
}

Unit * GenericTile::getUnit()
{
	return currUnit;
}

Building * GenericTile::getBuilding()
{
	return currBuilding;
}

Terrain * GenericTile::getTerrain()
{
	return currTerrain;
}

void GenericTile::addTerrain(Terrain *currTerrain)
{
	this->currTerrain = currTerrain;
}

void GenericTile::removeTerrain(Terrain *currTerrain)
{
}
