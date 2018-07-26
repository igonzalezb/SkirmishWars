#pragma once

#include <iostream>
#include<fstream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"
typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

#define COLUMNA		16
#define FILA		12

class Map
{
public:
	Map() { ; }
	Map(string mapName);
	void csvReader();
	~Map() { ; }

private:
	//file map.csv
	string mapName;
	string matrix[FILA][COLUMNA];
	//matriz de terrains + units

	GenericTile tilesArray[FILA][COLUMNA];
};