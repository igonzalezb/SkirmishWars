

#include "eventSources.h"
#include "Events.h"
#include <boost\algorithm\string\classification.hpp>
#include <boost\algorithm\string\split.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>
using namespace std;


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
#ifdef DEBUG
		cout << "insert event de map ok" << endl;
#endif //DEBUG
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
	case YOU_DIDNT_WIN:
		ret = (genericEvent *) new EV_YouDidntWin();
		break;
	case PLAY_AGAIN:
		cout << "inset event play again desde game" << endl;
		ret = (genericEvent *) new EV_PlayAgain();
		break;
	case GAME_OVER:
		ret = (genericEvent *) new EV_GameOver();
		break;
	case QUIT:
#ifdef DEBUG
		cout << "insert event quit, desde game" << endl;
#endif //_DEBUG
		ret = (genericEvent *) new EV_Quit();
		break;
	case END_PLAYING:
#ifdef DEBUG
		cout << "insert event end playing, desde game" << endl;
#endif //_DEBUG
		ret = (genericEvent *) new EV_EndPlaying();
		break;
	case ERR_DETECTED:	
		ret = (genericEvent *) new EV_ErrDetected();
		break;
	case R_YOU_START:
		ret = (genericEvent *) new EV_YouStart();
		break;
	case R_I_START:
		ret = (genericEvent *) new EV_IStart();
		break;
	case R_MOVE:
		ret = (genericEvent *) new EV_Rmove();	
		break;
	case R_PURCHASE:
		ret = (genericEvent *) new EV_Purchase();
		break;
	case R_ATTACK:
		ret = (genericEvent *) new EV_Attack();
		break;
	case R_PASS:
		ret = (genericEvent *) new EV_RPass();
		break;
	case R_YOU_WON:
		ret = (genericEvent *) new EV_YouWon();
		break;
	case R_GAME_OVER:
		ret = (genericEvent *) new EV_GameOver();
		break;
	case R_QUIT:
#ifdef DEBUG
		cout << "insert event r quit, desde game" << endl;
#endif //_DEBUG
		ret = (genericEvent *) new EV_Quit();
		break;
	case R_ERROR_:
#ifdef DEBUG
		cout << "insert event r error, desde game" << endl;
#endif //_DEBUG
		ret = (genericEvent *) new EV_Quit();
		break;
	case ERROR_:
#ifdef DEBUG
		cout << "insert event error, desde game" << endl;
#endif //_DEBUG
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
	bool ret = false;

	if (gameInterface->playerChosen)
	{
		if (gameInterface->Istart)
		{
			evCode = I_START;
		}
		else
			evCode = YOU_START;
		ret = true;
#ifdef DEBUG
		cout << "IS THERE EVENG:I START o YOU START" << endl;
#endif // DEBUG
		gameInterface->playerChosen = false; 
	}
	if (gameInterface->myMap->isMapReceivedOk)
	{
#ifdef DEBUG
		cout << "GENERA EVENTO MAP OK" << endl;
#endif // DEBUG		
		evCode = MAP_OK;
		gameInterface->myMap->isMapReceivedOk = false;
		ret = true;
	}
	if ((gameInterface->playerMe->getMoney())<=0)
	{
		evCode = NO_MONEY;
		ret = true;
	}

	if (gameInterface->getAnalyseVictory())
	{
		if(gameInterface->didHeWin())
		{
#ifdef DEBUG
			cout << "GENERA YOU WON" << endl;
#endif //_DEBUG
			evCode = YOU_WON;
		}
		else
		{
#ifdef DEBUG
			cout << "GENERA YOU didnt win" << endl;
#endif //_DEBUG
			evCode = YOU_DIDNT_WIN;
		}
		gameInterface->setAnalyseVictory(false);
		ret = true;
	}

	if (gameInterface->getAnalysePlayAgain())
	{
		if (gameInterface->getIWantToPlayAgain())
		{
#ifdef DEBUG
			cout << "GENERA PLAY AGAIN" << endl;
#endif //_DEBUG
			evCode = PLAY_AGAIN;
		}
		else
		{
#ifdef DEBUG
			cout << "GENERA GAME OVER" << endl;
#endif //_DEBUG
			evCode = GAME_OVER;
		}
		gameInterface->setAnalysePlayAgain(false);
		ret = true;
	}

	if (gameInterface->moving==true)
	{
					evCode = MOVE;
					gameInterface->moving = false;
					ret = true;
	}
	if (gameInterface->boardingAPC == true)
	{
		evCode = MOVE;
		gameInterface->boardingAPC = false;
		ret = true;
	}
	if (gameInterface->unboardingAPC == true)
	{
		evCode = MOVE;
		gameInterface->unboardingAPC = false;
		ret = true;
	}
	if (gameInterface->attacking == true)
	{
		if (((gameInterface->myMap->getTile(gameInterface->getDefender().i, gameInterface->getDefender().j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getDefender().i,gameInterface->getDefender().j)->getUnit()->getTeam()) == (gameInterface->playerYou->getTeam()))
			&&((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit()) != NULL) &&
			((gameInterface->myMap->getTile(gameInterface->getAttacker().i,gameInterface->getAttacker().j)->getUnit()->getTeam()) == (gameInterface->playerMe->getTeam())))
			//si las coordenadas de attacker y defender estan bien seteadas:
			{
				gameInterface->myMap->possibleAttack((gameInterface->myMap->getTile(gameInterface->getAttacker().i, gameInterface->getAttacker().j)->getUnit()), gameInterface->getAttacker().i, gameInterface->getAttacker().j, gameInterface->playerMe->getTeam());
				if ((gameInterface->myMap->canAttack[gameInterface->getDefender().i][gameInterface->getDefender().j]) == true)
				{
					evCode = ATTACK;
					gameInterface->attacking = false;
					ret = true;
#ifdef DEBUG
					cout << "se genera evento ATTACK!" << endl;
#endif // DEBUG

					
				}
			}
	}

	if (gameInterface->purchasing == true)
	{
#ifdef DEBUG
		cout << "ENTRA A IS THERE EVENT, PORQUE PURCHASING = TRUE" << endl;
#endif // DEBUG		
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
	if (gameInterface->getEndPlaying())
	{
#ifdef DEBUG
		cout << "is there event: end playing esta en trueeee" << endl;
#endif // DEBUG
		evCode = END_PLAYING;
		gameInterface->setEndPlaying(false);
		ret = true;
	}
	if (gameInterface->error)
	{
		cout << "is there event: error, desde game" << endl;
		evCode = ERROR_;
		gameInterface->error = false; //Ver
		ret = true;
	}
	if (gameInterface->quit)
	{
		cout << "is there event: quit, desde game" << endl;
		evCode = QUIT;
		gameInterface->quit = false; //Ver
		ret = true;
	}

	return ret;
}

//////////////////////NETWORK EVENT SOURCES////////////////////////////////////////////
/*****  NETWORK EVENT SOURCE  *****/
NetworkEventSource::NetworkEventSource(Networking *_networkInterface,Game* _gameInterface) :networkInterface(_networkInterface),gameInterface(_gameInterface)
{
	//gameInterface = _gameInterface;
	
	
}

//Chequea si se recibi� algo y se guarda la info correspondiente en r_algo en caso de haberla
bool NetworkEventSource::isThereEvent()
{
	bool ret = false;
	list<Unit>::iterator it4 = gameInterface->data->getUnitList().begin();
	std::vector<MYBYTE> aux; //en vez de MYBYTE se puede poner char ( que es lo que estaba) pero es lo mismo
	std::string auxstr; //ver si lo voy a usar o no
	int i;
	unsigned char temp;

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
			gameInterface->playerMe->setTeam(EQUIPO2); //cliente es equipo 2
			gameInterface->playerYou->setTeam(EQUIPO1); //server es equipo 1

		}
		else
		{
			evCode = CONNECTED_AS_SERVER;
			gameInterface->playerMe->setTeam(EQUIPO1); //server equipo 1
			gameInterface->playerYou->setTeam(EQUIPO2); //client equipo 2
		}
		ret = true;
	}

	else if (networkInterface->receivePackage())	//verifica si se recibio algo
	{
#ifdef DEBUG
		cout << "OP CODE RECIBIDO: " << (int)(networkInterface->getInputPackage()[0]) << " VS OP CODE QUIT: " << OP_QUIT << endl;

#endif // DEBUG

		if (networkInterface->getInputPackage()[0] == (-1))
		{
				evCode = R_QUIT;
				cout << "is there event desde networking: r quit CON EL IFFFF" << endl;
				ret = true;
		}
		else
		{
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
#ifdef DEBUG
				cout << "Opponent's Name: " << gameInterface->playerYou->getName() << endl;
#endif // DEBUG			
				ret = true;
				break;
			case OP_MAP_IS:
				evCode = R_MAP_IS;
#ifdef	DEBUG
				cout << "GENERA EL EVENTO MAP IS" << endl;
#endif	//DEBUG
				aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
				i = static_cast<int>(aux[1]);
				aux.erase(aux.begin());
				aux.erase(aux.begin());
				r_map.clear();
				r_map.insert(r_map.begin(), aux.begin(), aux.end());
				r_map_string.clear();
				for (char c : r_map) {
					r_map_string.push_back(c);
				}
				temp = r_map_string.back(); //el �ltimo char es el checksum
				gameInterface->myMap->setChecksumReceived(temp);
				r_map_string.pop_back();
				gameInterface->myMap->setMapName(r_map_string);
				gameInterface->myMap->generateTilesArray(gameInterface->data->getBuildingList(), gameInterface->data->getTerrainList(), gameInterface->data->getUnitList());
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
#ifdef DEBUG
				cout << "Attacker: i = " << (int)aux[1] << " j= " << (int)(aux[2] - 0x41) << endl;
				cout << "Defender: i = " << (int)aux[3] << " j= " << (int)(aux[4] - 0x41) << endl;
#endif // DEBUG
				gameInterface->setAttacker((int)aux[1], (int)(aux[2] - 0X41));
				gameInterface->setDefender((int)aux[3], (int)(aux[4] - 0X41));
				ret = true;
				break;
			case OP_PURCHASE:
				evCode = R_PURCHASE;
				aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
				r_unidad.clear();
				r_unidad.insert(r_unidad.begin(), aux.begin() + 1, aux.begin() + 3); //para que meta lo que hay en pos 1 y 2 de aux, se pone hasta +3 porque no incluye esa, sino que hasta la anterior.
				gameInterface->setDefender((int)aux[3], (int)(aux[4] - 0X41));

				//lo pasamos a string y lo guardamos en el tipo de newUnit adentro de networking:
				r_unidad_string.clear();
				for (char c : r_unidad) {
					r_unidad_string.push_back(c);
				}
#ifdef DEBUG
				cout << "UNIT QUE COMPARA EL ITERADOR: " << r_unidad_string.c_str() << endl;
#endif // DEBUG
				for (bool k = true; k && (it4 != gameInterface->data->getUnitList().end()); ++it4) {

#ifdef DEBUG
					cout << "lista con it4: " << it4->getType() << endl;
#endif // DEBUG
					if (strcmp(it4->getType().c_str(), r_unidad_string.c_str()) == false) {

						k = false;
						Unit *currUnit = new Unit(it4);
						currUnit->setTeam(gameInterface->playerYou->getTeam());
						gameInterface->setNewUnit(currUnit);
#ifdef DEBUG
						cout << "ENTRA AL IFFFFFFFFFF DEL ITERATOR, unidad cargada en New Unit: " << gameInterface->getNewUnit()->getName() << endl;

#endif // DEBUG
					}
				}
#ifdef DEBUG
				cout << "HOLA! coordenada DEFENDER :  (I= " << (int)aux[1] << "; J=" << (int)(aux[2] - 0X41) << " )" << endl;
				cout << "UNIDAD COMPRADA " << gameInterface->getNewUnit()->getName() << endl;

#endif // DEBUG

				ret = true;
				break;
			case OP_ATTACK:
				evCode = R_ATTACK;
				aux = std::vector<MYBYTE>(networkInterface->getInputPackage());

				gameInterface->setDie((int)aux[5]);
				gameInterface->setAttacker((int)aux[1], (int)(aux[2] - 0X41));
				gameInterface->setDefender((int)aux[3], (int)(aux[4] - 0X41));
#ifdef DEBUG
				cout << "Se arma eventio attack" << endl;
#endif // DEBUG
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
				cout << "is there event desde networking: r quit" << endl;
				ret = true;
				break;
			default:
				break;
			}
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
#ifdef DEBUG
		cout << "INSERT EVENT R PASS" << endl;
#endif // DEBUG
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
		cout << "insert event r error, desde networking" << endl;
		ret = (genericEvent *) new EV_Rerror_();
		break;
	case R_QUIT:
		cout << "insert event r quit, desde networking" << endl;
		ret = (genericEvent *) new EV_Rquit();
		break;
	case ERROR_:
		cout << "insert event error, desde networking" << endl;
		ret = (genericEvent *) new EV_Error_();
		break;
	case QUIT:
		cout << "insert event quit, desde networking" << endl;
		ret = (genericEvent *) new EV_Quit();
		break;
	case ERR_DETECTED:	
		ret = (genericEvent *) new EV_ErrDetected();
		break;
	case MOVE:		
		ret = (genericEvent *) new EV_Move();
		break;
	case PASS:	
		ret = (genericEvent *) new EV_Pass();
		break;
	case PURCHASE:		
		ret = (genericEvent *) new EV_Purchase();
		break;
	case ATTACK:	
		ret = (genericEvent *) new EV_Attack();
		break;
	default:
		break;
	}
	return ret;
}


/////////////////////USER EVENT SOURCES ///////////////////////////////////////////////
/*****  USER EVENT SOURCE  *****/
UserEventSource::UserEventSource(userInput* _userInterface, Game* _gameInterface):gameInterface(_gameInterface)
{
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
	bool ret = false;
	int button;
	
#ifdef DEBUG	//MOVERLO!!!!
	
#endif // DEBUG

	al_register_event_source(event_queue, al_get_display_event_source(gameInterface->graphics->getDisplay()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	if (al_is_event_queue_empty(event_queue))
	{
		ret = false;
	}
	else
	{
		ALLEGRO_EVENT ev;
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
				gameInterface->setEndPlaying(true);
				ret = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			if ((button = al_show_native_message_box(
				gameInterface->graphics->getDisplay(),
				"QUIT GAME",
				"Do you want to quit the game?",
				NULL,
				NULL,
				ALLEGRO_MESSAGEBOX_YES_NO
			)) == 1)
			{
				evCode = QUIT;
				ret = true;
			}
			
			break;
		default:
			ret = false;
			break;
		}
	}
	return ret;
}

eventCode UserEventSource::dispatchClick(int x, int y)
{
	int button;
	if (((0.0 < x) && (x < M_WIDTH(gameInterface->graphics->getDisplay()))) && ((0.0 < y) && (y < M_HEIGHT(gameInterface->graphics->getDisplay()))))
	{
		//Se cliqueo dentro del mapa
		for (int i = 0; i < (FILA); i++) {
			for (int j = 0; j < (COLUMNA); j++) {

				gameInterface->myMap->getTile(i, j)->toogleIsSelected(false);
			}
		}

		for (int i = 0; i < (FILA); i++) {
			for (int j = 0; j < (COLUMNA); j++) {
				if (((((T_WIDTH(gameInterface->graphics->getDisplay()) * j) < x) && (x < ((T_WIDTH(gameInterface->graphics->getDisplay()) * j) + T_WIDTH(gameInterface->graphics->getDisplay()))))) &&
					((((T_HEIGHT(gameInterface->graphics->getDisplay()) * i) < y) && (y < ((T_HEIGHT(gameInterface->graphics->getDisplay()) * i) + T_HEIGHT(gameInterface->graphics->getDisplay()))))))
				{
#ifdef DEBUG
					cout << "SE APRETO la fila:" << i << " , columna " << j << endl;
#endif // DEBUG
					gameInterface->setTileSelected(i, j);
					gameInterface->myMap->getTile(i, j)->toogleIsSelected(true);
					return TILE;
				}
			}
		}
	}

	else if ((((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay())))) &&
		((al_get_font_line_height(gameInterface->graphics->getMenuFont()) < y) && (y < (al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0)))))
	{
		//Se apreto ATTACK
#ifdef DEBUG
		cout << "Se apreto Attack" << endl;
#endif // DEBUG
		if (!gameInterface->graphics->wasAttackWarningShown() && gameInterface->graphics->getWarningsOnOff())
		{
			if ((button = al_show_native_message_box(
				gameInterface->graphics->getDisplay(),
				"WARNING",
				"Are you sure you want to attack?",
				"If you click \"yes\", you will no longer be able to move.",
				NULL,
				ALLEGRO_MESSAGEBOX_YES_NO)) == 1)
			{
				gameInterface->graphics->setAttackWarningShown(true);
				return BO_ATTACK;
			}
		}
		else
		{
			return BO_ATTACK;
		}
		
			
	}
	else if (((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay()))) &&
		(((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0)) < y) && (y < ((al_get_font_line_height((gameInterface->graphics->getMenuFont())) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0) * 2)))))
	{
		//Se apreto PASS
#ifdef DEBUG
		cout << "Se apreto Pass" << endl;
#endif // DEBUG
		if (gameInterface->graphics->getWarningsOnOff())
		{
			if ((button = al_show_native_message_box(
				gameInterface->graphics->getDisplay(),
				"WARNING",
				"Are you sure you want to pass your turn?", NULL, NULL,
				ALLEGRO_MESSAGEBOX_YES_NO)) == 1)
			{
				return PASS;
			}
		}
		else
			return PASS;
		
		
	}

	else if (((M_WIDTH(gameInterface->graphics->getDisplay()) < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay()))) &&
		(((((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0) * 2))) < y) && (y < (((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + (M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0) * 3))))))
	{
		//Se apreto PURCHASE
#ifdef DEBUG
		cout << "Se apreto Purchase\n" << endl;
#endif // DEBUG

		if (!gameInterface->graphics->wasPurchaseWarningShown() && gameInterface->graphics->getWarningsOnOff())
		{
			if ((button = al_show_native_message_box(
				gameInterface->graphics->getDisplay(),
				"WARNING",
				"Are you sure you want to purchase?",
				"If you click \"yes\", you will no longer be able to move & attack.",
				NULL,
				ALLEGRO_MESSAGEBOX_YES_NO)) == 1)
			{
				gameInterface->graphics->setPurchaseWarningShown(true);
				return BO_PURCHASE;
			}
		}
		else
		{
			return BO_PURCHASE;
		}
				
	}

	list<Unit>::iterator it3 = gameInterface->data->getUnitList().begin();
	for (int i = 0; i < 9; i++)
	{
		if (((M_WIDTH(gameInterface->graphics->getDisplay()) + 20 < x) && (x < al_get_display_width(gameInterface->graphics->getDisplay())))

			&& (((al_get_font_line_height(gameInterface->graphics->getMenuFont()) + 
			(M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0) * 3) + 
				(al_get_font_ascent(gameInterface->graphics->getMenuFont()) * i)
				< y) && (y <
				(al_get_font_line_height(gameInterface->graphics->getMenuFont()) + 
					(M_HEIGHT(gameInterface->graphics->getDisplay()) / 9.0) * 3) + 
					(al_get_font_ascent(gameInterface->graphics->getMenuFont()) * (i+1))))) 
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

	return NO_EV;
}

genericEvent * UserEventSource::insertEvent() 
{
	genericEvent * ret = (genericEvent *) new EV_ErrDetected();
	switch (evCode)
	{
	case NO_EV:
		ret = (genericEvent *) new EV_NoEv();
		break;
	case END_PLAYING:
		cout << "insert event end playing, desde user" << endl;
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
		ret = (genericEvent *) new EV_Pass();
		break;
	case BO_ATTACK:
		ret = (genericEvent *) new EV_BoAttack();
		break;
	case QUIT:
		cout << "insert event quit, desde user" << endl;

		ret = (genericEvent *) new EV_Quit();
		break;

	default:
		break;
	}
	return ret;
}


/*****  TIMEOUTS EVENT SOURCE  *****/

TimeoutEventSource::TimeoutEventSource()
{
	timeout = false;
	timerRunning1 = false;
	timerRunning2 = false;
	timeout10s = false;
	timeout30s = false;
	timeoutCount1 = false;
}

bool TimeoutEventSource::isThereEvent()
{
	timeout = false;
	if (((clock() - tInicial1) >= ONE_MIN * CLOCKS_PER_SEC) && timerRunning1)
	{
		timeout = true;
			evCode = ONE_MIN_TIMEOUT;
	}
	else if (((clock() - tInicial1) >= FIFTY_SEC * CLOCKS_PER_SEC) && timerRunning1 && (timeout10s == false))
	{
		timeout = true;
		timeout10s = true;
		timeoutCount1++;
		evCode = TEN_SEC_LEFT;
	}
	else if (((clock() - tInicial1) >= THIRTY_SEC * CLOCKS_PER_SEC) && timerRunning1 && (timeout30s == false))
	{
		timeout = true;
		timeout30s = true;
		timeoutCount1++;
		evCode = THIRTY_SEC_LEFT;
	}
	else if (((clock() - tInicial2) >= TWO_HALF_MIN * CLOCKS_PER_SEC) && timerRunning2)
	{
		timeout = true;
		timeoutCount1++;
		evCode = TWO_HALF_MIN_TIMEOUT;
	}
	else if (((clock() - tInicial1) >= timeoutCount1 * CLOCKS_PER_SEC) && timerRunning1)
	{
	timeout = true;
	evCode = ONE_SEC_TIMEOUT;
	timeoutCount1++;
	}
	else 
	{
		timeout = false;
		evCode = NO_EV;
	}
	return timeout;
}

void TimeoutEventSource::startTimer1()
{
	tInicial1 = clock();
	timerRunning1 = true;
	timeout10s = false;
	timeout30s = false;
	timeoutCount1 = 0;
}

void TimeoutEventSource::startTimer2()
{
	tInicial2 = clock();
	timerRunning2 = true;
}

void TimeoutEventSource::stopTimer1()
{
	timerRunning1 = false;
	timeoutCount1 = 0;
}

void TimeoutEventSource::stopTimer2()
{
	timerRunning2 = false;
}

unsigned int TimeoutEventSource::getTimeoutCount1()
{
	return timeoutCount1;
}

genericEvent * TimeoutEventSource::insertEvent()
{
	genericEvent * ret = (genericEvent *) new EV_ErrDetected();

	switch (evCode)
	{
	case ONE_MIN_TIMEOUT:
		ret = (genericEvent *) new EV_OneMinTimeout;
		break;
	case TWO_HALF_MIN_TIMEOUT:
		ret = (genericEvent *) new EV_EndPlaying; 
		break;
	case TEN_SEC_LEFT:
		ret = (genericEvent *) new EV_TenSecLeft;
		break;
	case THIRTY_SEC_LEFT:
		ret = (genericEvent *) new EV_ThirtySecLeft;
		break;
	case ONE_SEC_TIMEOUT:
		ret = (genericEvent *) new EV_OneSecTimeout;
		break;
	default:
		break;
	}
	return ret;
}