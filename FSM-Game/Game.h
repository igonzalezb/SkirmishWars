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

typedef char MYBYTE;



class Game
{
public:
	Game();
	~Game(); //Ver cuando llamarlo
	Player* playerMe = new Player;
	Player* playerYou = new Player;
	Map* myMap = new Map;
	//coordinates  attacker; //POR AHORA ESTAS DOS LINEAS ESTAN EN MAP.H. VER SI QUEDAN AHI O SI SE SACAN Y SE PONEN ACA O DONDE!
	//coordinates defender;

	void captureProperty(Player* pAttacker, Player* pDefender);
	void setAttacker();
	void setDefender();
	coordenadas getAttacker();
	coordenadas getDefender();

private:
	coordenadas attacker;
	coordenadas defender;
};
#endif // !GAME_H
