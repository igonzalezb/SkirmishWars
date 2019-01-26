#pragma once
//#ifndef GAME_H
//#define GAME_H

#define DEBUG true

#include <iostream>
#include <string>
#include <exception>
#include <array>
//#include <Windows.h> //ver si sacar
#include "PlayerInfo.h"
#include "Map.h"

#include "MapGraphics.h"

#include "basicXML.h"
#include "Resources.h"

#define XML_PATH	"resources/resources.xml"

typedef char MYBYTE;



class Game
{
public:
	Game(ALLEGRO_DISPLAY* display);
	~Game(); //Ver cuando llamarlo
	Player* playerMe;
	Player* playerYou;
	Map* myMap;
	Resources* data;
	MapGraphics* graphics;
	//coordinates  attacker; //POR AHORA ESTAS DOS LINEAS ESTAN EN MAP.H. VER SI QUEDAN AHI O SI SE SACAN Y SE PONEN ACA O DONDE!
	//coordinates defender;
	
	void move();
	void attack();
	void captureProperty(Player* pAttacker);
	void setAttacker(coordenadas newAttacker);
	void setAttacker(int i,int j);
	void setDefender(coordenadas newDefender);
	void setDefender(int i, int j);
	//void setTileSelected(coordenadas newTileSelected);
	void setTileSelected(int i, int j);
	coordenadas getAttacker();
	coordenadas getDefender();
	coordenadas getTileSelected();
	void purchase(Player* player);
	//void setOrigen(coordenadas origen); //USAMOS ATTACKER Y DEFENDER PARA TODO
	//void setDestino(coordenadas destino);
	//coordenadas getOrigen();
	//coordenadas getDestino();
	void generateDefenseModifiersTable();
	void setYouWinning(bool winning_);
	bool didHeWin();
	bool getYouWinning();
	void setNewUnit(Unit* unit);
	Unit* getNewUnit();
	int getDie();
	void setDie(int Dado_);
	void setIamPlaying(bool now);
	bool getIamPlaying();
	bool moving;
	bool attacking;
	bool purchasing;

	void chooseWhoStarts();
	bool playerChosen;
	bool Istart;

	void setEndPlaying(bool endPlaying_);
	bool getEndPlaying();
	
private:
	coordenadas attacker;
	coordenadas defender;
	coordenadas tileSelected;
	int die;
	//coordenadas origen;
	//coordenadas destino;
	bool youWinning;
	csvFile *defenseModifiers;
	modifiers tableMatrix[14][5];
	Unit *newUnit;
	bool iAmPlaying;
	bool endPlaying;
};
//#endif // !GAME_H
