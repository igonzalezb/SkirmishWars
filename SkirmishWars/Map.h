#pragma once


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"
typedef enum { RED, BLUE, YELLOW, GREEEN } TeamColor;


#define COLUMNAS	16
#define FILAS		12

class Map
{
public:
	Map() { ; }
	~Map() { ; }

private:
	//file map.csv
	//matriz de terrains + units
	
	
	//std::vector<GenericTile> terrMatrix;

	GenericTile tilesArray[FILAS][COLUMNAS];
};