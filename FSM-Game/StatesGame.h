#ifndef STATESGAME_H
#define STATESGAME_H

#define DEBUG true

#include "genericState.h"
 
class ST_GameIdle :public genericState 
{
	genericState* on_IStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_RyouStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_RIStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_Moving :public genericState //ACA se estaria esperando la coordenada de la unidad que se va a mover
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingDestination :public genericState
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingMoveConfirmation :public genericState //ACA se estaria esperando la coordenada de la unidad que se va a mover
{
	genericState* on_Move(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingBoardingConfirmation :public genericState 
{
	genericState* on_Move(genericEvent* ev, usefulInfo * Info); 
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingUnboardingConfirmation :public genericState
{
	genericState* on_Move(genericEvent* ev, usefulInfo * Info); //se envia paquete move
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingUnboardingLocation :public genericState
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingUnboardingLocationConfirmation :public genericState
{
	genericState* on_Move(genericEvent* ev, usefulInfo * Info); //se envia el segundo paquete move
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
};




class ST_Attacking :public genericState
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingDefender :public genericState
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingAttackConfirmation :public genericState //ACA se estaria esperando la coordenada de la unidad que se va a mover
{
	genericState* on_Attack(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_BoPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_Purchasing :public genericState
{
	genericState* on_NewUnit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_NoMoney(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingLocation :public genericState
{
	genericState* on_Tile(genericEvent* ev, usefulInfo * Info);
	genericState* on_NewUnit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_NoMoney(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_WaitingPurchaseConfirmation :public genericState
{
	genericState* on_Purchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_NoMoney(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_OneMinTimeout(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};


class ST_YouMoving :public genericState
{
	genericState* on_RMove(genericEvent* ev, usefulInfo * Info);
	genericState* on_RAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_YouUnboardingUnit :public genericState
{
	genericState* on_RMove(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_YouAttacking :public genericState
{
	genericState* on_RAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_YouPurchasing :public genericState
{
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};


class ST_AnalysingVictoryHQ :public genericState
{
	genericState* on_YouDidntWin(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_AnalysingVictoryUnits :public genericState
{
	genericState* on_YouDidntWin(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouWon(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

class ST_G_WaitingPlayingAgainConfirmation :public genericState
{
	genericState* on_PlayAgain(genericEvent* ev, usefulInfo * Info);
	genericState* on_GameOver(genericEvent* ev, usefulInfo * Info);
	genericState* on_Quit(genericEvent* ev, usefulInfo * Info);
	genericState* on_Rerror(genericEvent* ev, usefulInfo * Info);
	genericState* on_Error(genericEvent* ev, usefulInfo * Info);
};

////////////////////////////////////////////////

#endif // !STATESGAME_H
