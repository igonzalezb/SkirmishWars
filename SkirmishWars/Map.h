#pragma once

#include <iostream>
#include<fstream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"

//typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

#define MAP_0	"resources/maps/WaterWorld.csv"
#define MAP_1	"resources/maps/BalancedArena.csv"
#define MAP_2	"resources/maps/BalancedRing.csv"
#define MAP_3	"resources/maps/BlancedCross.csv"	
#define MAP_4	"resources/maps/IslandWar.csv"
#define MAP_5	"resources/maps/MystPi.csv"	
#define MAP_6	"resources/maps/Nascar.csv"
#define MAP_7	"resources/maps/SanFranciscoBridge.csv"
#define MAP_8	"resources/maps/SnakeArena.csv"
#define MAP_9	"resources/maps/SuperS.csv"


#define MAX_MAPS	10
#define CANNOT_MOVE	100
class Map
{
public:
	Map();
	~Map();
	void csvReader();
	void setMapPath(string mapName);
	void randomMap();

	//FUNCIONA PERO HABRIA QUE MEJORARLA
	void generateTilesArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units);

	void possibleMoves(Unit *currUnit, int i, int j, bool(&canMove)[FILA][COLUMNA]);
	
	GenericTile* getTile(int i, int j);
	void updateFogOfWar();


private:
	//file map.csv
	string mapName;
	//matriz de terrains + units
	string matrix[FILA][COLUMNA];	//Con los Codigos
	
	string terrainMatrix[FILA][COLUMNA];


	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles Genericos
};