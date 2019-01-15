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

	void attack();
	void captureProperty(Player* pAttacker, Player* pDefender);
	void setAttacker(coordenadas newAttacker);
	void setDefender(coordenadas newDefender);
	void setTileSelected(coordenadas newTileSelected);
	coordenadas getAttacker();
	coordenadas getDefender();
	coordenadas getTileSelected();
	void purchase(Player* player, string newUnit);
	//void setOrigen(coordenadas origen); //USAMOS ATTACKER Y DEFENDER PARA TODO
	//void setDestino(coordenadas destino);
	//coordenadas getOrigen();
	//coordenadas getDestino();
	bool didHeWin();
	void Game::generateDefenseModifiersTable();
	void setNotWinning(bool nWinning);
	bool getNotWinning();


private:
	coordenadas attacker;
	coordenadas defender;
	coordenadas tileSelected;
	//coordenadas origen;
	//coordenadas destino;
	bool notWinning;
	csvFile *defenseModifiers;
	modifiers tableMatrix[14][5];
};
#endif // !GAME_H
