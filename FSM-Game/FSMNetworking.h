#ifndef FSMNETWORKING_H
#define FSMNETWORKING

#include "genericFSM.h"

class FSMNetworking :public genericFSM 
{
public:
	FSMNetworking();
	~FSMNetworking();

	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	
};

#endif //!FSMNETWORKING_H
