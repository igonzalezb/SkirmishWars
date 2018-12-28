#ifndef USEFULINFO_H
#define USEFULINFO_H

#define DEBUG true

#include <string>
#include "eventSources.h"
//#include "FileSystem.h"
class usefulInfo
{
public:
	//Hay que agrgarle los punteros a las otras fuentes al constructor
	//y pasar el constructor a un .cpp

	/*
	usefulInfo(UserEventSource *UsEvSrc, TimeoutEventSource *TOEvSrc, NetworkEventSource *NETEvSrc, FileSystem *FileSys, SoftwareEventSource *SoftSrc)
	:userSrc(UsEvSrc), timeoutSrc(TOEvSrc), networkSrc(NETEvSrc), fileInterface(FileSys), softwareSrc(SoftSrc) {
	networkInterface = networkSrc->networkInterface;
	userInterface = userSrc->terminal;
	softwareSrc->fileInterface = fileInterface;

	}
	*/
	usefulInfo(GameEventSource *NETEvSrc) :gameSrc(NETEvSrc)
	{
		gameInterface = gameSrc->gameInterface;
	}

	GameEventSource* gameSrc;	//TODO: ponerle getters quizas? quedaria mas prolijo o es al pedo??
									//UserEventSource* userSrc;
									//TimeoutEventSource* timeoutSrc;
									//SoftwareEventSource* softwareSrc;

	Game *gameInterface;

private:

};

#endif // !USEFULINFO_H
