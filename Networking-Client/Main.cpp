
#include "usefulInfo.h"
#include "eventGenerator.h"
#include "genericFSM.h"
#include "eventSources.h"
//#include "Screen.h"
#include "Networking.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Windows.h"
using namespace std;

int main()
{
	std::cout << "Por favor ingrese la direccion IP del servidor a traves de la linea de comando.\n Ejemplo: 'Client.exe 192.168.0.50'" << std::endl;
	std::cout << "Presione una tecla para salir." << std::endl;
	getchar();

	std::string opponentsIP = "localhost"; //CAMBIAR y ver donde recibirlo y como
										   //Screen Terminal;
										   //FileSystem fileSystem;
	Networking Client(opponentsIP);
	//TimeoutEventSource Timeout;
	//SoftwareEventSource Software;
	NetworkEventSource networkSource(&Client);
	//UserEventSource userSource(&Terminal);
	//usefulInfo Info(&userSource, &Timeout, &networkSource, &fileSystem, &Software);
	usefulInfo Info(&networkSource);
	genericEvent *ev;
	eventGenerator evGen(&Info);
	genericFSM FSM;
	//Terminal.putClear("Listening on port 69...");
	cout << "Listening on port 69..." << endl; //VER EN QUE PUERTO
											   //Client.startConnection(SERVER_IP);
	Client.startConnection();
	//Terminal.putNext("Connection established");
	Client.justConnected = 1;
	//networkSource.evCode = CONNECTED; //VEEEEER COMO MODIFICAR ESE evCode!!!!!!!!!!!!!!!
	cout << "Connection established" << endl;


	do
	{
		evGen.generateEvent();
		ev = evGen.getNextEvent();
		if (ev != nullptr)
		{
#ifdef DEBUG
			cout << "entra 5: entro porque ev distinto de nullptr" << endl;
#endif // DEBUG
			FSM.dispatch(ev, &Info);
		}

	} while (FSM.getCurrentState()->getLastEvent() != QUIT); //ver bien si este QUIT queda el mismo o si hay que cambiarlo
}
