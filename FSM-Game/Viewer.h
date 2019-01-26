#ifndef VIEWER_H
#define VIEWER

//#include "genericFSM.h"
#include "StatesGame.h"

//class FSMGame :public genericFSM 
//{
//public:
//	FSMGame() :genericFSM() {};
//	~FSMGame();
//	genericState * getCurrentState();
//	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido	
//};

class Viewer
{
public:
	Viewer();	//Crea un estado al que apunta currentState
	~Viewer();	//Destruye el estado al que apunta currentState

	void dispatch(genericEvent * ev, usefulInfo *Info);	//llama a la funcion del estado al que apunta current state que repsonde al evento recibido
	//genericState * getCurrentState();

	void on_IStart(genericEvent* ev, usefulInfo * Info);
	void on_YouStart(genericEvent* ev, usefulInfo * Info);
	void on_RyouStart(genericEvent* ev, usefulInfo * Info);
	void on_RIStart(genericEvent* ev, usefulInfo * Info);
	void on_TenSecLeft(genericEvent* ev, usefulInfo * Info);
	void on_ThirtySecLeft(genericEvent* ev, usefulInfo * Info);

	void on_Move(genericEvent* ev, usefulInfo * Info);
	void on_Purchase(genericEvent* ev, usefulInfo * Info);
	void on_Attack(genericEvent* ev, usefulInfo * Info);
	void on_Pass(genericEvent* ev, usefulInfo * Info);
	void on_Tile(genericEvent* ev, usefulInfo * Info);
	//on_NewUnit(genericEvent* ev, usefulInfo * Info);
	//on_BoAttack(genericEvent* ev, usefulInfo * Info);
	//on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	//on_NoMoney(genericEvent* ev, usefulInfo * Info);

	void on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	//on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
	void on_TenSecLeft(genericEvent* ev, usefulInfo * Info);
	void on_ThirtySecLeft(genericEvent* ev, usefulInfo * Info);


	void on_RPass(genericEvent* ev, usefulInfo * Info);
	void on_RMove(genericEvent* ev, usefulInfo * Info);
	void on_RPurchase(genericEvent* ev, usefulInfo * Info);
	void on_RAttack(genericEvent* ev, usefulInfo * Info);
	void on_RYouWon(genericEvent* ev, usefulInfo * Info);

	void von_RplayAgain(genericEvent* ev, usefulInfo * Info);
	void on_RgameOver(genericEvent* ev, usefulInfo * Info);

	void on_Rerror_(genericEvent* ev, usefulInfo * Info);
	void on_Rquit(genericEvent* ev, usefulInfo * Info);


protected:
	//genericState * currentState;	//se usa para apuntar a los estados, que son objetos de una clase que hereda la clase genericState
};

#endif //!FSMGAME_H