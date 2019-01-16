#ifndef GENERICFSM_H
#define GENERICFSM

#define DEBUG true

#include "genericState.h"
#include "genericEvent.h"

class genericFSM
{
public:
	genericFSM();	//Crea un estado al que apunta currentState
	~genericFSM();	//Destruye el estado al que apunta currentState

	virtual void dispatch(genericEvent * ev, usefulInfo *Info)=0;	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido
	genericState * getCurrentState();

	//ESTO QUE SIGUE NO LO PUSIMOS EN LAS HIJAS, SI NO FUNCION, PONERLO.
protected:
	genericState * currentState;	//se usa para apuntar a los estados, que son objetos de una clase que hereda la clase genericState
};

#endif // !GENERICFSM_H