#include "eventSources.h"
//#include "Screen.h"
#include "Events.h"
//#include <boost\algorithm\string\classification.hpp>
//#include <boost\algorithm\string\split.hpp>
//#include <boost\date_time\posix_time\posix_time.hpp>

//CAMBIAAAAAAAAAAAR TODO ESTE ARCHIVO ADAPTANDO PARA EL GAAAAAMEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*****  GAME EVENT SOURCE  *****/

/*
GameEventSource::GameEventSource(Game *_gameInterface) :gameInterface(_gameInterface)
{}
*/
GameEventSource::GameEventSource() //DESPUES CAMBIAR POR EL DE ARRIBA PORQUE VA A TENER QUE RECIBIR UNA CLASE CON INFO DEL JUEGO
{}



//Chequea si se recibi� algo y se guarda la info correspondiente en r_algo en caso de haberla
bool GameEventSource::isThereEvent()
{
	//unsigned char blockLow, blockHigh;
	bool ret = false;
	//std::ifstream fileStream;
	std::vector<MYBYTE> aux; //en vez de MYBYTE se puede poner char ( que es lo que estaba) pero es lo mismo
	std::string auxstr; //ver si lo voy a usar o no
	int i;

	//VER COMO HACER PARA QUE APAREZCA UN EVENTO DE CONNECTED!!! CON SERVER. NO SE PUEDE

	if (networkInterface->justConnected == 1)
	{
		evCode = CONNECTED;
		networkInterface->justConnected = 0;
#ifdef DEBUG
		cout << "ENTRA 1" << endl;
#endif // DEBUG

		ret = true;
	}

	else if (networkInterface->receivePackage())	//verifica si se recibio algo
	{
#ifdef DEBUG
		cout << "entra 2 (aca no deberia entrar)" << endl;
#endif // DEBUG
		switch (networkInterface->getInputPackage()[0])	//segun el tipo de paquete devuelvo el tipo de evento
		{
		case ACK: //sin campo de datos
			evCode = R_ACK;
			ret = true;
			break;
		case NAME://sin campo de datos
			evCode = R_NAME;
			ret = true;
			break;
		case NAME_IS: //guarda en r_name el nombre recibido (del oponente) por networking
			evCode = R_NAME_IS;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			i = static_cast<int>(aux[1]);
			aux.erase(aux.begin());
			aux.erase(aux.begin());
			r_name.clear();
			r_name.insert(r_name.begin(), aux.begin(), aux.end());
			ret = true;
			/*for (int j = 0; j < i; j++) {
			cout << name[j];
			}*/
			break;
		case MAP_IS:
			evCode = R_MAP_IS;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			i = static_cast<int>(aux[1]);
			aux.erase(aux.begin());
			aux.erase(aux.begin());
			r_map.clear();
			r_map.insert(r_map.begin(), aux.begin(), aux.end());
			ret = true;
			/*for (int j = 0; j < i; j++) {
			cout << name[j];
			}*/
			break;
		case YOU_START: //sin campo de datos
			evCode = R_YOU_START;
			ret = true;
			break;
		case I_START: //sin campo de datos
			evCode = R_I_START;
			ret = true;
			break;
		case PASS: //sin campo de datos
			evCode = R_PASS;
			ret = true;
			break;
		case MOVE:
			evCode = R_MOVE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			r_fila_or = aux[1];
			r_col_or = aux[2];
			r_fila_de = aux[3];
			r_col_de = aux[4];
			ret = true;
			break;
		case PURCHASE:
			evCode = R_PURCHASE;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			r_unidad.clear();
			r_unidad.insert(r_unidad.begin(), aux.begin() + 1, aux.begin() + 3); //para que meta lo que hay en pos 1 y 2 de aux, se pone hasta +3 porque no incluye esa, sino que hasta la anterior.
			r_fila_de = aux[1];
			r_col_de = aux[2];
			ret = true;
			/*for (int j = 0; j < 2; j++) {
			cout << r_unidad[j];
			}*/

			break;
		case ATTACK:
			evCode = R_ATTACK;
			aux = std::vector<MYBYTE>(networkInterface->getInputPackage());
			r_fila_or = aux[1];
			r_col_or = aux[2];
			r_fila_de = aux[3];
			r_col_de = aux[4];
			r_dado = aux[5];
			ret = true;
			break;
		case YOU_WON: //sin campo de datos
			evCode = R_YOU_WON;
			ret = true;
			break;
		case PLAY_AGAIN: //sin campo de datos
			evCode = R_PLAY_AGAIN;
			ret = true;
			break;
		case GAME_OVER: //sin campo de datos
			evCode = R_GAME_OVER;
			ret = true;
			break;
		case ERROR_: //sin campo de datos
			evCode = R_ERROR_;
			ret = true;
			break;
		case QUIT: //sin campo de datos
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
