#pragma once
//#ifndef GAME_H
//#define GAME_H

#define DEBUG true

#include <iostream>
#include <string>
#include <exception>
#include <array>
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
	~Game(); 
	Player* playerMe;
	Player* playerYou;
	Map* myMap;
	Resources* data;
	MapGraphics* graphics;
	
	void move();
	void attack();
	void captureProperty(Player* pAttacker);
	void setAttacker(coordenadas newAttacker);
	void setAttacker(int i,int j);
	void setDefender(coordenadas newDefender);
	void setDefender(int i, int j);
	void setTileSelected(int i, int j);
	coordenadas getAttacker();
	coordenadas getDefender();
	coordenadas getTileSelected();
	void purchase(Player* player);
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
	void boardUnit();
	void unboardUnit();

	bool moving;
	bool boardingAPC;
	bool unboardingAPC;
	bool attacking;
	bool purchasing;

	void chooseWhoStarts();
	bool playerChosen;
	bool Istart;

	void setEndPlaying(bool endPlaying_);
	bool getEndPlaying();

	void setIWantToPlayAgain(bool playAgain);
	bool getIWantToPlayAgain();
	void setYouWantToPlayAgain(bool playAgain);
	bool getYouWantToPlayAgain();
	void setAnalysePlayAgain(bool yes_no);
	bool getAnalysePlayAgain();

	void setAnalyseVictory(bool analyse);
	bool getAnalyseVictory();

	bool error;
	bool quit;


	
private:
	coordenadas attacker;
	coordenadas defender;
	coordenadas tileSelected;
	int die;
	bool youWinning;
	csvFile *defenseModifiers;
	modifiers tableMatrix[14][5];
	Unit *newUnit;
	bool iAmPlaying;
	bool endPlaying;
	bool IWantToPlayAgain;
	bool youWantToPlayAgain;
	bool analyseVictory;
	bool analysePlayAgain;
};
//#endif // !GAME_H
