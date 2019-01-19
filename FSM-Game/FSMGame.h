#ifndef FSMGAME_H
#define FSMGAME

#include "genericFSM.h"

class FSMGame :public genericFSM 
{
public:
	FSMGame() :genericFSM() {};
	~FSMGame();
	genericState * getCurrentState();
	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	
};

#endif //!FSMGAME_H