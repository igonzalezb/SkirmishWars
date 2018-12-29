#pragma once
#include <iostream>
#include <string>

#define MAX_PLAYERS	2

using namespace std;


class Player
{
public:
	Player();
	~Player();
	void setMoney(int money);
	int getMoney();
	void setTeam(int team);
	int getTeam();
	bool doIStart();

private:
	string name;
	int money;
	int team;	//TeamNumber
	int ip;
	bool myTurn;

	//agrego lo siguiente:
	int cities; // ver si esta en otro lado!!!!!!!!!!!!!!!!!!! VER COMO CONTAR LA CANTIDAD DE CITIES. HACERLO
	//int hp;
};

