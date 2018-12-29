#ifndef GENERICEVENT_H
#define GENERICEVENT_H

#define DEBUG true

#include <string>

//lo que sigue a continuacion, ahora en vez de ponerlo aca lo puse en el archibo Events.h
// pero con los events que necesito ahora, que empiezan con R DE RECIBIDOS.
//typedef enum { NO_EV, QUIT, CLEAR, FILE_ERROR, ERRO, DATA, ACK, WRQ, RRQ, LAST_DATA, TIMEOUT, CONNECTION_FAIL } eventCode;
//Atencion que el evento ERROR es ERRO porque ERROR ya esta definido


typedef enum {
	//Eventos que genera la fsm de GAME :
	YOU_START, I_START, MOVE, PURCHASE, ATTACK, PASS, YOU_WON, PLAY_AGAIN,
	GAME_OVER, QUIT,

	//EVENTOS generados por Networking o otras sources:
	NO_EV, R_ACK, R_NAME, R_NAME_IS, R_MAP_IS, R_YOU_START, R_I_START,
	R_PASS, R_MOVE, R_PURCHASE, R_ATTACK, R_YOU_WON, R_PLAY_AGAIN,
	R_GAME_OVER, R_ERROR_, R_QUIT, ERR_DETECTED, CONNECTED,

	//Botones del juego:
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12,
	B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12,
	C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12,
	D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12,
	E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12,
	H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12,
	I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12,
	J1, J2, J3, J4, J5, J6, J7, J8, J9, J10, J11, J12,
	K1, K2, K3, K4, K5, K6, K7, K8, K9, K10, K11, K12,
	L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12,
	M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11, M12,
	N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12,
	O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12,
	P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12

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
