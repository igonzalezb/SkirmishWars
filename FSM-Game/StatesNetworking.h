#ifndef STATESNETWORKING_H
#define STATESNETWORKING_H

#define DEBUG true

#include "genericState.h"

class ST_WaitingConnection :public genericState
{
	genericState* on_ConnectedAsServer(genericEvent* ev, usefulInfo * Info);
	genericState* on_ConnectedAsClient(genericEvent* ev, usefulInfo * Info);
};

//Estados en caso de ser SERVER:
class ST_S_WaitingNameIs :public genericState
{
	genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingName :public genericState
{
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingNameIsAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingMapIsAck :public genericState
{
	genericState* ST_S_WaitingMapIsAck::on_Rack(genericEvent *ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingWhoStarts :public genericState
{
	genericState* on_IStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouStart(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingIPlayAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

//Estados en caso de ser CLIENT:
class ST_C_WaitingName :public genericState
{
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingNameIsAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingNameIs :public genericState
{
	genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingMapIs : public genericState
{
	genericState* on_RmapIs(genericEvent *ev, usefulInfo * Info);
};

class ST_C_WaitingMapConfirmation :public genericState
{
	genericState* on_MapOk(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingWhoStarts :public genericState
{
	genericState* on_RyouStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_RIStart(genericEvent* ev, usefulInfo * Info);
	};

//Estados en comun para SERVER y CLIENT:
class ST_WaitingAPlay : public genericState
{
public:
	genericState* on_RMove(genericEvent* ev, usefulInfo * Info);
	genericState* on_RAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_IPlay : public genericState
{
public:
	genericState* on_Move(genericEvent* ev, usefulInfo * Info);
	genericState* on_Purchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Attack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_NoMoney(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouWon(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingPlayAck : public genericState
{
public:
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	genericState* on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouWon(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingToAttack : public genericState
{
public:
	genericState* on_Attack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingPlayingAgainConfirmation: public genericState
{
	genericState* on_PlayAgain(genericEvent *ev, usefulInfo * Info); 
	genericState* on_GameOver(genericEvent *ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingYouWonResponse : public genericState
{
	genericState* on_RplayAgain(genericEvent *ev, usefulInfo * Info);
	genericState* on_RgameOver(genericEvent *ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingMyConfirmation : public genericState
{
	genericState* on_PlayAgain(genericEvent *ev, usefulInfo * Info); 
	genericState* on_GameOver(genericEvent *ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class  ST_WaitingYourConfirmation : public genericState
{
	genericState* on_RplayAgain(genericEvent *ev, usefulInfo * Info);
	genericState* on_RgameOver(genericEvent *ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingGameOverAck : public genericState
{
	genericState* on_Rack(genericEvent *ev, usefulInfo * Info);
	genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};



#endif // !STATESNETWORKING_H
