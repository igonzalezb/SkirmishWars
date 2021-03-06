#pragma once

#include <iostream>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#include "Tiles.h"
#include "csvHandler.h"
#include "genericEvent.h"



//#define NOFOG	//Just for Debug
#define ATTACK_TABLE "resources/terrainDefenseModifiers.csv"

#define MAP_0	"resources/maps/BalancedArena.csv"
#define MAP_1	"resources/maps/BalancedRing.csv"
#define MAP_2	"resources/maps/IslandWar.csv"
#define MAP_3	"resources/maps/Nascar.csv"
#define MAP_4	"resources/maps/SanFranciscoBridge.csv"
#define MAP_5	"resources/maps/SuperS.csv"
#define MAP_6	"resources/maps/WaterWorld.csv"
#define MAP_7	"resources/maps/SnakeArena.csv"
#define MAP_8	"resources/maps/MystPi.csv"	
#define MAP_9	"resources/maps/BlancedCross.csv"

#define MAX_MAPS	10
#define CANNOT_MOVE	100

#define M_HEIGHT(x)	al_get_display_height(x)
#define M_WIDTH(x)	(al_get_display_width(x)*3.0/4.0)

#define R_WIDTH		al_get_display_width(display)/4.0
#define T_HEIGHT(x)	M_HEIGHT(x)/FILA
#define T_WIDTH(x)	M_WIDTH(x)/COLUMNA

#define FOG_IMAGE	"resources/images/fog.png"
#define FONT_MENU	"resources/fonts/BAUHS93.otf"
#define DICE_FACE_PATH	"resources/images/dice/"


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


	GenericTile* getTile(int i, int j);
	void updateFogOfWar(int myTeam);

	void possibleMoves(Unit *currUnit, int i, int j);
	void possibleAttack(Unit *currUnit, int i, int j, TeamNumber myTeam);
	void checkPossibleMoves(int matrixCost[FILA][COLUMNA], int i, int j, int MP);
	void checkPossibleAttacks(int matrixCost[FILA][COLUMNA], int i, int j, int Range, TeamNumber myTeam, bool _canmove);

	bool canMove[FILA][COLUMNA];
	bool canAttack[FILA][COLUMNA];
	string getMapName();
	void setMapName(string mapName_);
	void verifyMapReceived();
	void setChecksum(); //esta es la que calcula el checksum
	unsigned char getChecksum();
	void setChecksumReceived(unsigned char checksumReceived_);
	unsigned char getChecksumReceived();

	bool isMapReceivedOk;
private:
	string mapName;
	csvFile* mapFile;
	string matrixDeTerrenoOrFacility[FILA][COLUMNA];
	unsigned char checksum;
	unsigned char checksumReceived;

	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles Genericos
};
