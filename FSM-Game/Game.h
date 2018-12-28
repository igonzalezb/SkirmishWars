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
#include "MapGraphics.h"

#include "basicXML.h"


#define XML_PATH	"resources.xml"


typedef char MYBYTE;



class Game
{
public:
	Game();
	~Game(); //Ver cuando llamarlo
	

private:
	Player* player1;
	Player* player2;
	Map* map;
	MapGraphics* graphics;
};
#endif // !GAME_H
