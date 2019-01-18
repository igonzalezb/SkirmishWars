//CHEQUEAR TODOS LOS ON...

#ifndef STATESSERVER_H
#define STATESSERVER_H

#define DEBUG true

#include "genericState.h"

//VER si usar idle
/*
class ST_Idle : public genericState
{
public:
};*/

class ST_WaitingConnection :public genericState
{
	genericState* on_Connected(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingNameIs : public genericState
{
public:
	genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
private:
};


class ST_WaitingName : public genericState
{
public:
	genericState* on_Rname(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingNameIsAck : public genericState
{
public:
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingWhoStarts : public genericState //WaitingWhoStarts AND MAP IS ACK VEEEEEEEEER
{
public:
	genericState* on_IPlay(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouPlay(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingIPlayAck : public genericState
{
public:
	genericState* on_Rack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_WaitingAPlay : public genericState
{
public:
	//genericState* on_YourTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rattack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rquit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rpurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rmove(genericEvent* ev, usefulInfo * Info);
private:
};

class ST_IPlay : public genericState
{
public:
	genericState* on_Imove(genericEvent* ev, usefulInfo * Info);
	genericState* on_Ipurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Iattack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Ipass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Iquit(genericEvent* ev, usefulInfo * Info);
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

class ST_WaitingQuitAck : public genericState
{
public:
	genericState* on_RAck(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Rtimeout(genericEvent* ev, usefulInfo * Info);
private:
};

/*
class ST_WaitingWhoStarts : public genericState //ver esto si se cambia
{
public:
genericState* on_Imove(genericEvent* ev, usefulInfo * Info);
genericState* on_Ipurchase(genericEvent* ev, usefulInfo * Info);
genericState* on_Iattack(genericEvent* ev, usefulInfo * Info);
genericState* on_Ipass(genericEvent* ev, usefulInfo * Info);
genericState* on_YouStart(genericEvent* ev, usefulInfo * Info); //en este mandar un ack
//genericState* on_timeout(genericEvent* ev, usefulInfo * Info);
genericState* on_RQuit(genericEvent* ev, usefulInfo * Info);
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

/*
class ST_WaitingMapConfirmation : public genericState
{
public:
genericState* on_MapOk(genericEvent* ev, usefulInfo * Info);
genericState* on_RgameOver(genericEvent* ev, usefulInfo * Info);
//genericState* on_timeout(genericEvent* ev, usefulInfo * Info);
private:
};
*/

//VER que hacer con FINNNNNN
/*
class ST_Fin : public genericState //VER SI FIN CUENTA COMO UN ESTADO
{
public:
private:
};*/




#endif // !STATESSERVER_H
