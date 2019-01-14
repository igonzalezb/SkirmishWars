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
///////ESTOS DE ABAJO NO ANDAN NO SE PORQUE////////////////////////////////////////////////////////////////////
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

	//void attack(coordenadas attacker, coordenadas defender);//ESTA FUNCION SEGURAMENTE HAYA QUE MOVERLA A OTRO ARCHIVO (+ prolijo) Quizas no recibe nada y se usa lo de abajo attacker y defender.
	void attack();
	void setAttacker(int tile);
	void setDefender(int tile);
	coordenadas getAttacker();
	coordenadas getDefender();

	void generateDefenseModifiersTable();
	
private:
	string mapName;
	csvFile *mapFile;
	csvFile *defenseModifiers;
		
	string terrainMatrix[FILA][COLUMNA]; //ESTO LO SACO Y USAMOS DIRECTAMENTE LA INFO QUE ESTA ADENTRO DEL TILE

	modifiers tableMatrix[14][5];
	
	GenericTile* tilesArray[FILA][COLUMNA];	//Array de Tiles Genericos
	coordenadas attacker; //HACER: INICIARLAS EN NULL
	coordenadas defender; //HACER: INICIAR EN NULL
};

void Map::setAttacker(int tile)
{
	switch (tile)
	{
	case A1: attacker.i = 0; attacker.j = 0; break;
	case A2: attacker.i = 0; attacker.j = 1; break;
	case A3: attacker.i = 0; attacker.j = 2; break;
	case A4: attacker.i = 0; attacker.j = 3; break;
	case A5: attacker.i = 0; attacker.j = 4; break;
	case A6: attacker.i = 0; attacker.j = 5; break;
	case A7: attacker.i = 0; attacker.j = 6; break;
	case A8: attacker.i = 0; attacker.j = 7; break;
	case A9: attacker.i = 0; attacker.j = 8; break;
	case A10: attacker.i = 0; attacker.j = 9; break;
	case A11: attacker.i = 0; attacker.j = 10; break;
	case A12: attacker.i = 0; attacker.j = 11; break;
	case A13: attacker.i = 0; attacker.j = 12; break;
	case A14: attacker.i = 0; attacker.j = 13; break;
	case A15: attacker.i = 0; attacker.j = 14; break;
	case A16: attacker.i = 0; attacker.j = 15; break;

	case B1: attacker.i = 1; attacker.j = 0; break;
	case B2: attacker.i = 1; attacker.j = 1; break;
	case B3: attacker.i = 1; attacker.j = 2; break;
	case B4: attacker.i = 1; attacker.j = 3; break;
	case B5: attacker.i = 1; attacker.j = 4; break;
	case B6: attacker.i = 1; attacker.j = 5; break;
	case B7: attacker.i = 1; attacker.j = 6; break;
	case B8: attacker.i = 1; attacker.j = 7; break;
	case B9: attacker.i = 1; attacker.j = 8; break;
	case B10: attacker.i = 1; attacker.j = 9; break;
	case B11: attacker.i = 1; attacker.j = 10; break;
	case B12: attacker.i = 1; attacker.j = 11; break;
	case B13: attacker.i = 1; attacker.j = 12; break;
	case B14: attacker.i = 1; attacker.j = 13; break;
	case B15: attacker.i = 1; attacker.j = 14; break;
	case B16: attacker.i = 1; attacker.j = 15; break;

	case C1: attacker.i = 2; attacker.j = 0; break;
	case C2: attacker.i = 2; attacker.j = 1; break;
	case C3: attacker.i = 2; attacker.j = 2; break;
	case C4: attacker.i = 2; attacker.j = 3; break;
	case C5: attacker.i = 2; attacker.j = 4; break;
	case C6: attacker.i = 2; attacker.j = 5; break;
	case C7: attacker.i = 2; attacker.j = 6; break;
	case C8: attacker.i = 2; attacker.j = 7; break;
	case C9: attacker.i = 2; attacker.j = 8; break;
	case C10: attacker.i = 2; attacker.j = 9; break;
	case C11: attacker.i = 2; attacker.j = 10; break;
	case C12: attacker.i = 2; attacker.j = 11; break;
	case C13: attacker.i = 2; attacker.j = 12; break;
	case C14: attacker.i = 2; attacker.j = 13; break;
	case C15: attacker.i = 2; attacker.j = 14; break;
	case C16: attacker.i = 2; attacker.j = 15; break;

	case D1: attacker.i = 3; attacker.j = 0; break;
	case D2: attacker.i = 3; attacker.j = 1; break;
	case D3: attacker.i = 3; attacker.j = 2; break;
	case D4: attacker.i = 3; attacker.j = 3; break;
	case D5: attacker.i = 3; attacker.j = 4; break;
	case D6: attacker.i = 3; attacker.j = 5; break;
	case D7: attacker.i = 3; attacker.j = 6; break;
	case D8: attacker.i = 3; attacker.j = 7; break;
	case D9: attacker.i = 3; attacker.j = 8; break;
	case D10: attacker.i = 3; attacker.j = 9; break;
	case D11: attacker.i = 3; attacker.j = 10; break;
	case D12: attacker.i = 3; attacker.j = 11; break;
	case D13: attacker.i = 3; attacker.j = 12; break;
	case D14: attacker.i = 3; attacker.j = 13; break;
	case D15: attacker.i = 3; attacker.j = 14; break;
	case D16: attacker.i = 3; attacker.j = 15; break;

	case E1: attacker.i = 4; attacker.j = 0; break;
	case E2: attacker.i = 4; attacker.j = 1; break;
	case E3: attacker.i = 4; attacker.j = 2; break;
	case E4: attacker.i = 4; attacker.j = 3; break;
	case E5: attacker.i = 4; attacker.j = 4; break;
	case E6: attacker.i = 4; attacker.j = 5; break;
	case E7: attacker.i = 4; attacker.j = 6; break;
	case E8: attacker.i = 4; attacker.j = 7; break;
	case E9: attacker.i = 4; attacker.j = 8; break;
	case E10: attacker.i = 4; attacker.j = 9; break;
	case E11: attacker.i = 4; attacker.j = 10; break;
	case E12: attacker.i = 4; attacker.j = 11; break;
	case E13: attacker.i = 4; attacker.j = 12; break;
	case E14: attacker.i = 4; attacker.j = 13; break;
	case E15: attacker.i = 4; attacker.j = 14; break;
	case E16: attacker.i = 4; attacker.j = 15; break;

	case F1: attacker.i = 5; attacker.j = 0; break;
	case F2: attacker.i = 5; attacker.j = 1; break;
	case F3: attacker.i = 5; attacker.j = 2; break;
	case F4: attacker.i = 5; attacker.j = 3; break;
	case F5: attacker.i = 5; attacker.j = 4; break;
	case F6: attacker.i = 5; attacker.j = 5; break;
	case F7: attacker.i = 5; attacker.j = 6; break;
	case F8: attacker.i = 5; attacker.j = 7; break;
	case F9: attacker.i = 5; attacker.j = 8; break;
	case F10: attacker.i = 5; attacker.j = 9; break;
	case F11: attacker.i = 5; attacker.j = 10; break;
	case F12: attacker.i = 5; attacker.j = 11; break;
	case F13: attacker.i = 5; attacker.j = 12; break;
	case F14: attacker.i = 5; attacker.j = 13; break;
	case F15: attacker.i = 5; attacker.j = 14; break;
	case F16: attacker.i = 5; attacker.j = 15; break;

	case G1: attacker.i = 6; attacker.j = 0; break;
	case G2: attacker.i = 6; attacker.j = 1; break;
	case G3: attacker.i = 6; attacker.j = 2; break;
	case G4: attacker.i = 6; attacker.j = 3; break;
	case G5: attacker.i = 6; attacker.j = 4; break;
	case G6: attacker.i = 6; attacker.j = 5; break;
	case G7: attacker.i = 6; attacker.j = 6; break;
	case G8: attacker.i = 6; attacker.j = 7; break;
	case G9: attacker.i = 6; attacker.j = 8; break;
	case G10: attacker.i = 6; attacker.j = 9; break;
	case G11: attacker.i = 6; attacker.j = 10; break;
	case G12: attacker.i = 6; attacker.j = 11; break;
	case G13: attacker.i = 6; attacker.j = 12; break;
	case G14: attacker.i = 6; attacker.j = 13; break;
	case G15: attacker.i = 6; attacker.j = 14; break;
	case G16: attacker.i = 6; attacker.j = 15; break;

	case H1: attacker.i = 7; attacker.j = 0; break;
	case H2: attacker.i = 7; attacker.j = 1; break;
	case H3: attacker.i = 7; attacker.j = 2; break;
	case H4: attacker.i = 7; attacker.j = 3; break;
	case H5: attacker.i = 7; attacker.j = 4; break;
	case H6: attacker.i = 7; attacker.j = 5; break;
	case H7: attacker.i = 7; attacker.j = 6; break;
	case H8: attacker.i = 7; attacker.j = 7; break;
	case H9: attacker.i = 7; attacker.j = 8; break;
	case H10: attacker.i = 7; attacker.j = 9; break;
	case H11: attacker.i = 7; attacker.j = 10; break;
	case H12: attacker.i = 7; attacker.j = 11; break;
	case H13: attacker.i = 7; attacker.j = 12; break;
	case H14: attacker.i = 7; attacker.j = 13; break;
	case H15: attacker.i = 7; attacker.j = 14; break;
	case H16: attacker.i = 7; attacker.j = 15; break;

	case I1: attacker.i = 8; attacker.j = 0; break;
	case I2: attacker.i = 8; attacker.j = 1; break;
	case I3: attacker.i = 8; attacker.j = 2; break;
	case I4: attacker.i = 8; attacker.j = 3; break;
	case I5: attacker.i = 8; attacker.j = 4; break;
	case I6: attacker.i = 8; attacker.j = 5; break;
	case I7: attacker.i = 8; attacker.j = 6; break;
	case I8: attacker.i = 8; attacker.j = 7; break;
	case I9: attacker.i = 8; attacker.j = 8; break;
	case I10: attacker.i = 8; attacker.j = 9; break;
	case I11: attacker.i = 8; attacker.j = 10; break;
	case I12: attacker.i = 8; attacker.j = 11; break;
	case I13: attacker.i = 8; attacker.j = 12; break;
	case I14: attacker.i = 8; attacker.j = 13; break;
	case I15: attacker.i = 8; attacker.j = 14; break;
	case I16: attacker.i = 8; attacker.j = 15; break;

	case J1: attacker.i = 9; attacker.j = 0; break;
	case J2: attacker.i = 9; attacker.j = 1; break;
	case J3: attacker.i = 9; attacker.j = 2; break;
	case J4: attacker.i = 9; attacker.j = 3; break;
	case J5: attacker.i = 9; attacker.j = 4; break;
	case J6: attacker.i = 9; attacker.j = 5; break;
	case J7: attacker.i = 9; attacker.j = 6; break;
	case J8: attacker.i = 9; attacker.j = 7; break;
	case J9: attacker.i = 9; attacker.j = 8; break;
	case J10: attacker.i = 9; attacker.j = 9; break;
	case J11: attacker.i = 9; attacker.j = 10; break;
	case J12: attacker.i = 9; attacker.j = 11; break;
	case J13: attacker.i = 9; attacker.j = 12; break;
	case J14: attacker.i = 9; attacker.j = 13; break;
	case J15: attacker.i = 9; attacker.j = 14; break;
	case J16: attacker.i = 9; attacker.j = 15; break;

	case K1: attacker.i = 10; attacker.j = 0; break;
	case K2: attacker.i = 10; attacker.j = 1; break;
	case K3: attacker.i = 10; attacker.j = 2; break;
	case K4: attacker.i = 10; attacker.j = 3; break;
	case K5: attacker.i = 10; attacker.j = 4; break;
	case K6: attacker.i = 10; attacker.j = 5; break;
	case K7: attacker.i = 10; attacker.j = 6; break;
	case K8: attacker.i = 10; attacker.j = 7; break;
	case K9: attacker.i = 10; attacker.j = 8; break;
	case K10: attacker.i = 10; attacker.j = 9; break;
	case K11: attacker.i = 10; attacker.j = 10; break;
	case K12: attacker.i = 10; attacker.j = 11; break;
	case K13: attacker.i = 10; attacker.j = 12; break;
	case K14: attacker.i = 10; attacker.j = 13; break;
	case K15: attacker.i = 10; attacker.j = 14; break;
	case K16: attacker.i = 10; attacker.j = 15; break;

	case L1: attacker.i = 11; attacker.j = 0; break;
	case L2: attacker.i = 11; attacker.j = 1; break;
	case L3: attacker.i = 11; attacker.j = 2; break;
	case L4: attacker.i = 11; attacker.j = 3; break;
	case L5: attacker.i = 11; attacker.j = 4; break;
	case L6: attacker.i = 11; attacker.j = 5; break;
	case L7: attacker.i = 11; attacker.j = 6; break;
	case L8: attacker.i = 11; attacker.j = 7; break;
	case L9: attacker.i = 11; attacker.j = 8; break;
	case L10: attacker.i = 11; attacker.j = 9; break;
	case L11: attacker.i = 11; attacker.j = 10; break;
	case L12: attacker.i = 11; attacker.j = 11; break;
	case L13: attacker.i = 11; attacker.j = 12; break;
	case L14: attacker.i = 11; attacker.j = 13; break;
	case L15: attacker.i = 11; attacker.j = 14; break;
	case L16: attacker.i = 11 ; attacker.j = 15; break;
	}
}