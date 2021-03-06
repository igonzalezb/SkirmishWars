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

#include "MapGraphics.h"




#define THIRTY_SEC			30
#define FIFTY_SEC			50
#define ONE_MIN				60
#define TWO_HALF_MIN			150 
#define MAX_TIMEOUTS			5 



class GameEventSource : public genericEventSource
{
public:
	GameEventSource(Game* _gameInterface);
	bool isThereEvent();
	genericEvent* insertEvent();
	Game *gameInterface;
private:
};


class NetworkEventSource : public genericEventSource
{
public:
	NetworkEventSource(Networking *_networkInterface, Game *_gameInterface);
	bool isThereEvent();
	genericEvent* insertEvent();
	Networking *networkInterface;
	Game* gameInterface;
	std::vector<char> r_name;
	string r_name_string;
	std::vector<char> r_map;
	string r_map_string;
	std::vector<char>  r_unidad;
	string r_unidad_string;
	MYBYTE r_dado;
private:

};


class UserEventSource : public genericEventSource
{
public:
	UserEventSource(userInput* _userInterface , Game*_gameInterface);
	~UserEventSource();
	bool isThereEvent();
	genericEvent* insertEvent();
	userInput *userInterface;
	Game *gameInterface;
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
	bool timeout;	//Si est� en true se cumpli� el tiempo.
	bool timerRunning1;
	bool timerRunning2;

	bool timeout10s;
	bool timeout30s;
};


#endif // !EVENTSOURCES_H