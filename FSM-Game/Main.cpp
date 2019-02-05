/////////////////////////////////////////////////////////////////////////////////////////////	
//
// Instituto Tecnologico de Buenos Aires						04/02/2019
//
// Algoritmos y Estructuras de Datos - Trabajo Práctico Final
//
//
// Gonzalez Bigliardi, Iñaki				 ////////////////////////////////////////////////
// Lago, Valentina					//		    S K I R M I S H    W A R S
// Muller, Malena					//////////////////////////////////////////////////
//
//
//
// Juego para dos jugadores. A continuación se encuentran las reglas del juego:
// http://skirmishwars.wikidot.com/start 
//
/////////////////////////////////////////////////////////////////////////////////////////////


#include "usefulInfo.h"
#include "eventGenerator.h"
#include "FSMGame.h"
#include "FSMNetworking.h"
#include "eventSources.h"
#include "userInput.h"
#include <string>
#include <sstream>
#include <iostream>


#include "basicXML.h"
#include "AllegroSetup.h"
#include "StartMenu.h"
#include "Viewer.h"

#define XML_PATH	"resources.xml"

using namespace std;

int main()
{
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	if (allegroStartup())
	{
		al_show_native_message_box(NULL, "ERROR", "Failed to Install Allegro", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	StartMenu* mainMenu = new StartMenu;
	mainMenu->openApp();

	std::string opponentsIP = mainMenu->getUserIP();					
	Game skirmish(mainMenu->getDisplay());												//Creo una instancia del juego
	skirmish.playerMe->setName(mainMenu->getUserName());
	skirmish.graphics->setBackgroundMusicOnOff(mainMenu->getBackgroundMusicOnOff());
	skirmish.graphics->setSoundEffectsOnOff(mainMenu->getSoundEffectsOnOff());
	skirmish.graphics->setWarningsOnOff(mainMenu->getWarningsOnOff());
	
	
	Networking communicator(opponentsIP);
	userInput user;
	
	TimeoutEventSource timeoutSource;
	GameEventSource gameSource(&skirmish);
	UserEventSource userSource(&user,&skirmish);
	NetworkEventSource networkSource(&communicator,&skirmish);
	usefulInfo Info(&userSource,&gameSource,&networkSource, &timeoutSource);
	genericEvent *ev;
	eventGenerator evGen(&Info);
	FSMGame gameFSM;
	FSMNetworking networkingFSM;
	Viewer gameviewer;
	
	cout << "Listening on port 13225..." << endl;
	communicator.startConnection();
	communicator.justConnected = 1;
	cout << "Connection established" << endl;

	do
	{
		evGen.generateEvent();
		ev = evGen.getNextEvent();
		if (ev != nullptr)
		{
			networkingFSM.dispatch(ev, &Info);
			gameFSM.dispatch(ev, &Info);
			gameviewer.dispatch(ev, &Info);
		}
	} while (((gameFSM.getCurrentState())->getLastEvent() != END_PLAYING) &&
		((networkingFSM.getCurrentState())->getLastEvent() != END_PLAYING));

#ifdef DEBUG
	cout << "FIN" << endl;
#endif // DEBUG

	//getchar();

	return EXIT_SUCCESS;
}






