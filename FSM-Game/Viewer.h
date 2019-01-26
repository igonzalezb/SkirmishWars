#ifndef VIEWER_H
#define VIEWER


#include "StatesGame.h"

class Viewer
{
public:
	Viewer();	
	~Viewer();	

	void dispatch(genericEvent * ev, usefulInfo *Info);	

	void on_IStart(genericEvent* ev, usefulInfo * Info);
	void on_YouStart(genericEvent* ev, usefulInfo * Info);
	void on_RyouStart(genericEvent* ev, usefulInfo * Info);
	void on_RIStart(genericEvent* ev, usefulInfo * Info);

	void on_Move(genericEvent* ev, usefulInfo * Info);
	void on_Purchase(genericEvent* ev, usefulInfo * Info);
	void on_Attack(genericEvent* ev, usefulInfo * Info);
	void on_Pass(genericEvent* ev, usefulInfo * Info);
	void on_Tile(genericEvent* ev, usefulInfo * Info);
	//on_NewUnit(genericEvent* ev, usefulInfo * Info);
	//void on_BoAttack(genericEvent* ev, usefulInfo * Info);
	//void on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	//on_NoMoney(genericEvent* ev, usefulInfo * Info);

	void on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	void on_TwoHalfMinTimeout(genericEvent* ev, usefulInfo * Info);
	void on_TenSecLeft(genericEvent* ev, usefulInfo * Info);
	void on_ThirtySecLeft(genericEvent* ev, usefulInfo * Info);
	void on_OneSecTimeout(genericEvent* ev, usefulInfo * Info);

	void on_RPass(genericEvent* ev, usefulInfo * Info);
	void on_RMove(genericEvent* ev, usefulInfo * Info);
	void on_RPurchase(genericEvent* ev, usefulInfo * Info);
	void on_RAttack(genericEvent* ev, usefulInfo * Info);
	
	void on_YouWon(genericEvent* ev, usefulInfo * Info);
	void on_RYouWon(genericEvent* ev, usefulInfo * Info);
	void on_PlayAgain(genericEvent* ev, usefulInfo * Info);
	void on_RplayAgain(genericEvent* ev, usefulInfo * Info);
	void on_GameOver(genericEvent* ev, usefulInfo * Info);
	void on_RgameOver(genericEvent* ev, usefulInfo * Info);
	void on_Error_(genericEvent* ev, usefulInfo * Info);
	void on_Rerror_(genericEvent* ev, usefulInfo * Info);
	void on_Quit(genericEvent* ev, usefulInfo * Info);
	void on_Rquit(genericEvent* ev, usefulInfo * Info);


protected:
	
};

#endif //!FSMGAME_H