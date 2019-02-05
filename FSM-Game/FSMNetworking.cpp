#include "FSMNetworking.h"

FSMNetworking::FSMNetworking()
{
	currentState = (genericState *) new ST_WaitingConnection(); 
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
			newState = currentState->on_RPass(ev, Info);
			break;
		case R_MOVE:
			newState = currentState->on_RMove(ev, Info);
			break;
		case R_PURCHASE:
			newState = currentState->on_RPurchase(ev, Info);
			break;
		case R_ATTACK:
			newState = currentState->on_RAttack(ev, Info);
			break;
		case R_YOU_WON:
			newState = currentState->on_RYouWon(ev, Info);
			break;
		case R_PLAY_AGAIN:
			cout << "dispatch de r play again en networking" << endl;
			newState = currentState->on_RplayAgain(ev, Info);
			break;
		case R_GAME_OVER:
			cout << "dispatch de r game over en networking" << endl;
			newState = currentState->on_RgameOver(ev, Info);
			break;
		case R_ERROR_:
			newState = currentState->on_Rerror(ev, Info);  
			break;
		case R_QUIT:
			newState = currentState->on_Rquit(ev, Info);
			break;
		case ERR_DETECTED:
			newState = currentState->on_ErrDetected(ev, Info); 
			break;
		case CONNECTED_AS_SERVER:
#ifdef DEBUG
			cout << "entra 6: dispatcher en CONNECTED as server" << endl;
#endif // DEBUG
			newState = currentState->on_ConnectedAsServer(ev, Info);
			break;
		case CONNECTED_AS_CLIENT:
#ifdef DEBUG
			cout << "entra 6: dispatcher en CONNECTED as client" << endl;
#endif // DEBUG
			newState = currentState->on_ConnectedAsClient(ev, Info);
			break;
		case MAP_OK:
			newState = currentState->on_MapOk(ev, Info);
			cout << "DISPATCH DE MAP OK" << endl;
			break;
		case I_START:
			newState = currentState->on_IStart(ev, Info);
			break;
		case YOU_START:
			newState = currentState->on_YouStart(ev, Info);
			break;
		case PASS:
			newState = currentState->on_Pass(ev, Info);
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
		case NO_MONEY:
			newState = currentState->on_NoMoney(ev, Info);
			break;
		case ONE_MIN_TIMEOUT:
			newState = currentState->on_OneMinTimeout(ev, Info);
			break;
		case TWO_HALF_MIN_TIMEOUT:
			newState = currentState->on_TwoHalfMinTimeout(ev, Info);
			break;
		case YOU_WON:
			newState = currentState->on_YouWon(ev, Info);
			break;
		case END_PLAYING:
			cout << "dispatch de networking en end playing" << endl;
			newState = currentState->on_Pass(ev, Info); 
			break;
		case QUIT: 
			newState = currentState->on_Quit(ev, Info); 
			break;
		case ERROR_: 
			newState = currentState->on_Error(ev, Info); 
			break;
		case PLAY_AGAIN: 
			newState = currentState->on_PlayAgain(ev, Info); 
			break;
		case GAME_OVER: 
			newState = currentState->on_GameOver(ev, Info); 
			break;
		default:
			break;
		}
		if (newState != nullptr)
		{
			delete currentState;
			currentState = newState;
			currentState->setLastEvent(ev->getEventType()); 
			if (ev->getEventType() == END_PLAYING)
			{
				cout << "NET: ev getEventType = END_PLAYING!!!!!!!!!!!!!!!" << endl;
			}
		}


	}
}
