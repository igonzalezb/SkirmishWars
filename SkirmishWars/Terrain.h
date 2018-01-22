#pragma once
#include <iostream>
#include <string>

#include "Unit.h"
#include "Building.h"

using namespace std;


//----- TERRAIN TYPE [CODES] -----
#define PLAIN		"t"
#define RIVER		"r"
#define ROAD		"a"
#define FOREST		"f"
#define HILLS		"h"



// Para saber si los ríos o calles son continuas
struct TerrStruct
{	bool up;
	bool down;
	bool left;
	bool right;
};

class Terrain
{
public:
	Terrain(string pathName, string type);
	~Terrain() { ; }

	void setConnections(); //Chequea/Setea? que si el terreno esta conectado con otro (Roads & Rivers)

	void removeFog();

private:
	string pathName; //?? Seria lo de Allegro, podríamos hacer un XML
	string type; //?? string o char?
	TerrStruct connections;
	bool fogOfWar; //Empieza en True
	
	Unit *currUnit = NULL;
	Building *currBuilding = NULL;
};