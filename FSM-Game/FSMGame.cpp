#include "FSMGame.h"


FSMGame::FSMGame()
{
	currentState = (genericState *) new ST_GameIdle(); //ver que poner
}

FSMGame::~FSMGame()
{
	delete currentState;
}

genericState * FSMGame::getCurrentState()
{
	return currentState;
}

//HACER: CAMBIAR ESTA FUNCION, ADAPTANDOLA AL DISPATCHER DEL GAME!!!!!!!!!!!!!!!!
void FSMGame::dispatch(genericEvent *ev, usefulInfo *Info)
{
	genericState *newState = nullptr;
	{
		switch (ev->getEventType())
		{
		case I_START:
			newState = currentState->on_IStart(ev, Info);
			break;
		case YOU_START:
			newState = currentState->on_YouStart(ev, Info);
			break;
		case MOVE:
			newState = currentState->on_Move(ev, Info);
			break;
		case PURCHASE:
			newState = currentState->on_Purchase(ev, Info);
			break;
		case ATTACK:
			newState = currentState->on_Attack(ev, Info);
			break;
		case PASS:
			newState = currentState->on_Pass(ev, Info);
			break;
		case TILE:
			newState = currentState->on_Tile(ev, Info);
			break;
		case NEW_UNIT:
			newState = currentState->on_NewUnit(ev, Info);
			break;
		case NO_MONEY:
			newState = currentState->on_NoMoney(ev, Info);
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