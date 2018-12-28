
#include "Resources.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Resources::Resources()
{
	feedState = IDLE;
	//CurrentNews = &Building.back();
}

Resources::~Resources()
{
}

void Resources::setFeedState(State state)
{
	feedState = state;
}

State Resources::getFeedSate()
{
	return feedState;
}

void Resources::addTerrain()
{
	Terrain current;
	terrains.push_back(current);
}

void Resources::addBuilding()
{
	Building current;
	buildings.push_back(current);
}

void Resources::addUnit()
{
	Unit current;
	units.push_back(current);
}

Terrain & Resources::getLastTerrain()
{
	return terrains.back();
}

Building & Resources::getLastBuilding()
{
	return buildings.back();
}

Unit & Resources::getLastUnit()
{
	return units.back();
}

list<Terrain>& Resources::getTerrainList()
{
	return terrains;
}

list<Building>& Resources::getBuildingList()
{
	return buildings;
}

list<Unit>& Resources::getUnitList()
{
	return units;
}
