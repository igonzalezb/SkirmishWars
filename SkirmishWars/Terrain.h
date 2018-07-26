#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

//----- TERRAIN TYPE [CODES] -----
#define PLAIN		"t"
#define RIVER		"r"
#define ROAD		"a"
#define FOREST		"f"
#define HILLS		"h"

// Para saber si los ríos o calles son continuas
struct TerrStruct
{
	bool up;
	bool down;
	bool left;
	bool right;
};

class Terrain
{
private:
	string name;
	string path;

	string type;
	TerrStruct connections;
	bool fogOfWar; //Empieza en True

public:
	Terrain();
	~Terrain();
	void setPath(string path);
	void setName(string name);
	void setType(string type);
	string getPath();
	string getName();
	string getType();

	void setConnections(); //Setea si el terreno esta conectado con otro (Roads & Rivers) Lo debería llamar 

	void removeFog();

};