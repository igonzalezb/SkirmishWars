#pragma once

#include <iostream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"
#include "csvHandler.h"

//typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

#define ATTACK_TABLE "resources/terrainDefenseModifiers.csv"

#define MAP_0	"resources/maps/BalancedArena.csv"
#define MAP_1	"resources/maps/BalancedRing.csv"
#define MAP_2	"resources/maps/IslandWar.csv"
#define MAP_3	"resources/maps/Nascar.csv"
#define MAP_4	"resources/maps/SanFranciscoBridge.csv"
#define MAP_5	"resources/maps/SuperS.csv"
///////ESTOS DE ABAJO NO ANDAN NOSE PORQUE////////////////////////////////////////////////////////////////////
#define MAP_6	"resources/maps/WaterWorld.csv"
#define MAP_7	"resources/maps/SnakeArena.csv"
#define MAP_8	"resources/maps/MystPi.csv"	
#define MAP_9	"resources/maps/BlancedCross.csv"

#define MAX_MAPS	6
#define CANNOT_MOVE	100

#define M_HEIGHT	al_get_display_height(display)
#define M_WIDTH		(al_get_display_width(display)*3.0/4.0)
#define R_WIDTH		al_get_display_width(display)/4.0
#define T_HEIGHT	M_HEIGHT/FILA
#define T_WIDTH		M_WIDTH/COLUMNA
#define FOG_IMAGE	"resources/images/fog.png"
#define FONT_MENU	"resources/BAUHS93.otf"


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
	void setMapPath(string mapName);
	void randomMap();
	void generateTilesArray(list<Building> buildings, list<Terrain> terrains, list<Unit> units);

	void possibleMoves(Unit *currUnit, int i, int j, bool(&canMove)[FILA][COLUMNA]);
	
	GenericTile* getTile(int i, int j);
	void updateFogOfWar(int myTeam);

	void attack(coordenadas attacker, coordenadas defender);

	void generateDefenseModifiersTable();

private:
	string mapName;
	csvFile *mapFile;
	csvFile *defenseModifiers;
		
	string terrainMatrix[FILA][COLUMNA]; //ESTO LO SACO Y USAMOS DIRECTAMENTE LA INFO QUE ESTA ADENTRO DEL TILE

	modifiers tableMatrix[14][5];
	
	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles Genericos
};