#include "FSMGame.h"

FSMGame::FSMGame()
{
	//currentState = (genericState *) new ST_WaitingConnection(); //ver que poner
}

FSMGame::~FSMGame()
{
	delete currentState;
}

//HACER: CAMBIAR ESTA FUNCION, ADAPTANDOLA AL DISPATCHER DEL GAME!!!!!!!!!!!!!!!!
void FSMGame::dispatch(genericEvent *ev, usefulInfo *Info)
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
		case CONNECTED:
#ifdef DEBUG
			cout << "entra 6: dispatcher en CONNECTED" << endl;
#endif // DEBUG
			newState = currentState->on_Connected(ev, Info);
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