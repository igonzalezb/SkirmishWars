#ifndef FSMNETWORKING_H
#define FSMNETWORKING

#include "genericFSM.h"

//probando con esto
//#include "genericState.h"
//#include "genericEvent.h"
#include "StatesNetworking.h"

class FSMNetworking :public genericFSM 
{
public:
	//FSMNetworking() :genericFSM() { currentState = (genericState *) new ST_WaitingConnection(); };
	FSMNetworking() :genericFSM() {};
	~FSMNetworking(); 
	genericState * getCurrentState();
	//genericState* genericFSM::getCurrentState();
	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	

};

#endif //!FSMNETWORKING_H
