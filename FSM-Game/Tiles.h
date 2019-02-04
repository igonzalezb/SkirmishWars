#pragma once

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

class GenericTile
{
public:
	GenericTile();
	~GenericTile();
	void addBuilding(Building *currBuilding);
	void removeBuilding();
	void addTerrain(Terrain *currTerrain);
	void removeTerrain(Terrain *currTerrain);
	void addUnit(Unit *currUnit);
	void removeUnit();
	void addFog();
	void removeFog();
	bool getFog();
	Unit* getUnit();
	void setUnit(Unit* newUnit);
	Building* getBuilding();
	Terrain* getTerrain();
	bool isSelected();
	void toogleIsSelected(bool _selected);

private:
	Unit *currUnit = NULL;
	Building *currBuilding = NULL;
	Terrain *currTerrain = NULL;
	bool fogOfWar;
	bool _selected;
};

