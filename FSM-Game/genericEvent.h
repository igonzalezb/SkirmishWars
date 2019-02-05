#ifndef GENERICEVENT_H
#define GENERICEVENT_H

#define DEBUG true

#include <string>


typedef enum {
	//Eventos que genera la fsm de GAME :
	CONNECTED_AS_CLIENT, CONNECTED_AS_SERVER, MAP_OK,
	YOU_START, I_START, MOVE, PURCHASE, ATTACK, PASS, YOU_WON, YOU_DIDNT_WIN, PLAY_AGAIN,
	GAME_OVER, QUIT, ERROR_,
	NO_MONEY,
	//EVENTOS generados por Networking o otras sources:
	NO_EV, R_ACK, R_NAME, R_NAME_IS, R_MAP_IS, R_YOU_START, R_I_START,
	R_PASS, R_MOVE, R_PURCHASE, R_ATTACK, R_YOU_WON, R_PLAY_AGAIN,
	R_GAME_OVER, R_ERROR_, R_QUIT, ERR_DETECTED, //CONNECTED,
	TILE, NEW_UNIT, BO_ATTACK, BO_PURCHASE,
	END_PLAYING,

	//EVENTOS generados por Timeout
	ONE_MIN_TIMEOUT, TWO_HALF_MIN_TIMEOUT, TEN_SEC_LEFT, THIRTY_SEC_LEFT, ONE_SEC_TIMEOUT

} eventCode;


class genericEvent
{
public:
	genericEvent() { ev = NO_EV; }	//por default, se setea el tipo de evento en NO_EV. Si otra clase hereda genericEvent, puede cambiar el constructor para setear el evento como el que corresponda
	eventCode getEventType() { return ev; }	//getter del tipo de evento
protected:
	eventCode ev;
};


#endif // !GENERICEVENT_H
