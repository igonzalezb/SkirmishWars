#pragma once
#include <iostream>
#include <list>
#include <string>

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

enum State {
	IDLE, RESOURCES,

	BUILDING, BUILDING_ITEM, B_NAME, B_HP, B_PATH,	//Buildings Status

	TERRAIN, TERRAIN_ITEM, T_NAME, T_PATH,	//Terrains Status

	UNIT, UNIT_ITEM, U_NAME, U_HP, U_PATH, COST, MP, DEFENCE, //Units Status
	RANGEMIN, RANGEMAX, PLAINCOST, ROADCOST, FORESTCOST, RIVERCOST, HILLSCOST,
	FPNORMAL, FPREDUCED, MOON, STAR, TRIANGLE, CIRCLE,	//Units FP Points
	_IGNORE
};

using namespace std;

class Resources
{
private:
	list<Building> buildings;
	list<Terrain> terrains;
	list<Unit> units;
	//Building * CurrentBuilding;
	//Terrain * CurrentTerrain;
	//Unit * CurrentUnit;
	State feedState;
public:
	Resources();
	~Resources();
	void setFeedState(State state);
	State getFeedSate();
	void addTerrain();
	void addBuilding();
	void addUnit();
	Terrain& getLastTerrain();
	Building& getLastBuilding();
	Unit& getLastUnit();
	list<Terrain>& getTerrainList();
	list<Building>& getBuildingList();
	list<Unit>& getUnitList();

};
