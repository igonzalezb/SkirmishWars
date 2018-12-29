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

	
	usefulInfo(GameEventSource *UsEvSrc,GameEventSource *GameEvSrc)
		//:userSrc(UsEvSrc),gameSrc(GameEvSrc)
	{
		gameInterface = gameSrc->gameInterface;
		//userInterface = userSrc->user;
	}
	
	GameEventSource* gameSrc;
	//UserEventSource* userSrc;

	Game *gameInterface;
	//Input *userInterface;
private:

};

#endif // !USEFULINFO_H
