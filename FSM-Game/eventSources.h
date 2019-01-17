//HACER: METER aca Network Event Source

#ifndef EVENTSOURCES_H
#define EVENTSOURCES_H

#define DEBUG true

#include <string>
#include <vector>
#include <fstream>
#include "Game.h"
#include "genericEventSource.h"
#include <ctime>
#include "MapGraphics.h"
#include <boost\asio.hpp>
#include "Packages.h"
#include <boost\asio\deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Networking.h"
#include "userInput.h"



/*
#define ONE_MINUTE		60
#define MAX_TIMEOUTS	5
*/


class GameEventSource : public genericEventSource
{
public:
	GameEventSource(Game* _gameInterface);//VER que recibe aca (A LOS DOS JUGADORES, O UNA CLASE CON TODO EL JUEGO O QUE)
	bool isThereEvent();
	//eventCode dispachClick(int x, int y);
	genericEvent* insertEvent();
	Game *gameInterface;
private:
	//MapGraphics* graphics;
};


class NetworkEventSource : public genericEventSource
{
public:
	NetworkEventSource(Networking *_networkInterface, Game *_gameInterface);
	bool isThereEvent();
	genericEvent* insertEvent();
	Networking *networkInterface;
	Game* gameInterface;
	//unsigned int expectedBlockNum;
	//std::string fileRequested;
	//std::vector<char> data;	//Se almacena la data en caso de recibir DATA
	//std::string errorMsg;
	//errorCodes errorCode;
	//unsigned int blockNumber;

	//agrego esto, despues ver donde meterlo (r de recibido)
	std::vector<char> r_name;
	std::vector<char> r_map;
	// VER si dejar las columnas con su valor como MYBYTE que significa char, o si guardarlo como int!!!
	// las columnas si o si chars porque son letras en mayuscula: A, B, C, D etc
	MYBYTE r_fila_or;
	MYBYTE r_col_or;
	MYBYTE r_fila_de;
	MYBYTE r_col_de;
	std::vector<char>  r_unidad;
	MYBYTE r_dado;
private:

};


class UserEventSource : public genericEventSource
{
public:
	UserEventSource(userInput* _userInterface,Game*_gameInterface); //VER que recibe aca (A LOS DOS JUGADORES, O UNA CLASE CON TODO EL JUEGO O QUE)
	bool isThereEvent();
	eventCode dispachClick(int x, int y);
	genericEvent* insertEvent();
	userInput *userInterface;
	Game *gameInterface;
private:
	MapGraphics* graphics;
	ALLEGRO_EVENT_QUEUE* event_queue;
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