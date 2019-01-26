//PARA PREPROCESSOR EN PROPERTIES: _CRT_SECURE_NO_WARNINGS
// <package id="Allegro" version="5.2.4.0" targetFramework="native" />
// <package id="AllegroDeps" version="1.7.0.0" targetFramework="native" />
//COMENTE TODOS LOS #include "Windows.h". VER SI ERAN IMPORTANTES PARA ALGO!!!!!!!!!

#include "usefulInfo.h"
#include "eventGenerator.h"
//#include "genericFSM.h"
#include "FSMGame.h"
#include "FSMNetworking.h"
#include "eventSources.h"
#include "userInput.h"
//#include "Networking.h"
//#include "Game.h"
#include <string>
#include <sstream>
#include <iostream>
//#include "Windows.h"

#include "basicXML.h"
#include "AllegroSetup.h"
#include "StartMenu.h"

#define XML_PATH	"resources.xml"

using namespace std;

int main()
{
	
	if (allegroStartup())
	{
		al_show_native_message_box(NULL, "ERROR", "Failed to Install Allegro", "", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	
	/////////////////////////////////////////
	//std::cout << "Por favor ingrese la direccion IP del servidor a traves de la linea de comando.\n Ejemplo: 'Client.exe 192.168.0.50'" << std::endl;
	//std::cout << "Presione una tecla para salir." << std::endl;
	//getchar();
	StartMenu* mainMenu = new StartMenu;
	mainMenu->openApp();

	std::string opponentsIP = "localhost";//mainMenu->getUserIP();  //"localhost"; //CAMBIAR y ver donde recibirlo y como
	Game skirmish(mainMenu->getDisplay()); //Creo una instancia del juego
	skirmish.playerMe->setName(mainMenu->getUserName());
	
	Networking communicator(opponentsIP);
	userInput user;
	
	TimeoutEventSource timeoutSource;
	GameEventSource gameSource(&skirmish);
	UserEventSource userSource(&user,&skirmish);
	NetworkEventSource networkSource(&communicator,&skirmish);
	//SoftwareEventSource Software;
	//NetworkEventSource networkSource(&Server);
	//UserEventSource userSource(&Terminal);
	//usefulInfo Info(&userSource, &Timeout, &networkSource, &fileSystem, &Software);
	usefulInfo Info(&userSource,&gameSource,&networkSource, &timeoutSource);
	genericEvent *ev;
	eventGenerator evGen(&Info);
	FSMGame gameFSM;
	FSMNetworking networkingFSM;
	
	
	cout << "Listening on port 13225..." << endl;
	communicator.startConnection();
	communicator.justConnected = 1;
	//networkSource.evCode = CONNECTED; //VEEEEER COMO MODIFICAR ESE evCode!!!!!!!!!!!!!!!
	cout << "Connection established" << endl;

	do
	{
		evGen.generateEvent();
		ev = evGen.getNextEvent();
		if (ev != nullptr)
		{
			networkingFSM.dispatch(ev, &Info);
			gameFSM.dispatch(ev, &Info);
		}
		/*if (skirmish.getPlaying())
		{
			cout << "MOSTRAR LA PANTALLA" << endl;
			Info.userSrc->graphics->loadBitmaps(skirmish.myMap);
			Info.userSrc->graphics->showMap(&skirmish);
		}*/

	} while (1); // (((gameFSM.getCurrentState())->getLastEvent() != END_PLAYING) &&
		//((networkingFSM.getCurrentState())->getLastEvent() != END_PLAYING));//VER BIEN ESTO
	//while (FSM.getCurrentState()->getLastEvent() != QUIT); //ver bien si este QUIT queda el mismo o si hay que cambiarlo
	//getchar();
}






