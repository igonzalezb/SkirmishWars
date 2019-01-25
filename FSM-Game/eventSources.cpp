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


GameEventSource::GameEventSource(Game *_gameInterface):gameInterface(_gameInterface)
{

}


genericEvent * GameEventSource::insertEvent()
{
	genericEvent * ret = (genericEvent *) new EV_ErrDetected();
	switch (evCode)
	{
	case MAP_OK: //ESTE CREO QUE SE BORRA DE ACA
		ret = (genericEvent *) new EV_MapOk();
		break;
	case YOU_START:
		ret = (genericEvent *) new EV_YouStart();
		break;
	case I_START:
		ret = (genericEvent *) new EV_IStart();
		break;
	case MOVE:
		ret = (genericEvent *) new EV_Move();
		break;
	case PURCHASE:
		ret = (genericEvent *) new EV_Purchase();
		break;
	case ATTACK:
		ret = (genericEvent *) new EV_Attack();
		break;
	case PASS:
		ret = (genericEvent *) new EV_Pass();
		break;
	case TILE:
		ret = (genericEvent *) new EV_Tile;
		break;
	case NEW_UNIT:
		ret = (genericEvent *) new EV_NewUnit();
		break;
	case YOU_WON:
		ret = (genericEvent *) new EV_YouWon();
		break;
	case PLAY_AGAIN:
		ret = (genericEvent *) new EV_PlayAgain();
		break;
	case GAME_OVER:
		ret = (genericEvent *) new EV_GameOver();
		break;
	case QUIT:
		ret = (genericEvent *) new EV_Quit();
		break;
	case END_PLAYING:
		ret = (genericEvent *) new EV_EndPlaying();
		break;
	case ERR_DETECTED:		//VER si este case se deja o si se saca
		ret = (genericEvent *) new EV_ErrDetected();
		break;
	case R_YOU_START:
		ret = (genericEvent *) new EV_YouStart();
		break;
	case R_I_START:
		ret = (genericEvent *) new EV_IStart();
		break;
	case R_MOVE:
		ret = (genericEvent *) new EV_Rmove();	//PROPBAMOS CON R!!!!!!!!!!!!!!!!!!!!!!!
		break;
	case R_PURCHASE:
		ret = (genericEvent *) new EV_Purchase();
		break;
	case R_ATTACK:
		ret = (genericEvent *) new EV_Attack();
		break;
	case R_PASS:
		ret = (genericEvent *) new EV_RPass(); //PROPBAMOS CON R!!!!!!!!!!!!!!!!!!!!!!!
		break;
	case R_YOU_WON:
		ret = (genericEvent *) new EV_YouWon();
		break;
	case R_GAME_OVER:
		ret = (genericEvent *) new EV_GameOver();
		break;
	case R_QUIT:
		ret = (genericEvent *) new EV_Quit();
		break;
	case BO_PURCHASE:
		ret = (genericEvent *) new EV_BoPurchase();
		break;
	case BO_ATTACK:
		ret = (genericEvent *) new EV_BoAttack();
		break;
	case NO_MONEY:
		ret = (genericEvent *) new EV_BoAttack();
		break;
	default:
		break;
	}
	return ret;
}

bool GameEventSource::isThereEvent()
{
//	cout << "entra a is there event del game" << endl;
	bool ret = false;

	if (gameInterface->playerChosen)
	{
		if (gameInterface->Istart)
		{
		//	cout << "IS THERE EVENG:I START" << endl;
			//evCode = I_START;
			evCode = I_START;
		}
		else
			evCode = YOU_START;
		ret = true;
		cout << "IS THERE EVENG:I START o YOU START" << endl;
		gameInterface->playerChosen = false; //probando
	}

	if (gameInterface->myMap->isMapReceivedOk)
	{
		cout << "GENERA EVENTO MAP OK" << endl;
		evCode = MAP_OK;
		gameInterface->myMap->isMapReceivedOk = false;
		ret = true;
	}
	//cout << "plata actual: " << gameInterface->playerMe->getMoney() << endl;
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
		//if ((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getUnit()) == NULL)
		//{
		//	if (((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit()) != NULL) &&
		//		(((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit())->getTeam()) == (gameInterface->playerMe->getTeam())))
		//		//si el attacker es una unidad mia:
		//	{
				//gameInterface->myMap->possibleMoves((gameInterface->myMap->getTile(gameInterface->getAttacker().i,gameInterface->getAttacker().j)->getUnit()), gameInterface->getAttacker().i,gameInterface->getAttacker().j);
				//if ((gameInterface->myMap->canMove[gameInterface->getDefender().i][gameInterface->getDefender().j]) == true)
				//{
					cout << "ENTRO ACA !!!! SIIII  2" << endl;
					evCode = MOVE;
					gameInterface->moving = false;
					ret = true;
				//}
			/*}
		}*/
	}
	if (gameInterface->attacking == true)
	{
		if (((((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getUnit()->getTeam()) == (gameInterface->playerYou->getTeam()))) ||
			(((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getBuilding()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()->getTeam()) != (gameInterface->playerMe->getTeam()))))&&
			 
			(((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getAttacker().i,gameInterface->getAttacker().j)->getUnit()->getTeam()) == (gameInterface->playerMe->getTeam()))))
			//si las coordenadas de attacker y defender estan bien seteadas:
			{
				//gameInterface->myMap->possibleAttack((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit()), gameInterface->getAttacker().i, gameInterface->getAttacker().j);
				if (1)//(gameInterface->myMap->canAttack[gameInterface->getDefender().i][gameInterface->getDefender().j]) == true)
				{
					evCode = ATTACK;
					gameInterface->attacking = false;
					ret = true;
					cout << "se genera evento ATTACK!!!!!!!!!!!!!" << endl;
				}
			}
	}

	if (gameInterface->purchasing == true)
	{
		cout << "ENTRA A IS THERE EVENT, PORQUE PURCHASING = TRUE" << endl;
		if (((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()) != NULL) &&
			(((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getBuilding()->getType()).compare("m")) == 0) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getBuilding()->getTeam()) == (gameInterface->playerMe->getTeam())) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getUnit()) == NULL) &&
			(stoi(gameInterface->getNewUnit()->getCost())) <= (gameInterface->playerMe->getMoney()))
		{
			evCode = PURCHASE;
			gameInterface->purchasing = false;
			ret = true;
		}
	}

	//COMPLETAR
	return ret;
}

//////////////////////NETWORK EVENT SOURCES////////////////////////////////////////////
/*****  NETWORK EVENT SOURCE  *****/
NetworkEventSource::NetworkEventSource(Networking *_networkInterface,Game* _gameInterface) :networkInterface(_networkInterface),gameInterface(_gameInterface)
{
	//gameInterface = _gameInterface;
	
	
}

//Chequea si se recibió algo y se guarda la info correspondiente en r_algo en caso de haberla
bool NetworkEventSource::isThereEvent()
{
	//cout << "entra a is there event de networking" << endl;
	//unsigned char blockLow, blockHigh;
	bool ret = false;
	list<Unit>::iterator it4 = gameInterface->data->getUnitList().begin();
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
		//cout << "ENTRA 1" << endl;
#endif // DEBUG
		if (networkInterface->IamClient)
		{
			evCode = CONNECTED_AS_CLIENT;
			gameInterface->Istart = false;//ESTO ACA NO VA
			gameInterface->playerMe->setTeam(EQUIPO2); //cliente es equipo 2
			gameInterface->playerYou->setTeam(EQUIPO1); //server es equipo 1

			//gameInterface->myMap->updateFogOfWar(gameInterface->playerMe->getTeam());
			//gameInterface->myMap->updateFogOfWar(gameInterface->playerMe->getTeam());
			//gameInterface->graphics->loadBitmaps(gameInterface->myMap);
			//gameInterface->graphics->showMap(gameInterface->data, gameInterface->myMap, gameInterface->playerMe->getMoney());
			

		}
		else
		{
			evCode = CONNECTED_AS_SERVER;
			gameInterface->Istart = true;//ESTO ACA NO VA
			gameInterface->playerMe->setTeam(EQUIPO1); //server equipo 1
			gameInterface->playerYou->setTeam(EQUIPO2); //client equipo 2

			//gameInterface->myMap->updateFogOfWar(gameInterface->playerMe->getTeam());
			//gameInterface->myMap->updateFogOfWar(gameInterface->playerMe->getTeam());
			//gameInterface->graphics->loadBitmaps(gameInterface->myMap);
			//gameInterface->graphics->showMap(gameInterface->data, gameInterface->myMap, gameInterface->playerMe->getMoney());
		}
		ret = true;
	}

	else if (networkInterface->receivePackage())	//verifica si se recibio algo
	{
#ifdef DEBUG
	//	cout << "entra 2 (aca no deberia entrar)" << endl;
#endif // DEBUG
		if (networkInterface->getInputPackage()[0] == OP_PASS) {
			cout << "OP_PASS==INPUT PACKKKKKKKK" << endl;
		}
		cout << "OP CODE RECIBIDO: " << (int)(MYBYTE)(networkInterface->getInputPackage()[0]) << endl;

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
			cout << "opponent's name: " << gameInterface->playerYou->getName() << endl;
			ret = true;
			break;
		case OP_MAP_IS:
			evCode = R_MAP_IS;
			cout << "GENERA EL EVENTO MAP IS" << endl;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			i = static_cast<int>(aux[1]);
			aux.erase(aux.begin());
			aux.erase(aux.begin());
			r_map.clear();
			//r_map.insert(r_map.begin(), aux.begin(), aux.end());
			r_map.insert(r_map.begin(), aux.begin(), aux.end()-1);
			//lo pasamos a string y lo guardamos en el nombre del player:
			r_map_string.clear();
			for (char c : r_map) {
				r_map_string.push_back(c);
			}
			gameInterface->myMap->setMapName(r_map_string);
			gameInterface->myMap->generateTilesArray(gameInterface->data->getBuildingList(), gameInterface->data->getTerrainList(), gameInterface->data->getUnitList());
			gameInterface->myMap->updateFogOfWar(gameInterface->playerMe->getTeam());
			gameInterface->graphics->loadBitmaps(gameInterface->myMap);
			gameInterface->graphics->showMap(gameInterface->data, gameInterface->myMap, gameInterface->playerMe->getMoney(), gameInterface->playerMe->getTeam());
			
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
			cout << "ENTRA A IS THERE EVENT CON PASS" << endl;
			evCode = R_PASS;
			ret = true;
			break;
		case OP_MOVE:
			evCode = R_MOVE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			cout << "Attacker: i = " << (int)aux[1] << " j= " << (int)(aux[2]-0x41) << endl;
			cout << "Defender: i = " << (int)aux[3] << " j= " << (int)(aux[4]-0x41) << endl;
			gameInterface->setAttacker((int)aux[1], (int)(aux[2]-0X41));
			gameInterface->setDefender((int)aux[3], (int)(aux[4]-0X41));
			ret = true;
			break;
		case OP_PURCHASE:
			evCode = R_PURCHASE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());

			//cout << "aux: " << aux << endl;
			r_unidad.clear();
			r_unidad.insert(r_unidad.begin(), aux.begin() + 1, aux.begin() + 3); //para que meta lo que hay en pos 1 y 2 de aux, se pone hasta +3 porque no incluye esa, sino que hasta la anterior.
			//r_fila_de = aux[1];
			//r_col_de = aux[2];
			gameInterface->setDefender((int)aux[3], (int)(aux[4]-0X41));
		
			//lo pasamos a string y lo guardamos en el tipo de newUnit adentro de networking:
			r_unidad_string.clear();
			for (char c : r_unidad) {
				r_unidad_string.push_back(c);
			}
			cout << "UNIT QUE COMPARA EL ITERADOR: " << r_unidad_string.c_str() << endl;
			for (bool k = true; k && (it4 != gameInterface->data->getUnitList().end()); ++it4) {

				cout << "lista con it4: " << it4->getType() << endl;
				if (strcmp(it4->getType().c_str(), r_unidad_string.c_str()) == false) {
					
					k = false;
					Unit *currUnit = new Unit(it4);
					currUnit->setTeam(gameInterface->playerYou->getTeam());
					gameInterface->setNewUnit(currUnit);
					cout << "ENTRA AL IFFFFFFFFFF DEL ITERATOR, unidad cargada en New Unit: " << gameInterface->getNewUnit()->getName()<< endl;
				}
			}

			cout << "HOLA! coordenada DEFENDER :  (I= " << (int)aux[1] << "; J=" << (int)(aux[2] - 0X41) << " )" << endl;
			cout << "UNIDAD COMPRADA " << gameInterface->getNewUnit()->getName() << endl;
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
			gameInterface->setAttacker((int)aux[1], (int)(aux[2]-0X41));
			gameInterface->setDefender((int)aux[3], (int)(aux[4]-0X41));
			cout << "Se arma eventio attack" << endl;
			
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
	case CONNECTED_AS_CLIENT:
		ret = (genericEvent *) new EV_ConnectedAsClient();
#ifdef DEBUG
		cout << "entra 3: genera evento connected as client" << endl;
#endif // DEBUG
		break;
	case CONNECTED_AS_SERVER:
		ret = (genericEvent *) new EV_ConnectedAsServer();
#ifdef DEBUG
		cout << "entra 3: genera evento connected as server" << endl;
#endif // DEBUG
		break;
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
		cout << "INSERT EVENT R PASS" << endl;
		ret = (genericEvent *) new EV_RPass();
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
	case MOVE:		//VER si este case se deja o si se saca
		cout << "IMPRIMIO ESTOOOOOOOOOOOOOOOOOOOO" << endl;
		ret = (genericEvent *) new EV_Move();
		break;
	case PASS:		//VER si este case se deja o si se saca
		cout << "INSERT EVENT PASS (networking)" << endl;
		ret = (genericEvent *) new EV_Pass();
		break;
	case PURCHASE:		//VER si este case se deja o si se saca
		ret = (genericEvent *) new EV_Purchase();
		break;
	case ATTACK:		//VER si este case se deja o si se saca
		ret = (genericEvent *) new EV_Attack();
		break;
	default:
		break;
	}
	return ret;
}


/////////////////////USER EVENT SOURCES ///////////////////////////////////////////////
//UserEventSource::UserEventSource()
UserEventSource::UserEventSource(userInput* _userInterface, Game* _gameInterface):gameInterface(_gameInterface)
{
	//graphics = new MapGraphics;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_quieue!\n");
	}

	
}

UserEventSource::~UserEventSource()
{
	al_destroy_event_queue(event_queue);
}

bool UserEventSource::isThereEvent()
{
	//cout << "Entra a is there event de user" << endl;
	bool ret = false;
	int button;

#ifdef DEBUG
	gameInterface->graphics->setDisplayName("SKIRMISH WARS - PLAYER: " + gameInterface->playerMe->getName());	//Esto no va aca
#endif // DEBUG

	al_register_event_source(event_queue, al_get_display_event_source(gameInterface->graphics->getDisplay()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//graphics->loadBitmaps(gameInterface->myMap);	 //AGREGAR DENUEVO DES[PUES
	//graphics->showMap(gameInterface);

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
				if (gameInterface->getIamPlaying())	//si no es mi turno no entro
				{
					evCode = dispatchClick(ev.mouse.x, ev.mouse.y);
					ret = true;
				}
				
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				evCode = END_PLAYING;
				ret = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			button = al_show_native_message_box(
				gameInterface->graphics->getDisplay(),
				"QUIT GAME","Do you want to quit gane?","",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
			if (button == 1) {
				evCode = END_PLAYING;
				ret = true;
			}
			else
				ret = false;
			break;
		/*case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
			al_flip_display();
			break;*/
		default:
			ret = false;
			break;
		}


	}

#ifdef DEBUG
	//cout << "Salgo de isThereEvent del USER" << endl;
#endif // DEBUG

	return ret;

}

eventCode UserEventSource::dispatchClick(int x, int y)
{
	if (((0.0 < x) && (x < M_WIDTH(gameInterface->graphics->getDisplay()))) && ((0.0 < y) && (y < M_HEIGHT(gameInterface->graphics->getDisplay()))))
	{
		//Se cliqueo dentro del mapa
		for (int i = 0; i < (FILA); i++) {
			for (int j = 0; j < (COLUMNA); j++) {

				gameInterface->myMap->getTile(i, j)->toogleIsSelected(false);
				if (((((T_WIDTH(gameInterface->graphics->getDisplay()) * j) < x) && (x < ((T_WIDTH(gameInterface->graphics->getDisplay()) * j) + T_WIDTH(gameInterface->graphics->getDisplay()))))) &&
					((((T_HEIGHT(gameInterface->graphics->getDisplay()) * i) < y) && (y < ((T_HEIGHT(gameInterface->graphics->getDisplay()) * i) + T_HEIGHT(gameInterface->graphics->getDisplay()))))))
				{
					//Se cliqueo en la posicion ij (i:fila(16). j:col(12))
#ifdef DEBUG
					cout << "SE APRETO la fila:" << i << " , columna " << j << endl;
#endif // DEBUG
					gameInterface->setTileSelected(i, j);
					gameInterface->myMap->getTile(i, j)->toogleIsSelected(true);
					gameInterface->graphics->showMap(gameInterface->data, gameInterface->myMap, gameInterface->playerMe->getMoney(), gameInterface->playerMe->getTeam());
					return TILE;
				}
			}
		}
	}

	else if ((((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay())))) &&
		((al_get_font_line_height(gameInterface->graphics->getMenuFont()) < y) && (y < (al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0)))))
	{
		//Se apreto ATTACK
#ifdef DEBUG
		cout << "Se apreto Attack" << endl;
#endif // DEBUG
		return BO_ATTACK;
	}
	else if (((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay()))) &&
		(((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0)) < y) && (y < ((al_get_font_line_height((gameInterface->graphics->getMenuFont())) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0) * 2)))))
	{
		//Se apreto PASS
#ifdef DEBUG
		cout << "Se apreto Pass" << endl;
#endif // DEBUG
		return PASS;
	}

	else if (((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay()))) &&
		(((((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0) * 2))) < y) && (y < (((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0) * 3))))))
	{
		//Se apreto PURCHASE
#ifdef DEBUG
		cout << "Se apreto Purchase\n" << endl;
#endif // DEBUG
		return BO_PURCHASE;
	}

	list<Unit>::iterator it3 = gameInterface->data->getUnitList().begin();
	for (int i = 0; i < 9; i++)
	{
		if (((M_WIDTH(gameInterface->graphics->getDisplay()) + 20 < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay())))
			&& (((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0) * 3) + (al_get_font_line_height(gameInterface->graphics->getMenuFont()) * i)
				< y) && (y <
				(al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 8.0) * 3) + (al_get_font_line_height(gameInterface->graphics->getMenuFont()) * i) + al_get_font_line_height(gameInterface->graphics->getMenuFont()))))
		{
			// Se apreto para comprar la unidad de numero i de la lista
			advance(it3, i);
			Unit *currUnit = new Unit(it3);
			currUnit->setTeam(gameInterface->playerMe->getTeam());
			gameInterface->setNewUnit(currUnit);
#ifdef DEBUG
			cout << "Se apreto comprar: " << it3->getName() << endl;
#endif // DEBUG
			return NEW_UNIT;
		}

	}

#ifdef DEBUG
	cout << "No se apreto nada relevante" << endl;
#endif // DEBUG

	return NO_EV;		//VER!!!!!
}

genericEvent * UserEventSource::insertEvent() //COMPLETAR!!!
{
	genericEvent * ret = (genericEvent *) new EV_ErrDetected();
	switch (evCode)
	{
	case NO_EV:
		ret = (genericEvent *) new EV_NoEv();
		break;
	case END_PLAYING:
		ret = (genericEvent *) new EV_EndPlaying();
		break;
	case TILE:
		ret = (genericEvent *) new EV_Tile();
		break;
	case NEW_UNIT:
		ret = (genericEvent *) new EV_NewUnit();
		break;
	case BO_PURCHASE:
		ret = (genericEvent *) new EV_BoPurchase();
		break;
	case PASS:
		cout << "insert event PASS" << endl;
		ret = (genericEvent *) new EV_Pass();
		break;
	case BO_ATTACK:
		ret = (genericEvent *) new EV_BoAttack();
		break;

	default:
		break;
	}
	return ret;
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