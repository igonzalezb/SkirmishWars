#pragma once
#include <iostream>
#include <string>
#include "Map.h"
#define MAX_PLAYERS	2

using namespace std;


class Player
{
public:
	Player();
	~Player();
	void setMoney(int money);
	int getMoney();
	void setTeam(TeamNumber team);
	TeamNumber getTeam();
	bool doIStart();
	void setAmmountOfCities(Map* myMap);
	int getAmmountOfCities();
	string getName();
	void setName(string Name_);

private:
	string name;
	int money;
	TeamNumber team;	//TeamNumber
	TeamColor teamcolor;
	int ip;
	bool myTurn;
	int cities; // ver si esta en otro lado!!!!!!!!!!!!!!!!!!! VER COMO CONTAR LA CANTIDAD DE CITIES. HACERLO
	//int hp;
};

