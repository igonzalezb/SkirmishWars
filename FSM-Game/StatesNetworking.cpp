
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
	Info->timeoutSrc->startTimer2();
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
	Info->nextPkg = new NameIs(Info->gameInterface->playerMe->getName());
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete NAME IS
	Info->timeoutSrc->stopTimer2();
	return ret;
}


genericState* ST_S_WaitingName::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING WHO STARTS: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
	return ret;
}


/////////////////////////////// ST_S_WaitingNameIsAck ///////////////////////////////

genericState* ST_S_WaitingNameIsAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S 4" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingMapIsAck();

	Info->gameInterface->myMap->randomMap();
	Info->gameInterface->myMap->generateTilesArray(Info->gameInterface->data->getBuildingList(), Info->gameInterface->data->getTerrainList(), Info->gameInterface->data->getUnitList());	
	//Info->gameInterface->myMap->updateFogOfWar(Info->gameInterface->playerMe->getTeam());
	//Info->gameInterface->graphics->loadBitmaps(Info->gameInterface->myMap);
	//Info->gameInterface->graphics->showMap(Info->gameInterface->data, Info->gameInterface->myMap, Info->gameInterface->playerMe->getMoney(), Info->gameInterface->playerMe->getTeam());
	
	Info->gameInterface->myMap->setChecksum();
	Info->nextPkg = new MapIs(Info->gameInterface->myMap->getMapName(), Info->gameInterface->myMap->getChecksum());
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	Info->timeoutSrc->stopTimer2();
	cout << "TERMINO DE MANDAR EL MAPA" << endl;
	return ret;
}

genericState* ST_S_WaitingNameIsAck::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING NAME IS ACK: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
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
	Info->timeoutSrc->stopTimer2();
	//Info->nextPkg = new MapIs();
	//Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	return ret;
}

genericState* ST_S_WaitingMapIsAck::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING MAP IS ACK: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
	return ret;
}

/////////////////////////////// ST_S_WaitingWhoStarts ///////////////////////////////

genericState* ST_S_WaitingWhoStarts::on_IStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S PLAYING" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_S_WaitingIPlayAck();
	Info->gameInterface->setIamPlaying(true);
	Info->nextPkg = new IStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete I START
	Info->timeoutSrc->startTimer2();
	return ret;
}

genericState* ST_S_WaitingWhoStarts::on_YouStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST S YOU PLAYING" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->gameInterface->setIamPlaying(false);
	Info->nextPkg = new YouStart();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete YOU START
	return ret;
}

/////////////////////////////// ST_S_WaitingIPlayAck ///////////////////////////////

genericState* ST_S_WaitingIPlayAck::on_Rack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	Info->timeoutSrc->stopTimer2();
	return ret;
}

genericState* ST_S_WaitingIPlayAck::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING I PLAY: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
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
	Info->nextPkg = new NameIs(Info->gameInterface->playerMe->getName());
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MAP IS
	Info->timeoutSrc->stopTimer2();
	return ret;
}

genericState* ST_C_WaitingName::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING NAME: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
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
	Info->timeoutSrc->stopTimer2();
	return ret;
}

genericState* ST_C_WaitingNameIsAck::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING NAME IS ACK: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
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
	cout << "ST C 6: C_WaitingWhoStarts::on_RyouStart" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_IPlay();
	Info->gameInterface->setIamPlaying(true);
	//Info->nextPkg = new Ack();
	//Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_C_WaitingWhoStarts::on_RIStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "ST c  R I START" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->gameInterface->setIamPlaying(false);
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

genericState* ST_IPlay::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "N ST I PLAY::onImove" << endl;
	genericState *ret = (genericState *) new ST_WaitingPlayAck();
	Info->nextPkg = new Move(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j, Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j);
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete MOVE
	Info->timeoutSrc->startTimer2();
	cout << "se envio el paquete de move" << endl;
	return ret;
}

genericState* ST_IPlay::on_Purchase(genericEvent *ev, usefulInfo * Info)
{
	cout << "N ST I PLAY::onIpurchase" << endl;
	genericState *ret = (genericState *) new ST_WaitingPlayAck();
	Info->nextPkg = new Purchase(Info->gameInterface->getNewUnit()->getType(), Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j);
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PURCHASE
	Info->timeoutSrc->startTimer2();
	return ret;
}

genericState* ST_IPlay::on_Attack(genericEvent *ev, usefulInfo * Info)
{
	cout << "N ST I PLAY::onIattack" << endl;
	//genericState *ret = (genericState *) new ST_WaitingCounterAttack(); //SACAMOS EL COUNTERATTACK
	genericState *ret = (genericState *) new ST_WaitingPlayAck();
	Info->nextPkg = new Attack(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j, Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j, Info->gameInterface->getDie());
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ATTACK
	Info->timeoutSrc->startTimer2();
	return ret;
}

genericState* ST_IPlay::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "N ST I PLAY::onIpass" << endl;
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->gameInterface->setIamPlaying(false);
	Info->nextPkg = new Pass();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PASS
	cout << "se envio el paquete de pass" << endl;
	return ret;
}

genericState* ST_IPlay::on_NoMoney(genericEvent *ev, usefulInfo * Info)
{
	cout << "N ST I PLAY::on no money" << endl;
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->gameInterface->setIamPlaying(false);
	Info->nextPkg = new Pass();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PASS
	cout << "se envio el paquete de pass" << endl;
	return ret;
}

genericState* ST_IPlay::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING PLAY ACK: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingAPlay(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->nextPkg = new Pass();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete PASS
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	return ret;
}

genericState* ST_IPlay::on_RYouWon(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "I Play: on R YOU WON" << endl;
	genericState *ret = (genericState *) new ST_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIamPlaying(true);
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
	cout << "Waiting play ACK: on R ACK" << endl;
	genericState *ret = (genericState *) new ST_IPlay();
	Info->timeoutSrc->startTimer2();
	return ret;
}

genericState* ST_WaitingPlayAck::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "N WAITING PLAY ACK: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
	return ret;
}

genericState* ST_WaitingPlayAck::on_RYouWon(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "waiting Play ack: on R YOU WON" << endl;
	genericState *ret = (genericState *) new ST_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIamPlaying(true);
	return ret;
}

/////////////////////////////// ST_WaitingCounterAttack ///////////////////////////////

genericState* ST_WaitingCounterAttack::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_IPlay();
	return ret;
}

/////////////////////////////// ST_WaitingAPlay ///////////////////////////////

genericState* ST_WaitingAPlay::on_RMove(genericEvent *ev, usefulInfo * Info)
{
	cout << " waitingAPlay: on R MOVE" << endl;
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_WaitingAPlay::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	cout << "waitingAPlay: on R PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Ack();
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_WaitingAPlay::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	cout << "waitingAPlay: on R attack" << endl;
	//genericState *ret = (genericState *) new ST_WaitingToAttack(); //SACAR LO DEL CONTRATAQUE
	genericState *ret = (genericState *) new ST_WaitingAPlay(); //esto para no hacer counterattack
	Info->nextPkg = new Ack(); //ESTA Y LA LINEA DE ABAJO SON SI NO USAMOS CONTRAATAQJE
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ACK
	return ret;
}

genericState* ST_WaitingAPlay::on_RPass(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "waitingAPlay: on R PASS, Y pasa a I PLAY" << endl;
	genericState *ret = (genericState *) new ST_IPlay();
	Info->gameInterface->setIamPlaying(true);
	return ret;
}

genericState* ST_WaitingAPlay::on_TwoHalfMinTimeout(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "N WAITING a PLAY: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection(); //VER ESTADO!! se perdio comunicacion
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	Info->gameInterface->setEndPlaying(true);
	return ret;
}

genericState* ST_WaitingAPlay::on_RYouWon(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "waitingAPlay: on R YOU WON" << endl;
	genericState *ret = (genericState *) new ST_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIamPlaying(true);
	return ret;
}

genericState* ST_WaitingAPlay::on_YouWon(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "N WAITING a PLAY: ON 2,5 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_WaitingYouWonResponse(); //VER ESTADO!! se perdio comunicacion
	Info->nextPkg = new YouWon();
	Info->networkInterface->sendPackage(Info->nextPkg);
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer2(); //CHEQUEAR
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingYouWonResponse::on_RplayAgain(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	genericState *ret = (genericState *) new ST_WaitingMyConfirmation();
}

genericState* ST_WaitingYouWonResponse::on_RgameOver(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{

}

///////////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingMyConfirmation::on_PlayAgain(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	genericState *ret = (genericState *) new ST_S_WaitingNameIsAck(); //PARA MANDARLE EL MAP IS
}

genericState* ST_WaitingMyConfirmation::on_GameOver(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	genericState *ret = (genericState *) new ST_WaitingGameOverAck();
	Info->nextPkg = new GameOver();
	Info->networkInterface->sendPackage(Info->nextPkg);
}

///////////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingGameOverAck::on_Rack(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	genericState *ret = (genericState *) new ST_WaitingConnection(); //PARA MANDARLE EL MAP IS
	//Info->gameInterface->
}

///////////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingPlayingAgainConfirmation::on_PlayAgain(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
	cout << "waitingAPlay: on R YOU WON" << endl;
	genericState *ret = (genericState *) new ST_C_WaitingMapIs();
	Info->gameInterface->setIamPlaying(true);
	Info->nextPkg = new PlayAgain();
	Info->networkInterface->sendPackage(Info->nextPkg);
	return ret;
}

genericState* ST_WaitingPlayingAgainConfirmation::on_GameOver(genericEvent *ev, usefulInfo * Info) //NO FALTA ALGO ACA??????????????????
{
//	cout << "waitingAPlay: on R YOU WON" << endl;
	genericState *ret = (genericState *) new ST_WaitingConnection();//jejejejeeee
	Info->gameInterface->setIamPlaying(true);
	Info->nextPkg = new GameOver();
	Info->networkInterface->sendPackage(Info->nextPkg);
	//APAGAAAAAAAAAAAAR!!!!!!!!!!!!!!!!!!!!
	Info->gameInterface->setEndPlaying(true);
	return ret;
}



/////////////////////////// ST_WaitingToAttack //////////////////////////////
genericState* ST_WaitingToAttack::on_Attack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_WaitingAPlay();
	Info->nextPkg = new Attack(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j, Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j, Info->gameInterface->getDie());
	Info->networkInterface->sendPackage(Info->nextPkg);	//Envio paquete ATTACK
	return ret;
}

/*
genericState* ST_WaitingAPlay::on_Rquit(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_QUITTTTTTT();
return ret;
}*/ //ver que hacer con el quit