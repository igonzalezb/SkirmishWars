#pragma once

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

class GenericTile
{
public:
	GenericTile();
	~GenericTile();

private:
	//Esto No se bien como hacerlo
	Unit *currUnit = NULL;
	Building *currBuilding = NULL;
	Terrain *currTerrain = NULL;
	bool fogOfWar;
};

GenericTile::GenericTile()
{
}

GenericTile::~GenericTile()
{
}