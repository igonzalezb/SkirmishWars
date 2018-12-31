#ifndef GENERICEVENT_H
#define GENERICEVENT_H

#define DEBUG true

#include <string>

//lo que sigue a continuacion, ahora en vez de ponerlo aca lo puse en el archibo Events.h
// pero con los events que necesito ahora, que empiezan con R DE RECIBIDOS.
//typedef enum { NO_EV, QUIT, CLEAR, FILE_ERROR, ERRO, DATA, ACK, WRQ, RRQ, LAST_DATA, TIMEOUT, CONNECTION_FAIL } eventCode;
//Atencion que el evento ERROR es ERRO porque ERROR ya esta definido


typedef enum {
	NO_EV, R_ACK, R_NAME, R_NAME_IS, R_MAP_IS, R_YOU_START, R_I_START,
	R_PASS, R_MOVE, R_PURCHASE, R_ATTACK, R_YOU_WON, R_PLAY_AGAIN,
	R_GAME_OVER, R_ERROR_, R_QUIT, ERR_DETECTED, CONNECTED
} eventCode;


class genericEvent
{
public:
	genericEvent() { ev = NO_EV; }//por default, se setea el tipo de evento en NO_EV. Si otra clase hereda genericEvent, puede cambiar el constructor para setear el evento como el que corresponda
	eventCode getEventType() { return ev; }	//getter del tipo de evento

protected:
	//std::string selectedFile;
	eventCode ev;
};


#endif // !GENERICEVENT_H
