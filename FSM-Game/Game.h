#ifndef GAME_H
#define GAME_H

#define DEBUG true

#include <iostream>
#include <string>
#include <exception>
#include <array>
#include <Windows.h> //ver si sacar
#include "PlayerInfo.h"
#include "Map.h"


#include "basicXML.h"
#include "MapGraphics.h"
#include "Resources.h"

#define XML_PATH	"resources.xml"

typedef char MYBYTE;



class Game
{
public:
	Game();
	~Game(); //Ver cuando llamarlo
	Player* playerMe;
	Player* playerYou;
	Map* myMap;
	//coordinates  attacker; //POR AHORA ESTAS DOS LINEAS ESTAN EN MAP.H. VER SI QUEDAN AHI O SI SE SACAN Y SE PONEN ACA O DONDE!
	//coordinates defender;
	
	void move();
	void attack();
	void captureProperty(Player* pAttacker, Player* pDefender);
	void setAttacker(coordenadas newAttacker);
	void setAttacker(int i,int j);
	void setDefender(coordenadas newDefender);
	void setDefender(int i, int j);
	void setTileSelected(coordenadas newTileSelected);
	void setTileSelected(int i, int j);
	coordenadas getAttacker();
	coordenadas getDefender();
	coordenadas getTileSelected();
	void purchase(Player* player);
	//void setOrigen(coordenadas origen); //USAMOS ATTACKER Y DEFENDER PARA TODO
	//void setDestino(coordenadas destino);
	//coordenadas getOrigen();
	//coordenadas getDestino();
	bool didHeWin();
	void generateDefenseModifiersTable();
	void setNotWinning(bool nWinning);
	bool getNotWinning();
	void setNewUnit(Unit* unit);
	Unit* getNewUnit();
	int getDie();
	void setDie(int Dado_);
	bool moving;
	bool attacking;
	bool purchasing;
private:
	coordenadas attacker;
	coordenadas defender;
	coordenadas tileSelected;
	int die;
	//coordenadas origen;
	//coordenadas destino;
	bool notWinning;
	csvFile *defenseModifiers;
	modifiers tableMatrix[14][5];
	Unit *newUnit;

};
#endif // !GAME_H
