#pragma once

#include "Tiles.h"

#include "Map.h"
#define HQ(x)		"q"#x
#define CITY(x)		"c"#x
#define FACTORY(x)	"m"#x

class Building: public GenericTile
{
public:
	Building();
	~Building();

private:
	int Health;
	TeamColor team;
};

Building::Building()
{
}

Building::~Building()
{
}