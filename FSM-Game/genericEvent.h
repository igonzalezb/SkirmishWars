#ifndef GENERICEVENT_H
#define GENERICEVENT_H

//#define DEBUG true

#include <string>

//lo que sigue a continuacion, ahora en vez de ponerlo aca lo puse en el archibo Events.h
// pero con los events que necesito ahora, que empiezan con R DE RECIBIDOS.
//typedef enum { NO_EV, QUIT, CLEAR, FILE_ERROR, ERRO, DATA, ACK, WRQ, RRQ, LAST_DATA, TIMEOUT, CONNECTION_FAIL } eventCode;
//Atencion que el evento ERROR es ERRO porque ERROR ya esta definido


typedef enum {
	//Eventos que genera la fsm de GAME :

	CONNECTED_AS_CLIENT, CONNECTED_AS_SERVER, MAP_OK,

	YOU_START, I_START, MOVE, PURCHASE, ATTACK, PASS, YOU_WON, YOU_DIDNT_WIN, PLAY_AGAIN,
	GAME_OVER, QUIT,

	NO_MONEY,
	//EVENTOS generados por Networking o otras sources:
	NO_EV, R_ACK, R_NAME, R_NAME_IS, R_MAP_IS, R_YOU_START, R_I_START,
	R_PASS, R_MOVE, R_PURCHASE, R_ATTACK, R_YOU_WON, R_PLAY_AGAIN,
	R_GAME_OVER, R_ERROR_, R_QUIT, ERR_DETECTED, //CONNECTED,

	//Tiles presionados durante el juego:	//VER DE HACER QUE ESTOS NO SEAN EVENTOS
	//PROBABLEMENTE ESTOS SE ELIMINEN Y QUEDE SOLO TILE!!!!!!!!
	/*A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16,
	B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15, B16,
	C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16,
	D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15, D16,
	E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16,
	G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, G13, G14, G15, G16,
	H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12, H13, H14, H15, H16,
	I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16,
	J1, J2, J3, J4, J5, J6, J7, J8, J9, J10, J11, J12, J13, J14, J15, J16,
	K1, K2, K3, K4, K5, K6, K7, K8, K9, K10, K11, K12, K13, K14, K15, K16,
	L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15, L16,*/

	TILE, NEW_UNIT, BO_ATTACK, BO_PURCHASE, //ESTE QUEDA


	//Opciones de compra presionadas
	/*OPT_1, OPT_2, OPT_3, OPT_4, OPT_5, OPT_6, OPT_7, OPT_8, OPT_9,*/

	END_PLAYING,// VER SI ESTE ESTADO QUEDA O NO

	//EVENTOS generados por Timeout
	//TIMEOUT//, CONNECTION_FAIL
	ONE_MIN_TIMEOUT, TWO_HALF_MIN_TIMEOUT, TEN_SEC_LEFT, THIRTY_SEC_LEFT, ONE_SEC_TIMEOUT

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
