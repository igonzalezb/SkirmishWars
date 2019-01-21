#include "FSMNetworking.h"

FSMNetworking::FSMNetworking()
{
	currentState = (genericState *) new ST_WaitingConnection(); //ver que poner
}

FSMNetworking::~FSMNetworking()
{
	delete currentState;
}

genericState * FSMNetworking::getCurrentState()
{
	return currentState;
}


void FSMNetworking::dispatch(genericEvent *ev, usefulInfo *Info)
{
	genericState *newState = nullptr;
	{
		switch (ev->getEventType())
		{

		case R_ACK:
			newState = currentState->on_Rack(ev, Info);
			break;
		case R_NAME:
			newState = currentState->on_Rname(ev, Info);
			break;
		case R_NAME_IS:
			newState = currentState->on_RnameIs(ev, Info);
			break;
		case R_MAP_IS:
			newState = currentState->on_RmapIs(ev, Info);
			break;
		case R_YOU_START:
			newState = currentState->on_RyouStart(ev, Info);
			break;
		case R_I_START:
			newState = currentState->on_RIStart(ev, Info);
			break;
		case R_PASS:
			newState = currentState->on_Rpass(ev, Info);
			break;
		case R_MOVE:
			newState = currentState->on_Rmove(ev, Info);
			break;
		case R_PURCHASE:
			newState = currentState->on_Rpurchase(ev, Info);
			break;
		case R_ATTACK:
			newState = currentState->on_Rattack(ev, Info);
			break;
		case R_YOU_WON:
			newState = currentState->on_RyouWon(ev, Info);
			break;
		case R_PLAY_AGAIN:
			newState = currentState->on_RplayAgain(ev, Info);
			break;
		case R_GAME_OVER:
			newState = currentState->on_RgameOver(ev, Info);
			break;
		case R_ERROR_:
			newState = currentState->on_Rerror_(ev, Info);  
			break;
		case R_QUIT:
			newState = currentState->on_Rquit(ev, Info);
			break;
		case ERR_DETECTED:
			newState = currentState->on_ErrDetected(ev, Info); //VER si este caso se deja o no 
															   //si lo saco, sacar tambien de generic_states.h, genericEvent.h
															   // se se deja, VER donde agregar en States.h
			break;
		case CONNECTED_AS_SERVER:
#ifdef DEBUG
			//cout << "entra 6: dispatcher en CONNECTED as server" << endl;
#endif // DEBUG
			//newState = currentState->on_Connected(ev, Info);
			newState = currentState->on_ConnectedAsServer(ev, Info);
			break;
		case CONNECTED_AS_CLIENT:
#ifdef DEBUG
			//cout << "entra 6: dispatcher en CONNECTED as client" << endl;
#endif // DEBUG
			//newState = currentState->on_Connected(ev, Info);
			newState = currentState->on_ConnectedAsClient(ev, Info);
			break;
		case MAP_OK:
			newState = currentState->on_MapOk(ev, Info);
			cout << "DISPATCH DE MAP OK" << endl;
			break;
		case I_START:
			newState = currentState->on_IStart(ev, Info);
			cout << "DISPATCH DE I START" << endl;
			break;
		case YOU_START:
			newState = currentState->on_YouStart(ev, Info);
			cout << "DISPATCH DE YOU START" << endl;
			break;
		default:
			break;
		}

		if (newState != nullptr)
		{
			delete currentState;
			currentState = newState;
		}
	}
}
