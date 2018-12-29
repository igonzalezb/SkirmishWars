#ifndef EVENTSOURCES_H
#define EVENTSOURCES_H

#define DEBUG true

#include <string>
#include <vector>
#include <fstream>
#include <boost\asio.hpp>
//#include "FileSystem.h"
#include "Packages.h"
//#include "Screen.h"
#include "Networking.h"
#include "genericEventSource.h"
#include <boost\asio\deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>

/*
#define ONE_MINUTE		60
#define MAX_TIMEOUTS	5
*/

class NetworkEventSource : public genericEventSource
{
public:
	NetworkEventSource(Networking *_networkInterface);
	bool isThereEvent();
	genericEvent* insertEvent();
	Networking *networkInterface;
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

/*
class UserEventSource : public genericEventSource
{
public:
UserEventSource(Screen *Terminal);
bool isThereEvent();
genericEvent* insertEvent();
std::string getFileToTransfer();	//getter del nombre del archivo a transferir
std::string getCommand();	//getter del commando ingresado
Screen *terminal;
private:

std::string fileToTransfer;
std::vector<std::string> words;	//Vector para separar los argumentos ingresados
std::vector<char> buffer;
std::string command;

int inputChar;
char ** args;

};

class TimeoutEventSource : public genericEventSource
{
public:
TimeoutEventSource();
bool isThereEvent();
void startTimer();
void stopTimer();
genericEvent* insertEvent();
private:
clock_t tInicial;
unsigned int timeoutsCount;
bool timeout;	//Si está en true se cumplió el tiempo.
bool timerRunning;
};

class SoftwareEventSource : public genericEventSource
{
public:
SoftwareEventSource();
bool isThereEvent();
bool ev;
genericEvent* insertEvent();
FileSystem *fileInterface;
};
*/

#endif // !EVENTSOURCES_H