
#include "States.h"
#include "Game.h"
#include "usefulInfo.h"
#include "Events.h"
#include <fstream>
#include <sstream>

/////////////////////////////// ST_GameIdle ///////////////////////////////

genericState* ST_GameIdle::on_IStart(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setMoney(5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			//if (((Info->gameInterface->myMap->getTile(i,j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i,j)->getBuilding()) != NULL))
			if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL)
			{
				Info->gameInterface->myMap->getTile(i,j)->getUnit()->setHp(8); //VER si este HP inicial por default ya esta cargado en algun lado
			}
		}
	}

	//COMPLETAR 
	return ret;
}

genericState* ST_GameIdle::on_YouStart(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setMoney(5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			//if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL))
			if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL)
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
			}
		}
	}
	//COMPLETAR

	return ret;
}

genericState* ST_GameIdle::on_RYouStart(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setMoney(5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			//if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL))
			if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL)
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
			}
		}
	}
	//COMPLETAR

	return ret;
}

genericState* ST_GameIdle::on_RIStart(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setMoney(5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			//if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL))
			if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL)
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
			}
		}
	}
	//COMPLETAR

	return ret;
}


/////////////////////////////// ST_Moving ///////////////////////////////
//creo que onMove ocurriendo en el estado Moving, se borraria (PERO CHEQUEAR)
genericState* ST_Moving::on_Move(genericEvent *ev, usefulInfo * Info) //en un lugar ya estan guardadas las coordenadas origen y destino del movimiento
{
	genericState *ret = (genericState *) new ST_Moving();

	//COMPLETAR 

	return ret;
}

genericState* ST_Moving::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	//HACER: cuando el mouse ve que se toca un tile del mapa,
	//guardar esa info en la clase game en tileSelected y generar el evento TILE
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		genericState *ret = (genericState *) new ST_WaitingDestination();
	}
	else
	{
		genericState *ret = (genericState *) new ST_Moving();
	}
}

genericState* ST_Moving::on_Attack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{																	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();

	//COMPLETAR 

	return ret;
}

genericState* ST_Moving::on_Purchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerMe, newUnit);

	//COMPLETAR 

	return ret;
}

genericState* ST_Moving::on_LastMove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Attacking();

	//COMPLETAR 

	return ret;
}

genericState* ST_Moving::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerYou->setMoney(((Info->gameInterface->playerYou->getAmmountOfCities())+1)*5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL)&&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

/*
genericState* ST_Moving::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();

	//COMPLETAR 

	return ret;
}
*/

/////////////////////////////// ST_WaitingDestination //////////////////////
genericState* ST_WaitingDestination::on_Tile(genericEvent* ev, usefulInfo * Info)
{
	if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
	{
		Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());
		genericState *ret = (genericState *) new ST_Moving();

		if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit()) != NULL) &&
			(((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit())->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			//si el attacker es una unidad mia:
		{
			Info->gameInterface->myMap->possibleMoves((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit()), Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j);
			if ((Info->gameInterface->myMap->canMove[Info->gameInterface->getDefender.i][Info->gameInterface->getDefender.j]) == true)
			{
				Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender.i, Info->gameInterface->getDefender.j)->setUnit(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit());
				Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->setUnit(NULL);
			}
			else {
				//COMPLETAR:ver si se pone algo aca
			}
		}
		//VER si se borra el tile selected
		genericState *ret = (genericState *) new ST_Moving();
	}
	else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
			((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		genericState *ret = (genericState *) new ST_WaitingDestination();
	}
}


genericState* ST_WaitingDestination::on_Attack(genericEvent* ev, usefulInfo * Info)
{

}
	
genericState* ST_WaitingDestination::on_Purchase(genericEvent* ev, usefulInfo * Info)
{

}

genericState* ST_WaitingDestination::on_Pass(genericEvent* ev, usefulInfo * Info)
{

}


/////////////////////////////// ST_Attacking ///////////////////////////////
//si se apretan los tiles, guardar la info en attacker y defender. Cuando se presione el boton ATTACK, recien ahi GENERAR EVENTO ATTACK! (ver donde se hacen estas cosas)
//VER SI ESTO QUEDA, CREO QUE NO
genericState* ST_Attacking::on_Attack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Attacking();

	//DE ACA EN ADELANTE SE VA A BORRAR
	if ((Info->gameInterface->myMap->getAttacker().i != NULL) &&
		(Info->gameInterface->myMap->getAttacker().j != NULL) &&
		(Info->gameInterface->myMap->getDefender().i != NULL) &&
		(Info->gameInterface->myMap->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i),(Info->gameInterface->myMap->getDefender().j)))->getUnit())!=NULL)
		{
			Info->gameInterface->attack();
		}
		else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getBuilding()) != NULL)
		{
			Info->gameInterface->captureProperty(Info->gameInterface->playerMe,Info->gameInterface->playerYou);
		}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)
	//COMPLETAR 

	return ret;
}

genericState* ST_Attacking::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	//HACER: cuando el mouse ve que se toca un tile del mapa,
	//guardar esa info en la clase game en tileSelected y generar el evento TILE
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		genericState *ret = (genericState *) new ST_WaitingDefender();
	}
	else
	{
		genericState *ret = (genericState *) new ST_Attacking();
	}
}

genericState* ST_Attacking::on_Purchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerMe, newUnit);

	//COMPLETAR 

	return ret;
}

genericState* ST_Attacking::on_LastAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();

	if ((Info->gameInterface->myMap->getAttacker().i != NULL) &&
		(Info->gameInterface->myMap->getAttacker().j != NULL) &&
		(Info->gameInterface->myMap->getDefender().i != NULL) &&
		(Info->gameInterface->myMap->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->attack();
		}
		else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getBuilding()) != NULL)
		{
			Info->gameInterface->captureProperty(Info->gameInterface->playerMe, Info->gameInterface->playerYou);
		}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)
	//COMPLETAR 

	return ret;
}

genericState* ST_Attacking::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerYou->setMoney(((Info->gameInterface->playerYou->getAmmountOfCities()) + 1) * 5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

/*
genericState* ST_Attacking::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();

	//COMPLETAR 

	return ret;
}*/

/////////////////////////////// ST_WaitingDefender //////////////////////////
genericState* ST_WaitingDefender::on_Tile(genericEvent* ev, usefulInfo * Info) 
{
	////////////////////////////////////////
	if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL)
	{
		Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());
		genericState *ret = (genericState *) new ST_Moving();

		if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit()) != NULL) &&
			(((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit())->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			//si el attacker es una unidad mia:
		{
			Info->gameInterface->myMap->possibleMoves((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit()), Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j);
			if ((Info->gameInterface->myMap->canMove[Info->gameInterface->getDefender.i][Info->gameInterface->getDefender.j]) == true)
			{
				Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender.i, Info->gameInterface->getDefender.j)->setUnit(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit());
				Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->setUnit(NULL);
			}
			else {
				//COMPLETAR:ver si se pone algo aca
			}
		}
		//VER si se borra el tile selected
		genericState *ret = (genericState *) new ST_Moving();
	}
	else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		genericState *ret = (genericState *) new ST_WaitingDestination();
	}
}

genericState* ST_WaitingDefender::on_Attack(genericEvent* ev, usefulInfo * Info) //ESTO QUEDA????????
{

}

genericState* ST_WaitingDefender::on_Purchase(genericEvent* ev, usefulInfo * Info)
{

}

genericState* ST_WaitingDefender::on_Pass(genericEvent* ev, usefulInfo * Info)
{

}


/////////////////////////////// ST_Purchasing ///////////////////////////////

genericState* ST_Purchasing::on_Purchase(genericEvent *ev, usefulInfo * Info) //VER SI SE PUEDE COMPRAR MAS DE UNA VEZ
{
	genericState *ret = (genericState *) new ST_Purchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerMe, newUnit);

	//COMPLETAR 

	return ret;
}

genericState* ST_Purchasing::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerYou->setMoney(((Info->gameInterface->playerYou->getAmmountOfCities()) + 1) * 5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}


/////////////////////////////// ST_YouMoving ///////////////////////////////

genericState* ST_YouMoving::on_RMove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();


	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit())->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->myMap->possibleMoves((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getDefender.j)->getUnit()), Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j);
		if ((Info->gameInterface->myMap->canMove[Info->gameInterface->getDefender.i][Info->gameInterface->getDefender.j]) == 1)
		{
			Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender.i, Info->gameInterface->getDefender.j)->setUnit(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->getUnit());
			Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker.i, Info->gameInterface->getAttacker.j)->setUnit(NULL);
		}
		else 
		{
			//COMPLETAR: TIRAR ERROR O VER QUE SE HACE
		}
	}


	//COMPLETAR 

	return ret;
}

genericState* ST_YouMoving::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouAttacking();

	//HACER: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->myMap->getAttacker().i != NULL) &&
		(Info->gameInterface->myMap->getAttacker().j != NULL) &&
		(Info->gameInterface->myMap->getDefender().i != NULL) &&
		(Info->gameInterface->myMap->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->attack();
		}
		else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getBuilding()) != NULL)
		{
			Info->gameInterface->captureProperty(Info->gameInterface->playerYou, Info->gameInterface->playerMe);
		}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)

	//COMPLETAR 

	return ret;
}

genericState* ST_YouMoving::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerYou, newUnit);

	//COMPLETAR 

	return ret;
}

/*
genericState* ST_YouMoving::on_LastMove(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Attacking();

	//COMPLETAR 

	return ret;
}*/

genericState* ST_YouMoving::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerMe->setMoney(((Info->gameInterface->playerMe->getAmmountOfCities()) + 1) * 5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

/*
genericState* ST_YouMoving::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_Moving();

//COMPLETAR

return ret;
}
*/


/////////////////////////////// ST_YouAttacking ///////////////////////////////

genericState* ST_YouAttacking::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouAttacking();

	//HACER: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->myMap->getAttacker().i != NULL) &&
		(Info->gameInterface->myMap->getAttacker().j != NULL) &&
		(Info->gameInterface->myMap->getDefender().i != NULL) &&
		(Info->gameInterface->myMap->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->attack();
		}
		else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->myMap->getDefender().i), (Info->gameInterface->myMap->getDefender().j)))->getBuilding()) != NULL)
		{
			Info->gameInterface->captureProperty(Info->gameInterface->playerYou, Info->gameInterface->playerMe);
		}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)

	//COMPLETAR 

	return ret;
}

genericState* ST_YouAttacking::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerYou, newUnit);

	//COMPLETAR 

	return ret;
}

/*
genericState* ST_YouAttacking::on_LastAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	//COMPLETAR 

	return ret;
}
*/
genericState* ST_YouAttacking::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerMe->setMoney(((Info->gameInterface->playerMe->getAmmountOfCities()) + 1) * 5);// se suma 1 porque el HQ tambien aporta $5 al inicio de cada jugada
	
	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
//COMPLETAR 

	return ret;
}

/*
genericState* ST_YouAttacking::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_Moving();

//COMPLETAR

return ret;
}*/


/////////////////////////////// ST_YouPurchasing ///////////////////////////////

genericState* ST_YouPurchasing::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerYou, newUnit);

	//COMPLETAR 

	return ret;
}

genericState* ST_YouPurchasing::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerMe->setMoney(((Info->gameInterface->playerMe->getAmmountOfCities()) + 1) * 5);

	int i = 0, j = 0;
	for (i = 0; i < FILA; i++)
	{
		for (j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) >> 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

/*
genericState* ST_YouPurchasing::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_Moving();

//COMPLETAR

return ret;
}*/
