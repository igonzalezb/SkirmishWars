#ifndef FSMGAME_H
#define FSMGAME

#include "StatesGame.h"

class FSMGame
{
public:
	FSMGame();	//Crea un estado al que apunta currentState
	~FSMGame();	//Destruye el estado al que apunta currentState

	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido
	genericState * getCurrentState();

protected:
	genericState * currentState;	//se usa para apuntar a los estados, que son objetos de una clase que hereda la clase genericState
};

#endif //!FSMGAME_H