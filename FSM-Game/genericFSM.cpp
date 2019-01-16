#include "genericFSM.h"
#include "States.h"

genericFSM::genericFSM()
{
	currentState = (genericState *) new ST_WaitingConnection(); //ver que poner
}

genericFSM::~genericFSM()
{
	delete currentState;
}

genericState * genericFSM::getCurrentState()
{
	return currentState;
}

//MOVI LA DEFINICION DE dispatch A LAS HIJAS