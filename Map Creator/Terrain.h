#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum { RIVER, ROAD, GRASS, TREE, MOUNTAIN} TerrainType;

struct TerrStruct
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
	string pathName;
	TerrainType type;
};