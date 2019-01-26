//HACER: METER aca Network Event Source

#ifndef EVENTSOURCES_H
#define EVENTSOURCES_H

//#define DEBUG true

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

#include "MapGraphics.h"




#define THIRTY_SEC			30
#define FIFTY_SEC			50
#define ONE_MIN				60
#define TWO_HALF_MIN		150 
#define MAX_TIMEOUTS		5 //VER ESTO!!!!!!



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
	string r_name_string;
	std::vector<char> r_map;
	string r_map_string;
	// VER si dejar las columnas con su valor como MYBYTE que significa char, o si guardarlo como int!!!
	// las columnas si o si chars porque son letras en mayuscula: A, B, C, D etc
    /*
	MYBYTE r_fila_or;
	MYBYTE r_col_or;
	MYBYTE r_fila_de;
	MYBYTE r_col_de;
	*/
	std::vector<char>  r_unidad;
	string r_unidad_string;
	MYBYTE r_dado;
private:

};


class UserEventSource : public genericEventSource
{
public:
	UserEventSource(userInput* _userInterface , Game*_gameInterface); //VER que recibe aca (A LOS DOS JUGADORES, O UNA CLASE CON TODO EL JUEGO O QUE)
	~UserEventSource();
	bool isThereEvent();
	/*eventCode dispachClick(int x, int y);*/
	genericEvent* insertEvent();
	userInput *userInterface;
	Game *gameInterface;
	//MapGraphics* graphics;
	eventCode dispatchClick(int x, int y);

private:
	ALLEGRO_EVENT_QUEUE* event_queue;
};


class TimeoutEventSource : public genericEventSource
{
public:
	TimeoutEventSource();
	bool isThereEvent();
	void startTimer1();
	void startTimer2();
	void stopTimer1();
	void stopTimer2();
	unsigned int getTimeoutCount1();
	genericEvent* insertEvent();
private:
	clock_t tInicial1;
	clock_t tInicial2;
	unsigned int timeoutCount1;
	unsigned int timeoutCount2;
	bool timeout;	//Si está en true se cumplió el tiempo.
	bool timerRunning1;
	bool timerRunning2;

	bool timeout10s;
	bool timeout30s;
};


#endif // !EVENTSOURCES_H