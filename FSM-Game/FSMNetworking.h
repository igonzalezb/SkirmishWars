#ifndef FSMNETWORKING_H
#define FSMNETWORKING

//#include "genericFSM.h"

#include "StatesNetworking.h"

class FSMNetworking 
{
public:
	FSMNetworking();
	~FSMNetworking(); 

	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	
	genericState * getCurrentState();

protected:
	genericState * currentState;	//se usa para apuntar a los estados, que son objetos de una clase que hereda la clase genericState
};

#endif //!FSMNETWORKING_H
