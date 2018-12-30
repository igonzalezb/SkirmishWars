//CHEQUEAR TODOS LOS ON...

#ifndef STATES_H
#define STATES_H

#define DEBUG true

#include "genericState.h"
//#include "PlayerInfo.h"
//#include "Map.h"

//VER si usar idle
/*
class ST_Idle : public genericState
{
public:
};*/


class ST_GameIdle :public genericState
{
	genericState* on_IStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_YouStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_RYouStart(genericEvent* ev, usefulInfo * Info);
	genericState* on_RIStart(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_Moving :public genericState
{
	genericState* on_Move(genericEvent* ev, usefulInfo * Info);
	genericState* on_Attack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Purchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_LastMove(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_Attacking :public genericState
{
	genericState* on_Attack(genericEvent* ev, usefulInfo * Info);
	genericState* on_Purchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	genericState* on_LastAttack(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_Purchasing :public genericState
{
	genericState* on_Purchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_Pass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

/*
class ST_YouPlay :public genericState
{
	genericState* on_IPlay(genericEvent* ev, usefulInfo * Info); //VER si este queda o no
	//genericState* on_RMove(genericEvent* ev, usefulInfo * Info);
	//genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	//genericState* on_RAttack(genericEvent* ev, usefulInfo * Info); //VER por lo del counter attack!! 
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};
*/

class ST_YouMoving :public genericState
{
	genericState* on_RMove(genericEvent* ev, usefulInfo * Info);
	genericState* on_RAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_LastMove(genericEvent* ev, usefulInfo * Info); //aca creo que esto no va
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_YouAttacking :public genericState
{
	genericState* on_RAttack(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_LastAttack(genericEvent* ev, usefulInfo * Info); //aca creo que esto no va
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};

class ST_YouPurchasing :public genericState
{
	genericState* on_RPurchase(genericEvent* ev, usefulInfo * Info);
	genericState* on_RPass(genericEvent* ev, usefulInfo * Info);
	//genericState* on_Timeout(genericEvent* ev, usefulInfo * Info);
};


#endif // !STATES_H