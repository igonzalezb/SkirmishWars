#ifndef EVENTSOURCES_H
#define EVENTSOURCES_H

#define DEBUG true

#include <string>
#include <vector>
#include <fstream>
#include "Game.h"
#include "genericEventSource.h"
#include <ctime>

/*
#define ONE_MINUTE		60
#define MAX_TIMEOUTS	5
*/


class GameEventSource : public genericEventSource
{
public:
	GameEventSource(Game *_gameInterface); //VER que recibe aca (A LOS DOS JUGADORES, O UNA CLASE CON TODO EL JUEGO O QUE)
	bool isThereEvent();
	genericEvent* insertEvent();
	Game *gameInterface;
private:

};

/*
class UserEventSource : public genericEventSource
{
public:
	UserEventSource( *_userInterface); // ver aca que onda
	bool isThereEvent();
	genericEvent* insertEvent();
	//std::string getCommand();	//getter del commando ingresado
private:
	//std::vector<std::string> words;	//Vector para separar los argumentos ingresados
	std::vector<char> buffer;
	std::string command;

	int inputChar;
	char ** args;
};
*/

#endif // !EVENTSOURCES_H