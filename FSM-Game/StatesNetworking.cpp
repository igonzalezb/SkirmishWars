
#include "StatesNetworking.h"
//#include "Screen.h"
#include "Events.h"
#include <fstream>
#include <sstream>

/////////////////////////////// ST_WaitingConnection ///////////////////////////////

genericState* ST_WaitingConnection::on_ConnectedAsServer(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_S_WaitingNameIs();// ESTO VA!!!!!!!!!!!!!!!!!!!!!!!!!!! PERO ESTAMOS PROBANDO
	//genericState *ret = (genericState *) new ST_S_WaitingWhoStarts();
	Info->nextPkg = new Name();
#ifdef DEBUG
	cout << "ST S 1" << endl;
#endif // DEBUG
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME
	return ret;
}


genericState* ST_WaitingConnection::on_ConnectedAsClient(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_C_WaitingName();//ESTO VAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	//genericState *ret = (genericState *) new ST_C_WaitingWhoStarts();
#ifdef DEBUG
	cout << " ST C 1" << endl;
#endif // DEBUG
	return ret;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// SERVER /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////// ST_S_WaitingNameIs ///////////////////////////////

genericState* ST_S_WaitingNameIs::on_RnameIs(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S 2" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingName();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

/////////////////////////////// ST_S_WaitingName ///////////////////////////////

genericState* ST_S_WaitingName::on_Rname(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S 3" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingNameIsAck();
	Info->nextPkg = new NameIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME IS
	return ret;
}

/////////////////////////////// ST_S_WaitingNameIsAck ///////////////////////////////

genericState* ST_S_WaitingNameIsAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S 4" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingMapIsAck();
	Info->nextPkg = new MapIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	cout << "TERMINO DE MANDAR EL MAPA" << endl;
	return ret;
}

/////////////////////////////// ST_S_WaitingMapIsAck ///////////////////////////////

genericState* ST_S_WaitingMapIsAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S 4.1" << endl;
#endif // DEBUG
	Info->gameInterface->chooseWhoStarts();
	genericState *ret = (genericState *) new ST_S_WaitingWhoStarts();
	//Info->nextPkg = new MapIs();
	//Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	return ret;
}

/////////////////////////////// ST_S_WaitingWhoStarts ///////////////////////////////

genericState* ST_S_WaitingWhoStarts::on_IStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S PLAYING" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingIPlayAck();
	Info->nextPkg = new IStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete I START
	return ret;
}

genericState* ST_S_WaitingWhoStarts::on_YouStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S YOU PLAYING" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new YouStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete YOU START
	return ret;
}

/////////////////////////////// ST_S_WaitingIPlayAck ///////////////////////////////

genericState* ST_S_WaitingIPlayAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CLIENT /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////// ST_C_WaitingNameIsAck ///////////////////////////////

genericState* ST_C_WaitingName::on_Rname(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C 2" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_C_WaitingNameIsAck();
	Info->nextPkg = new NameIs();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	return ret;
}
/////////////////////////////// ST_C_WaitingNameIsAck ///////////////////////////////

genericState* ST_C_WaitingNameIsAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C 3" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_C_WaitingNameIs();
	Info->nextPkg = new Name();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	return ret;
}

/////////////////////////////// ST_C_WaitingNameIs ///////////////////////////////

genericState* ST_C_WaitingNameIs::on_RnameIs(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C 4" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_C_WaitingMapIs();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	cout << "termino de mandar ACK RESPONDIENDO AL NAME IS" << endl;
	return ret;
}

/////////////////////////////// ST_C_WaitingMapIs ///////////////////////////////

genericState* ST_C_WaitingMapIs::on_RmapIs(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C ON MAP IS" << endl;
#endif // DEBUG
	Info->gameInterface->myMap->verifyMapReceived();
	genericState *ret = (genericState *) new ST_C_WaitingMapConfirmation();
	//Info->nextPkg = new Ack();
	//Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}


/////////////////////////////// ST_C_WaitingMapConfirmation ///////////////////////////////

genericState* ST_C_WaitingMapConfirmation::on_MapOk(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C 5" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_C_WaitingWhoStarts();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	cout << "cliente responde con ACK AL SERVER CUANDO MANDA MAP IS" << endl;
	return ret;
}

/////////////////////////////// ST_C_WaitingWhoStarts ///////////////////////////////

//genericState* ST_C_WaitingWhoStarts::on_IPlay(genericEvent *ev, usefulInfo * Info)
genericState* ST_C_WaitingWhoStarts::on_RyouStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST C 6" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_IPlay();
	//Info->nextPkg = new Ack();
	//Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_C_WaitingWhoStarts::on_RIStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST R I START" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

/*
genericState* ST_C_WaitingWhoStarts::on_Rmove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_C_WaitingWhoStarts::on_Rpurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_C_WaitingWhoStarts::on_Rattack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingToAttack();
	return ret;
}

genericState* ST_C_WaitingWhoStarts::on_Rpass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}
*/


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// IN COMMON ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


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

/*
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
*/

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