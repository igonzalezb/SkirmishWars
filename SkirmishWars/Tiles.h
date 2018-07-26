#pragma once

#include "Unit.h"

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
};

GenericTile::GenericTile()
{
}

GenericTile::~GenericTile()
{
}