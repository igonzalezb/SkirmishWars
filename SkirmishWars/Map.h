#pragma once

#include <iostream>
#include<fstream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"

//typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

#define COLUMNA		16
#define FILA		12

class Map
{
public:
	Map() { ; }
	Map(string mapName);
	~Map();
	void csvReader();
	void setMapPath(string mapName);
	
	void generateTilesArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units);
	GenericTile* getTile(int i, int j);



private:
	//file map.csv
	string mapName;
	//matriz de terrains + units
	string matrix[FILA][COLUMNA];	//Con los Codigos
	

	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles
};