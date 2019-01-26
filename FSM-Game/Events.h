#ifndef EVENTS_H
#define EVENTS_H

//#define DEBUG true

//#include "Screen.h"
#include "genericEvent.h"

typedef char MYBYTE;

//GAME EVENTS
/*
Eventos que genera la fsm de GAME :
YOU_START, I_START, MOVE, PURCHASE, ATTACK, PASS, YOU_WON, PLAY_AGAIN,
GAME_OVER */

class EV_MapOk : public genericEvent //VER QUIEN LO GENERA
{
public:
	EV_MapOk() { ev = MAP_OK; };
private:
};

class EV_YouStart : public genericEvent //VER QUIEN LO GENERA
{
public:
	EV_YouStart() { ev = YOU_START; };
private:
};

class EV_IStart : public genericEvent //VER QUIEN LO GENERA
{
public:
	EV_IStart() { ev = I_START; };
private:
};

class EV_Move : public genericEvent
{
public:
	EV_Move() { ev = MOVE; };
private:
};

class EV_Purchase : public genericEvent
{
public:
	EV_Purchase() { ev = PURCHASE; };
private:
};

class EV_Attack : public genericEvent
{
public:
	EV_Attack() { ev = ATTACK; };
private:
};

class EV_Pass : public genericEvent
{
public:
	EV_Pass() { ev = PASS; };
private:
};

class EV_YouWon : public genericEvent
{
public:
	EV_YouWon() { ev = YOU_WON; };
private:
};

class EV_YouDidntWin : public genericEvent
{
public:
	EV_YouDidntWin() { ev = YOU_DIDNT_WIN; };
private:
};

class EV_PlayAgain : public genericEvent
{
public:
	EV_PlayAgain() { ev = PLAY_AGAIN; };
private:
};

class EV_GameOver : public genericEvent
{
public:
	EV_GameOver() { ev = GAME_OVER; };
private:
};

class EV_EndPlaying : public genericEvent
{
public:
	EV_EndPlaying() { ev = END_PLAYING; };
private:
};

class EV_Quit : public genericEvent
{
public:
	EV_Quit() { ev = QUIT; };
private:
};


class EV_NoMoney : public genericEvent
{
public:
	EV_NoMoney() { ev = NO_MONEY; };
private:
};



/*
//USER EVENTS

class EV_Quit : public genericEvent
{
public:
EV_Quit() { ev = QUIT; };
private:

};

class EV_Clear : public genericEvent
{
public:
EV_Clear() { ev = CLEAR; };
private:

};
*/


/*
Eventos que genera la fsm de NETWORKING:
R_ACK, R_NAME, R_NAME_IS, R_MAP_IS, R_YOU_START, R_I_START,
R_PASS, R_MOVE, R_PURCHASE, R_ATTACK, R_YOU_WON, R_PLAY_AGAIN,
R_GAME_OVER, R_ERROR_, R_QUIT,*/


//NETWORK EVENTS

class EV_ConnectedAsServer : public genericEvent
{
public:
	EV_ConnectedAsServer() { ev = CONNECTED_AS_SERVER; };
	//TODO: funciones de cargar el buffer y de obetener la info

private:
	//unsigned int blockNumber;	//Guardar el numero de bloque aca.
	//MYBYTE* dataBuffer;
};

class EV_ConnectedAsClient : public genericEvent
{
public:
	EV_ConnectedAsClient() { ev = CONNECTED_AS_CLIENT; };
	//TODO: funciones de cargar el buffer y de obetener la info

private:
	//unsigned int blockNumber;	//Guardar el numero de bloque aca.
	//MYBYTE* dataBuffer;
};

class EV_Rack : public genericEvent
{
public:
	EV_Rack() { ev = R_ACK; };
	//TODO: funciones de cargar el buffer y de obetener la info

private:
	//unsigned int blockNumber;	//Guardar el numero de bloque aca.
	//MYBYTE* dataBuffer;
};

class EV_Rname : public genericEvent
{
public:
	EV_Rname() { ev = R_NAME; };

private:
	//unsigned int blockNumber;
};

class EV_RnameIs : public genericEvent
{
public:
	EV_RnameIs() { ev = R_NAME_IS; };

private:

};

class EV_RmapIs : public genericEvent
{
public:
	EV_RmapIs() { ev = R_MAP_IS; };

private:
	
};

class EV_RyouStart : public genericEvent
{
public:
	EV_RyouStart() { ev = R_YOU_START; };

private:
	

};

class EV_RIStart : public genericEvent
{
public:
	EV_RIStart() { ev = R_I_START; };

private:
	

};

class EV_RPass : public genericEvent
{
public:
	EV_RPass() { ev = R_PASS; };

private:
	
};

class EV_Rmove : public genericEvent
{
public:
	EV_Rmove() { ev = R_MOVE; };

private:

};

class EV_Rpurchase : public genericEvent
{
public:
	EV_Rpurchase() { ev = R_PURCHASE; };

private:
	
};

class EV_Rattack : public genericEvent
{
public:
	EV_Rattack() { ev = R_ATTACK; };

private:
	
};


class EV_RyouWon : public genericEvent
{
public:
	EV_RyouWon() { ev = R_YOU_WON; };

private:
	
};

class EV_RplayAgain : public genericEvent
{
public:
	EV_RplayAgain() { ev = R_PLAY_AGAIN; };

private:
	
};

class EV_RgameOver : public genericEvent
{
public:
	EV_RgameOver() { ev = R_GAME_OVER; };

private:
	
};

class EV_Rerror_ : public genericEvent
{
public:
	EV_Rerror_() { ev = R_ERROR_; };

private:
	
};

class EV_ErrDetected : public genericEvent
{
public:
	EV_ErrDetected() { ev = ERR_DETECTED; };

private:

};

class EV_Rquit : public genericEvent
{
public:
	EV_Rquit() { ev = R_QUIT; };

private:

};

//USER EVENTS
/*
Eventos que genera el usuario con mouse o teclado :
TILE, NEW_UNIT, PURCHASE, ATTACK, PASS */
class EV_NoEv : public genericEvent //VER QUIEN LO GENERA
{
public:
	EV_NoEv() { ev = NO_EV; };
private:
};

class EV_Tile
	: public genericEvent
{
public:
	EV_Tile() { ev = TILE; };
private:
};

class EV_NewUnit : public genericEvent
{
public:
	EV_NewUnit() { ev = NEW_UNIT; };
private:
};

class EV_BoAttack : public genericEvent
{
public:
	EV_BoAttack() { ev = BO_ATTACK; };
private:
};

class EV_BoPurchase : public genericEvent
{
public:
	EV_BoPurchase() { ev = BO_PURCHASE; };
private:
};


//TIMEOUT EVENT

/*class EV_Timeout : public genericEvent
{
public:
EV_Timeout() { ev = TIMEOUT; };

private:

};*/

class EV_OneMinTimeout : public genericEvent
{
public:
	EV_OneMinTimeout() { ev = ONE_MIN_TIMEOUT; };
private:
};

class EV_TwoHalfMinTimeout : public genericEvent
{
public:
	EV_TwoHalfMinTimeout() { ev = TWO_HALF_MIN_TIMEOUT; };
private:
};

class EV_TenSecLeft : public genericEvent
{
public:
	EV_TenSecLeft() { ev = TEN_SEC_LEFT; };
private:
};

class EV_ThirtySecLeft : public genericEvent
{
public:
	EV_ThirtySecLeft() { ev = THIRTY_SEC_LEFT; };
private:
};

class EV_OneSecTimeout : public genericEvent
{
public:
	EV_OneSecTimeout() { ev = ONE_SEC_TIMEOUT; };
private:
};


//class EV_ConnectionFailed : public genericEvent
//{
//public:
//	EV_ConnectionFailed() { ev = CONNECTION_FAIL; };
//
//private:
//
//};



#endif // !EVENTS_H

