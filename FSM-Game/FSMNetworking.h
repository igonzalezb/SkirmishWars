#ifndef FSMNETWORKING_H
#define FSMNETWORKING

#include "genericFSM.h"

//probando con esto
#include "genericState.h"
#include "genericEvent.h"

//class FSMNetworking :public genericFSM 
class FSMNetworking
{
public:
	FSMNetworking();
	~FSMNetworking();

	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	

	genericState * getCurrentState();

	//ESTO QUE SIGUE NO LO PUSIMOS EN LAS HIJAS, SI NO FUNCION, PONERLO.
protected:
	genericState * currentState;
};

#endif //!FSMNETWORKING_H
