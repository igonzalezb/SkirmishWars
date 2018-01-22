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
};

GenericTile::GenericTile()
{
}

GenericTile::~GenericTile()
{
}