//CHEQUEAR TODOS LOS ON...

#ifndef STATESNETWORKING_H
#define STATESNETWORKING_H

#define DEBUG true

#include "genericState.h"

class ST_WaitingConnection :public genericState
{
	genericState* on_ConnectedAsServer(genericEvent* ev, usefulInfo * Info);
	genericState* on_ConnectedAsClient(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

//Estados en caso de ser SERVER:
class ST_S_WaitingNameIs :public genericState
{
	genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingName :public genericState
{
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingNameIsAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingMapIsAck :public genericState
{
	genericState* ST_S_WaitingMapIsAck::on_Rack(genericEvent *ev, usefulInfo * Info);
};

class ST_S_WaitingWhoStarts :public genericState
{
	genericState* on_IPlay(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouPlay(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_S_WaitingIPlayAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

//Estados en caso de ser CLIENT:
class ST_C_WaitingName :public genericState
{
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingNameIsAck :public genericState
{
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingNameIs :public genericState
{
	genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingMapIs : public genericState
{
	genericState* on_RMapIs(genericEvent *ev, usefulInfo * Info);
};

class ST_C_WaitingMapConfirmation :public genericState
{
	genericState* on_MapOk(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_C_WaitingWhoStarts :public genericState
{
	genericState* on_IPlay(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rmove(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rattack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

//Estados en comun para SERVER y CLIENT:
class ST_WaitingAPlay : public genericState
{
public:
	//genericState* on_YourTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rmove(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rattack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_IPlay : public genericState
{
public:
	genericState* on_Imove(genericEvent* ev, usefulInfo * Info);
	genericState* on_Ipurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Iattack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Ipass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Iquit(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingPlayAck : public genericState
{
public:
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingCounterAttack : public genericState
{
public:
	genericState* on_Rattack(genericEvent* ev, usefulInfo * Info);
private:
};
/*
class ST_WaitingQuitAck : public genericState
{
public:
	genericState* on_RAck(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rtimeout(genericEvent* ev, usefulInfo * Info);
private:
};
*/
class ST_WaitingToAttack : public genericState
{
public:
	genericState* on_IAttack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rtimeout(genericEvent* ev, usefulInfo * Info);
private:
};


#endif // !STATESNETWORKING_H
