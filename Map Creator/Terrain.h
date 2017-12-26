#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum { RED, BLUE, YELLOW, GREEEN} TeamColor;

//----- TERRAIN TYPE [CODES] -----
#define PLAIN		"t"
#define RIVER		"r"
#define ROAD		"a"
#define FOREST		"f"
#define HILLS		"h"
#define HQ(x)		"q"#x
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
	Terrain(string pathName, string type, TeamColor team) 
	{
		this->pathName = pathName;
		this->type = type;
		this->team = team;
	}

	~Terrain() { ; }

	/////////////////////////////////////////////////////////////////////////////////////
	//		Set Connection
	//	Chequea/Setea? que si el terreno esta conectado con otro (Roads & Rivers)
	////////////////////////////////////////////////////////////////////////////////////
	void setConnection();

private:
	string pathName; //??
	
	string type;
	TeamColor team;
	TerrStruct connection;
};