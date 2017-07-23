#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum { RIVER, ROAD, GRASS, TREE, MOUNTAIN} TerrainType;

struct River
{
	bool up;
	bool down;
	bool left;
	bool right;

};

class Terrain
{
public:
	Terrain();
	~Terrain();

private:
	string psthName;
	TerrainType type;



};

Terrain::~Terrain()
{
}