#pragma once

#include <iostream>
#include<fstream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"

//typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;


//Mapa 0, 3, 5, 8 no anda



#define MAP_0	"resources/maps/BalancedArena.csv"
#define MAP_1	"resources/maps/BalancedRing.csv"
#define MAP_2	"resources/maps/IslandWar.csv"
#define MAP_3	"resources/maps/Nascar.csv"
#define MAP_4	"resources/maps/SanFranciscoBridge.csv"
#define MAP_5	"resources/maps/SuperS.csv"
///////////////////////////////////////////////////////////////////////////
#define MAP_6	"resources/maps/WaterWorld.csv"
#define MAP_7	"resources/maps/SnakeArena.csv"
#define MAP_8	"resources/maps/MystPi.csv"	
#define MAP_9	"resources/maps/BlancedCross.csv"

#define MAX_MAPS	6
#define CANNOT_MOVE	100


enum tabla
{
	M_HQ, CI_FA, FORR, PLA, RO_RI
};

struct modifiers
{
	int golpe;
	int dado;
};


struct coordenadas
{
	int i;
	int j;
};


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
	void updateFogOfWar(int myTeam);

	void attack(coordenadas attacker, coordenadas defender);


private:
	//file map.csv
	string mapName;
	//matriz de terrains + units
	string matrix[FILA][COLUMNA];	//Con los Codigos
	
	string terrainMatrix[FILA][COLUMNA];

	modifiers tableMatrix[14][5];
	
	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles Genericos
};