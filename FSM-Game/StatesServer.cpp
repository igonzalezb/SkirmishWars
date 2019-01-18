
#include "StatesServer.h"
//#include "Screen.h"
#include "Events.h"
#include <fstream>
#include <sstream>

/////////////////////////////// ST_WaitingConnection ///////////////////////////////

genericState* ST_WaitingConnection::on_Connected(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingNameIs();
	Info->nextPkg = new Name();
#ifdef DEBUG
	cout << "entra 7: funcion on Connected" << endl;
#endif // DEBUG
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME
	return ret;
}

// este caso que sigue aca on Rname en waiting connection es si soy el client
// (ver si esto queda o si ya por default uno es server de entrada o client)
genericState* ST_WaitingConnection::on_Rname(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingNameIsAck();
	Info->nextPkg = new NameIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME IS
	return ret;
}

/////////////////////////////// ST_WaitingNameIs ///////////////////////////////

genericState* ST_WaitingNameIs::on_RnameIs(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingName();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

/////////////////////////////// ST_WaitingName ///////////////////////////////

genericState* ST_WaitingName::on_Rname(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingNameIsAck();
	Info->nextPkg = new NameIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME IS
	return ret;
}

/////////////////////////////// ST_WaitingNameIsAck ///////////////////////////////

genericState* ST_WaitingNameIsAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingWhoStarts();
	Info->nextPkg = new MapIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	return ret;
}

/////////////////////////////// ST_WaitingWhoStarts ///////////////////////////////

genericState* ST_WaitingWhoStarts::on_IPlay(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingIPlayAck();
	Info->nextPkg = new IStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete I START
	return ret;
}

genericState* ST_WaitingWhoStarts::on_YouPlay(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new YouStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete YOU START
	return ret;
}

/////////////////////////////// ST_WaitingIPlayAck ///////////////////////////////

genericState* ST_WaitingIPlayAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}

/////////////////////////////// ST_IPlay ///////////////////////////////

genericState* ST_IPlay::on_Imove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingPlayAck();
	Info->nextPkg = new Move();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MOVE
	return ret;
}

genericState* ST_IPlay::on_Ipurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingPlayAck();
	Info->nextPkg = new Purchase();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PURCHASE
	return ret;
}

genericState* ST_IPlay::on_Iattack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingCounterAttack();
	Info->nextPkg = new Attack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ATTACK
	return ret;
}

genericState* ST_IPlay::on_Ipass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Pass();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PASS
	return ret;
}

genericState* ST_IPlay::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Pass();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PASS
	return ret;
}

genericState* ST_IPlay::on_Iquit(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingQuitAck();
	Info->nextPkg = new Quit();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete QUIT
	return ret;
}

/////////////////////////////// ST_WaitingPlayAck ///////////////////////////////

genericState* ST_WaitingPlayAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}

/////////////////////////////// ST_WaitingCounterAttack ///////////////////////////////

genericState* ST_WaitingCounterAttack::on_Rattack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}

/////////////////////////////// ST_WaitingAPlay ///////////////////////////////

genericState* ST_WaitingAPlay::on_Rmove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_WaitingAPlay::on_Rpurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_WaitingAPlay::on_Rattack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingToAttack();
	return ret;
}

genericState* ST_WaitingAPlay::on_Rpass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}

genericState* ST_WaitingToAttack::on_IAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Attack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ATTACK
	return ret;
}

/*
genericState* ST_WaitingAPlay::on_Rquit(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_QUITTTTTTT();
return ret;
}*/ //ver que hacer con el quit