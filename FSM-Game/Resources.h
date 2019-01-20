#pragma once
#include <iostream>
#include <list>
#include <string>

#include "Terrain.h"
#include "Unit.h"
#include "Building.h"

enum State {
	IDLE, RESOURCES, _IGNORE,

	BUILDING, BUILDING_ITEM, B_NAME, B_HP, B_PATH, B_TYPE,	//Buildings Status

	TERRAIN, TERRAIN_ITEM, T_NAME, T_PATH, T_TYPE,	//Terrains Status

	UNIT, UNIT_ITEM, U_NAME, U_HP, U_PATH, COST, MP, DEFENSE, U_TYPE, U_SYMBOL, //Units Status
	RANGEMIN, RANGEMAX, PLAINCOST, ROADCOST, FORESTCOST, RIVERCOST, HILLSCOST,
	FPNORMAL, FPREDUCED, N_MOON, N_STAR, N_TRIANGLE, N_CIRCLE, N_SQUARE, R_MOON, R_STAR, R_TRIANGLE, R_CIRCLE, R_SQUARE	//Units FP Points
	
};

using namespace std;

class Resources
{
private:
	list<Building> buildings;
	list<Terrain> terrains;
	list<Unit> units;
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
	//Unit* getLastUnit();
	list<Terrain>& getTerrainList();
	list<Building>& getBuildingList();
	list<Unit>& getUnitList();

};
