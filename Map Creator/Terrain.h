#pragma once
#include <iostream>
#include <string>

using namespace std;

//typedef enum { RIVER, ROAD, PLAIN, FOREST, HILLS, CITIES, FACTORIES, HQ} TerrainType;

#define PLAIN		"t"
#define RIVER		"r"
#define ROAD		"a"
#define FOREST		"f"
#define HILLS		"h"
#define HQ(x)		"hq"#x
#define CITY(x)		"c"#x
#define FACTORY(x)	"m"#x



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
	Terrain(string pathName, string code) 
	{
		this->pathName = pathName;
		this->code = code;
	}

	~Terrain() { ; }

	void setConnection();

private:
	string pathName;
	string code;
	TerrStruct connection;
};