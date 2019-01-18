#pragma once

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

class Generic

{
public:
	GenericTile();
	~GenericTile();
	void addBuilding(Building *currBuilding);
	void removeBuilding(Building *currBuilding);
	void addTerrain(Terrain *currTerrain);
	void removeTerrain(Terrain *currTerrain);
	void addUnit(Unit *currUnit);
	void removeUnit(Unit *currUnit);
	void addFog();
	void removeFog();
	bool getFog();
	Unit* getUnit();
	void setUnit(Unit* newUnit);
	Building* getBuilding();
	Terrain* getTerrain();
	

private:
	Unit *currUnit = NULL;
	Building *currBuilding = NULL;
	Terrain *currTerrain = NULL;
	bool fogOfWar;
};

