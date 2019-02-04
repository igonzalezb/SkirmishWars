#include "Tiles.h"

//VER: aparentemente si hay una factory en un tile, no hay terreno
//DEBIDO A ESO, VER SI HAY QUE CAMBIAR ALGO EN COMO ESTA GUARDADA LA INFO O SI QUEDA COMO ESTA, CON buildings y terrains separados

GenericTile::GenericTile()
{
	fogOfWar = true;		//VOLVER A CAMBIAR! - va en true
	_selected = false;
}

GenericTile::~GenericTile()
{
	if (currBuilding != NULL)
		delete currBuilding;
	if (currUnit != NULL)
		delete currUnit; //!!!!!!!!
	if (currTerrain != NULL)
		delete currTerrain;
}

void GenericTile::addUnit(Unit *currUnit)
{
	this->currUnit = currUnit;
}

void GenericTile::removeUnit()
{
	if (currUnit != NULL)
		delete currUnit; //!!!!!!!
	currUnit = NULL;
}

void GenericTile::addBuilding(Building *currBuilding)
{
	this->currBuilding = currBuilding;
}

void GenericTile::removeBuilding()
{
	if (currBuilding != NULL)
		delete currBuilding;
	currBuilding = NULL;
}

void GenericTile::addFog()
{
	fogOfWar = true;
}

void GenericTile::removeFog()
{
	fogOfWar = false;
}

bool GenericTile::getFog()
{
	return fogOfWar;
}

Unit * GenericTile::getUnit()
{
	return currUnit;
}

void GenericTile::setUnit(Unit* newUnit)
{
	currUnit = newUnit;
}

Building * GenericTile::getBuilding()
{
	return currBuilding;
}

Terrain * GenericTile::getTerrain()
{
	return currTerrain;
}

bool GenericTile::isSelected()
{
	return _selected;
}

void GenericTile::toogleIsSelected(bool _selected)
{
	this->_selected = _selected;
}

void GenericTile::addTerrain(Terrain *currTerrain)
{
	this->currTerrain = currTerrain;
}

void GenericTile::removeTerrain()
{
	if (currTerrain != NULL)
		delete currTerrain;
	currTerrain = NULL;
}
