//HACER DESDE USER EVENT SOURCE: cuando el mouse ve que se toca un tile del mapa,
//guardar esa info en la clase game en tileSelected y generar el evento TILE

#include "eventSources.h"
//#include "Screen.h"
#include "Events.h"
//#include <boost\algorithm\string\classification.hpp>
//#include <boost\algorithm\string\split.hpp>
//#include <boost\date_time\posix_time\posix_time.hpp>
using namespace std;

//CAMBIAAAAAAAAAAAR TODO ESTE ARCHIVO ADAPTANDO PARA EL GAAAAAMEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*****  GAME EVENT SOURCE  *****/


GameEventSource::GameEventSource(Game *_gameInterface)
{

}


genericEvent * GameEventSource::insertEvent()
{
	genericEvent * ret;
	
	//COMPLETAR
}

bool GameEventSource::isThereEvent()
{
	bool ret = false;

	if ((gameInterface->playerMe->getMoney())<=0)
	{
		evCode = NO_MONEY;
		ret = true;
	}

	if (!(gameInterface->getNotWinning()))
	{
		evCode = YOU_WON; //VER en que parte se setea nuevamente notWinning en true (probablemente cuando arranca el juego)
		ret = true;
	}
	if (gameInterface->moving==true)
	{
		if ((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getUnit()) == NULL)
		{
			if (((gameInterface->myMap->getTile(gameInterface->getAttacker.i, gameInterface->getAttacker.j)->getUnit()) != NULL) &&
				(((gameInterface->myMap->getTile(gameInterface->getAttacker.i, gameInterface->getAttacker.j)->getUnit())->getTeam()) == (gameInterface->playerMe->getTeam())))
				//si el attacker es una unidad mia:
			{
				gameInterface->myMap->possibleMoves((gameInterface->myMap->getTile(gameInterface->getAttacker.i,gameInterface->getAttacker.j)->getUnit()), gameInterface->getAttacker.i,gameInterface->getAttacker.j);
				if ((gameInterface->myMap->canMove[gameInterface->getDefender.i][gameInterface->getDefender.j]) == true)
				{
					evCode = MOVE;
					gameInterface->moving = false;
				}
			}
		}
	}
	if (gameInterface->attacking == true)
	{
		if (((((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getUnit()->getTeam()) == (gameInterface->playerYou->getTeam()))) ||
			(((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getBuilding()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()->getTeam()) != (gameInterface->playerMe->getTeam()))))&&
			 
			(((gameInterface->myMap->getTile(gameInterface->getAttacker.i, gameInterface->getAttacker.j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getAttacker().i,gameInterface->getAttacker().j)->getUnit()->getTeam()) == (gameInterface->playerMe->getTeam()))))
			//si las coordenadas de attacker y defender estan bien seteadas:
			{
				evCode = ATTACK;
				gameInterface->attacking = false;
			}
	}

	if (gameInterface->purchasing == true)
	{
		if (((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()) != NULL) &&
			(((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()->getType()).compare("m")) == 0) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getBuilding()->getTeam()) == (gameInterface->playerMe->getTeam())) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getUnit()) == NULL) &&
			(stoi(gameInterface->getNewUnit()->getCost())) <= (gameInterface->playerMe->getMoney()))
		{
			evCode = PURCHASE;
			gameInterface->purchasing = false;
		}
	}

	//COMPLETAR
}

//////////////////////NETWORK EVENT SOURCES////////////////////////////////////////////
/*****  NETWORK EVENT SOURCE  *****/
NetworkEventSource::NetworkEventSource(Networking *_networkInterface,Game* _gameInterface) :networkInterface(_networkInterface)//:gameInterface(_gameInterface)
{
}

//Chequea si se recibió algo y se guarda la info correspondiente en r_algo en caso de haberla
bool NetworkEventSource::isThereEvent()
{
	//unsigned char blockLow, blockHigh;
	bool ret = false;
	//std::ifstream fileStream;
	std::vector<MYBYTE> aux; //en vez de MYBYTE se puede poner char ( que es lo que estaba) pero es lo mismo
	std::string auxstr; //ver si lo voy a usar o no
	int i;

	//VER COMO HACER PARA QUE APAREZCA UN EVENTO DE CONNECTED!!! CON SERVER. NO SE PUEDE

	if (networkInterface->justConnected)
	{
		//evCode = CONNECTED;
		networkInterface->justConnected = false;
#ifdef DEBUG
		cout << "ENTRA 1" << endl;
#endif // DEBUG
		if (networkInterface->IamClient)
		{
			evCode = CONNECTED_AS_CLIENT;
		}
		else
		{
			evCode = CONNECTED_AS_SERVER;
		}
		ret = true;
	}

	else if (networkInterface->receivePackage())	//verifica si se recibio algo
	{
#ifdef DEBUG
		cout << "entra 2 (aca no deberia entrar)" << endl;
#endif // DEBUG
		switch (networkInterface->getInputPackage()[0])	//segun el tipo de paquete devuelvo el tipo de evento
		{
		case OP_ACK: //sin campo de datos
			evCode = R_ACK;
			ret = true;
			break;
		case OP_NAME://sin campo de datos
			evCode = R_NAME;
			ret = true;
			break;
		case OP_NAME_IS: //guarda en r_name el nombre recibido (del oponente) por networking
			evCode = R_NAME_IS;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			i = static_cast<int>(aux[1]);
			aux.erase(aux.begin());
			aux.erase(aux.begin());
			r_name.clear();
			r_name.insert(r_name.begin(), aux.begin(), aux.end());

			//lo pasamos a string y lo guardamos en el nombre del player:
			for (char c : r_name) {
				r_name_string.push_back(c);
			}
			gameInterface->playerYou->setName(r_name_string);
			ret = true;
			break;
		case OP_MAP_IS:
			evCode = R_MAP_IS;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			i = static_cast<int>(aux[1]);
			aux.erase(aux.begin());
			aux.erase(aux.begin());
			r_map.clear();
			r_map.insert(r_map.begin(), aux.begin(), aux.end());
			
			//lo pasamos a string y lo guardamos en el nombre del player:
			for (char c : r_name) {
				r_map_string.push_back(c);
			}
			gameInterface->myMap->setMapName(r_map_string);
			ret = true;
			break;
		case OP_YOU_START: //sin campo de datos
			evCode = R_YOU_START;
			ret = true;
			break;
		case OP_I_START: //sin campo de datos
			evCode = R_I_START;
			ret = true;
			break;
		case OP_PASS: //sin campo de datos
			evCode = R_PASS;
			ret = true;
			break;
		case OP_MOVE:
			evCode = R_MOVE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			gameInterface->setAttacker((int)aux[1], (int)(aux[2]-'0X41'));
			gameInterface->setDefender((int)aux[3], (int)(aux[4]-'0X41'));
			ret = true;
			break;
		case OP_PURCHASE:
			evCode = R_PURCHASE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			r_unidad.clear();
			r_unidad.insert(r_unidad.begin(), aux.begin() + 1, aux.begin() + 3); //para que meta lo que hay en pos 1 y 2 de aux, se pone hasta +3 porque no incluye esa, sino que hasta la anterior.
			//r_fila_de = aux[1];
			//r_col_de = aux[2];
			gameInterface->setDefender((int)aux[1], (int)(aux[2]-'0X41'));
			//CARGAR LA UNIDAD CORRESPONDIENTE EN NEW UNIT ADENTRO DE GAME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			ret = true;
			break;
		case OP_ATTACK:
			evCode = R_ATTACK;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			/*
			r_fila_or = aux[1];
			r_col_or = aux[2];
			r_fila_de = aux[3];
			r_col_de = aux[4];
			r_dado = aux[5];
			*/
			gameInterface->setDie((int)aux[5]);
			gameInterface->setAttacker((int)aux[1], (int)(aux[2]-'0X41'));
			gameInterface->setDefender((int)aux[3], (int)(aux[4]-'0X41'));
			
			ret = true;
			break;
		case OP_YOU_WON: //sin campo de datos
			evCode = R_YOU_WON;
			ret = true;
			break;
		case OP_PLAY_AGAIN: //sin campo de datos
			evCode = R_PLAY_AGAIN;
			ret = true;
			break;
		case OP_GAME_OVER: //sin campo de datos
			evCode = R_GAME_OVER;
			ret = true;
			break;
		case OP_ERROR: //sin campo de datos
			evCode = R_ERROR_;
			ret = true;
			break;
		case OP_QUIT: //sin campo de datos
			evCode = R_QUIT;
			ret = true;
			break;
		default:
			break;
		}
	}
	return ret;
}

genericEvent * NetworkEventSource::insertEvent()
{
	genericEvent * ret = (genericEvent *) new EV_ErrDetected();
	switch (evCode)
	{
	case R_ACK:
		ret = (genericEvent *) new EV_Rack();
		break;
	case R_NAME:
		ret = (genericEvent *) new EV_Rname();
		break;
	case R_NAME_IS:
		ret = (genericEvent *) new EV_RnameIs();
		break;
	case R_MAP_IS:
		ret = (genericEvent *) new EV_RmapIs();
		break;
	case R_YOU_START:
		ret = (genericEvent *) new EV_RyouStart();
		break;
	case R_I_START:
		ret = (genericEvent *) new EV_RIStart();
		break;
	case R_PASS:
		ret = (genericEvent *) new EV_Rpass();
		break;
	case R_MOVE:
		ret = (genericEvent *) new EV_Rmove();
		break;
	case R_PURCHASE:
		ret = (genericEvent *) new EV_Rpurchase();
		break;
	case R_ATTACK:
		ret = (genericEvent *) new EV_Rattack();
		break;
	case R_YOU_WON:
		ret = (genericEvent *) new EV_RyouWon();
		break;
	case R_PLAY_AGAIN:
		ret = (genericEvent *) new EV_RplayAgain();
		break;
	case R_GAME_OVER:
		ret = (genericEvent *) new EV_RgameOver();
		break;
	case R_ERROR_:
		ret = (genericEvent *) new EV_Rerror_();
		break;
	case R_QUIT:
		ret = (genericEvent *) new EV_Rquit();
		break;
	case ERR_DETECTED:		//VER si este case se deja o si se saca
		ret = (genericEvent *) new EV_ErrDetected();
		break;
	case CONNECTED:
		ret = (genericEvent *) new EV_Connected();
#ifdef DEBUG
		cout << "entra 3: entro a insert event" << endl;
#endif // DEBUG
		break;
	default:
		break;
	}
	return ret;
}


/////////////////////USER EVENT SOURCES ///////////////////////////////////////////////
//UserEventSource::UserEventSource()
UserEventSource::UserEventSource(userInput* _userInterface, Game* _gameInterface)
{
	graphics = new MapGraphics;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_quieue!\n");
	}
}

bool UserEventSource::isThereEvent()
{
	bool redraw = false;
	bool ret = false;

	al_register_event_source(event_queue, al_get_display_event_source(graphics->getDisplay()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	if (al_is_event_queue_empty(event_queue))
	{
		ret = false;
	}
	else
	{
		ALLEGRO_EVENT ev;

		//al_wait_for_event(event_queue, &ev);
		al_get_next_event(event_queue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (ev.mouse.button == 1)		//Para usar solo el click izquierdo
			{
				evCode = graphics->dispatchClick(ev.mouse.x, ev.mouse.y, gameInterface);

				if (evCode == NO_EV)	//RET?????? VER!
					ret = false;
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				evCode = END_PLAYING;
				ret = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			evCode = END_PLAYING;
			ret = true;
			break;
		default:
			ret = false;
			break;
		}


	}

	return ret;

}
//
//eventCode UserEventSource::dispachClick(int x, int y)
//{
//	
//}


genericEvent * UserEventSource::insertEvent()
{
	genericEvent * ret;

	//COMPLETAR
}


/*
UserEventSource::UserEventSource()
{
}

bool UserEventSource::isThereEvent()
{

}

genericEvent * UserEventSource::insertEvent()
{

}
*/