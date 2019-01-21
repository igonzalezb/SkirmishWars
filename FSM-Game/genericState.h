//Revisar bien los estados, por ejemplo:WaitingWhoStarts y WaitingWhoStartsAndMapAck (ver si se hace uno solo)
#ifndef GENERICSTATE_H
#define GENERICSTATE_H

#define DEBUG true

#include "usefulInfo.h"
#include "genericEvent.h"

class genericState
{
public:
	// Estas funciones responden a los eventos recibidos en el estado actual. 
	//Por default, se toma que los eventos recibidos son eventos inesperados, 
	//lo que se indica devolviendo nullptr. Al ser virtuales, las clases 
	//de los estados especificos que heredan a genericState pueden redefinir 
	//que respuesta tomar ante los eventos que no son inesperados para ese estado en especifico.

	
	virtual genericState* on_NoEv(genericEvent* ev) { return nullptr; }

	virtual genericState* on_WaitingConnection(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Connected(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_ConnectedAsServer(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_ConnectedAsClient(genericEvent* ev, usefulInfo * Info) { return nullptr; }


	virtual genericState* on_MapSelected(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_WaitingMapIs(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	//virtual genericState* on_RMapIs(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_WaitingMapConfirmation(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_MapOk(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_ErrDetected(genericEvent* ev, usefulInfo * Info) { return nullptr; } //VER si esto se deja o no.

	//ESTOS DOS VER SI SE BORRAN O QUE HACER:
	virtual genericState* on_IPlay(genericEvent* ev, usefulInfo * Info) { return nullptr; } //VER si estos dos se usan en la fsm del juego o no.
	virtual genericState* on_YouPlay(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_IStart(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_YouStart(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	
	//virtual genericState* on_Iquit(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Move(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Purchase(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Attack(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Pass(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Tile(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_NewUnit(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_NoMoney(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	//virtual genericState* on_Timeout(genericEvent* ev, usefulInfo * Info) { return nullptr; }


	virtual genericState* on_Rack(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rname(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_RnameIs(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_RmapIs(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_RyouStart(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_RIStart(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rpass(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rmove(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rpurchase(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rattack(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_RyouWon(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_RplayAgain(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_RgameOver(genericEvent* ev, usefulInfo * Info) { return nullptr; }

	virtual genericState* on_Rerror_(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	virtual genericState* on_Rquit(genericEvent* ev, usefulInfo * Info) { return nullptr; }
	//virtual genericState* on_Rtimeout(genericEvent* ev, usefulInfo * Info) { return nullptr; }


	void setLastEvent(eventCode lastEvent) { this->lastEvent = lastEvent; }   //setter
	eventCode getLastEvent() { return lastEvent; }    //getter de last event
													  //std::string getSelectedFile() { return fileToTransfer; }
													  //void setFileToTransfer(std::string selectedFile) { this->fileToTransfer = selectedFile; }

protected:
	eventCode lastEvent;
	//std::string fileToTransfer;
};

#endif // !GENERICSTATE_H