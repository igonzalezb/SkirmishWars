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

	
	usefulInfo(UserEventSource *UsEvSrc,GameEventSource *GameEvSrc, NetworkEventSource *NETEvSrc) :networkSrc(NETEvSrc),gameSrc(GameEvSrc)//CHEQUEAR
		//:userSrc(UsEvSrc),gameSrc(GameEvSrc)
	{
		networkInterface = networkSrc->networkInterface;
		gameInterface = gameSrc->gameInterface;
		//userInterface = userSrc->user;
	}
	

	Game *gameInterface;
	Networking *networkInterface;
	genericPackage *nextPkg;
	//Input *userInterface;

	GameEventSource* gameSrc;
	NetworkEventSource* networkSrc;
	//UserEventSource* userSrc;
private:

};

#endif // !USEFULINFO_H
