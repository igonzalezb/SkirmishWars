
#include "StatesGame.h"
#include "Game.h"
#include "usefulInfo.h"
#include "Events.h"
#include <fstream>
#include <sstream>

/////////////////////////////// ST_GameIdle ///////////////////////////////

genericState* ST_GameIdle::on_IStart(genericEvent *ev, usefulInfo * Info)
{
	cout << "GAME IDLE: ON I START" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->setIamPlaying(true);
	return ret;
}

genericState* ST_GameIdle::on_YouStart(genericEvent *ev, usefulInfo * Info)
{
	cout << "GAME IDLE: ON you START" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	return ret;
}

genericState* ST_GameIdle::on_RyouStart(genericEvent *ev, usefulInfo * Info)
{
	cout << "GAME IDLE: ON R you START" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->setIamPlaying(true);

	return ret;
}

genericState* ST_GameIdle::on_RIStart(genericEvent *ev, usefulInfo * Info)
{
	cout << "GAME IDLE: ON R ISTART" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	return ret;
}


/////////////////////////////// ST_Moving ///////////////////////////////

genericState* ST_Moving::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	cout << "G MOVING: ON TILE" << endl;
	genericState *ret;
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		Info->gameInterface->moving = false;
		ret = (genericState *) new ST_WaitingDestination();
		cout << "ENTRO AL IF DEL ON_TILE" << endl;
	}
	else
	{
		ret = (genericState *) new ST_Moving();
		Info->gameInterface->moving = false;
		cout << "ENTRO AL else DEL ON_TILE (no apretre ninguna unit)" << endl;
	}
	return ret;
}

genericState* ST_Moving::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{	
	cout << "G MOVING: ATTACK" << endl;
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();

	return ret;
}

genericState* ST_Moving::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
	cout << "G MOVING: ON PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();

	return ret;
}


genericState* ST_Moving::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G MOVING: ON PASS" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->playerYou->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerYou->setMoney(((Info->gameInterface->playerYou->getAmmountOfCities())+1)*5);

	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getBuilding()->getTeam())==Info->gameInterface->playerYou->getTeam())&&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}



			//CAPPPPPPPPPPPPPPPPPPPPPPPPTURAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA DE PROOOOOOOOOOOOOPIEDAD
			// antes de llamar a esta funcion debo setear el attacker con la unidad que este encima de un building que no es propio
			//if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
			//	(((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("infantry")) == 0) || 
			//	((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("mech")) == 0)) &&
			//	((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())) &&
			//	(Info->gameInterface->myMap->getTile(i, j)->getBuilding()->getTeam() != (Info->gameInterface->playerMe->getTeam())))
			//{
			//		Info->gameInterface->setAttacker(i, j);
			//		Info->gameInterface->captureProperty(Info->gameInterface->playerMe);
			//		if ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()->getCp()) <= 0)
			//		{
			//			cout << "SE CAPTURO POR COMPLETO!!!!(I=" << i << "; J=" << j << ")" << endl;
			//			cout << "CP DEL BUILDING=" << Info->gameInterface->myMap->getTile(i, j)->getBuilding()->getCp() << endl;
			//			//en el tile donde estaba antes el building del oponente, poner el mismo building pero de mi equipo.
			//			Info->gameInterface->myMap->getTile(i, j)->getBuilding()->setTeam(Info->gameInterface->playerMe->getTeam());
			//		}
			//		cout << "CAPTURE PERO NO DEL TODO EN (I=" << i << ";J=" << j << ")" << endl;
			//		cout << "CP DEL BUILDING=" << Info->gameInterface->myMap->getTile(i, j)->getBuilding()->getCp() << endl;
			//}

		}
	}
	//ACA HAY QUE AGREGAR LA CAPTURA DE PROPIEDADES
	return ret;
}

////////////////////////////////////////
genericState* ST_WaitingMoveConfirmation::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING MOVE CONFIRMATION: ON MOVE" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->move();
	return ret;
}

///////////////////////////////////////
/////////////////////////////////////

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
	cout << "G WaitingDestination::on_Tile" << endl;
	genericState *ret;
	if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
	{
		Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());
		Info->gameInterface->myMap->possibleMoves((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()), Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j);
		if ((Info->gameInterface->myMap->canMove[Info->gameInterface->getDefender().i][Info->gameInterface->getDefender().j]))
		{
			//cout << "ENTRA AL IF 1" << endl;
			Info->gameInterface->moving = true;
			ret = (genericState *) new ST_WaitingMoveConfirmation();
		}
		else
		{
			ret = (genericState *) new ST_WaitingDestination();
			Info->gameInterface->moving = false;
		}
	}
	else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
			((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		ret = (genericState *) new ST_WaitingDestination();
		Info->gameInterface->moving = false;
	}
	else
	{
		ret = (genericState *) new ST_WaitingDestination();
		Info->gameInterface->moving = false;
	}
	
	cout << "Saliendo..." << endl;
	return ret;
}


genericState* ST_WaitingDestination::on_BoAttack(genericEvent* ev, usefulInfo * Info)
{
	cout << "G WaitingDestination::on_Attack" << endl;
	genericState *ret = (genericState *) new ST_Attacking();

	//COMPLETAR 

	return ret;
}
	
genericState* ST_WaitingDestination::on_BoPurchase(genericEvent* ev, usefulInfo * Info)
{
	cout << "G WaitingDestination::on_Purchase" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();

	//COMPLETAR 

	return ret;
}

genericState* ST_WaitingDestination::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "G WaitingDestination::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();

	//COMPLETAR 

	return ret;
}

/////////////////////////////// ST_Attacking ///////////////////////////////
//si se apretan los tiles, guardar la info en attacker y defender. Cuando se presione el boton ATTACK, recien ahi GENERAR EVENTO ATTACK! (ver donde se hacen estas cosas)

genericState* ST_Attacking::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	cout << "G Attacking::on_Tile" << endl;
	genericState *ret;
	//HACER: cuando el mouse ve que se toca un tile del mapa,
	//guardar esa info en la clase game en tileSelected y generar el evento TILE
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		ret = (genericState *) new ST_WaitingDefender();
		Info->gameInterface->attacking = false;
	}
	else
	{
		ret = (genericState *) new ST_Attacking();
		Info->gameInterface->attacking = false;
	}
	return ret;
}

genericState* ST_Attacking::on_BoPurchase(genericEvent *ev, usefulInfo * Info)
{
	cout << "G Attacking::on_Purchase" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();

	/*
	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
	Info->gameInterface->purchase(Info->gameInterface->playerMe, newUnit);
	*/

	//COMPLETAR 

	return ret;
}

genericState* ST_Attacking::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "G Attacking::on_Pass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
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
	cout << "G aitingDefender::on_Tile" << endl;
	genericState *ret;
	
	if ((((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))) //||
		//(((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getBuilding()) != NULL) &&
		//((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getBuilding()->getTeam()) != (Info->gameInterface->playerMe->getTeam()))))
	{ //si es una unit del equipo contrario:
		Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());
		ret = (genericState *) new ST_WaitingAttackConfirmation();
		Info->gameInterface->attacking = true;
		cout << "PONE ATTACKING EN TRUE" << endl;
		//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)
	}
	else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam())==(Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		ret = (genericState *) new ST_WaitingDefender();
		Info->gameInterface->attacking = false;
		cout << "PONE ATTACKING EN FALSE. IF ELSE" << endl;
	}
	else
	{
		ret = (genericState *) new ST_WaitingDefender();
		Info->gameInterface->attacking = false;
		cout << "PONE ATTACKING EN FALSE.  ELSE" << endl;

	}
	return ret;
}

genericState* ST_WaitingDefender::on_BoPurchase(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();

	//COMPLETAR 

	return ret;
}

genericState* ST_WaitingDefender::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "ST_WaitingDefender::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();

	//COMPLETAR 

	return ret;
}

/////////////////////////////// ST_WaitingAttackConfirmation ///////////////////////////////
genericState* ST_WaitingAttackConfirmation::on_Attack(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_WaitingAttackConfirmation::on_Attack" << endl;
	genericState *ret = (genericState *) new ST_Attacking();

	if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
	{
		Info->gameInterface->setDie(rand() % 6 + 1); //VERIFICAR si esto tira un valor random entre 1 y 6.
		Info->gameInterface->attack();
	}
	//else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getBuilding()) != NULL)
	//{
	//	Info->gameInterface->captureProperty(Info->gameInterface->playerMe, Info->gameInterface->playerYou);
	//}

	return ret;
}

/////////////////////////////// ST_WaitingPurchaseConfirmation ///////////////////////////////
genericState* ST_WaitingPurchaseConfirmation::on_Purchase(genericEvent *ev, usefulInfo * Info)
{
	cout << "waiting purchase confirmation: on purchase" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	Info->gameInterface->purchase(Info->gameInterface->playerMe);
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_NoMoney(genericEvent *ev, usefulInfo * Info)
{
	cout << "G waiting purchase confirm::on_NoMoney" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}


genericState* ST_WaitingPurchaseConfirmation::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "G waiting purchase confirm::on_Pass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

/////////////////////////////// ST_Purchasing ///////////////////////////////
//PURCHASING::ON PURCHASE PROBABLEMENTE DESAPAREZCA!!!!!!!
//genericState* ST_Purchasing::on_Purchase(genericEvent *ev, usefulInfo * Info) //VER SI SE PUEDE COMPRAR MAS DE UNA VEZ
//{
//	genericState *ret = (genericState *) new ST_Purchasing();
//
//	string newUnit;//HACER: VER SI QUEDA COMO STRING O QUE, Y VER DONDE SE COMPLETA QUIEN ES ESA NEW UNIT!!!!!!!!!!!!!!!!!
//	Info->gameInterface->purchase(Info->gameInterface->playerMe, newUnit);
//
//	//COMPLETAR 
//
//	return ret;
//}



genericState* ST_Purchasing::on_NewUnit(genericEvent *ev, usefulInfo * Info) //VER SI SE PUEDE COMPRAR MAS DE UNA VEZ
{
	genericState *ret;

	cout << " G Purhcasing: on new unit" << endl;
	if ((stoi(Info->gameInterface->getNewUnit()->getCost()))<=(Info->gameInterface->playerMe->getMoney()))
	{//Si alcanza la plata para comprar esa unidad, cambio de estado
		ret = (genericState *) new ST_WaitingLocation();
		Info->gameInterface->purchasing = false;
	}
	else
	{//Si no alcanza la plata para comprar esa unidad, espera que se elija una nueva unidad.
		ret = (genericState *) new ST_Purchasing();
		Info->gameInterface->purchasing = false;
	}

	//COMPLETAR 

	return ret;
}

genericState* ST_Purchasing::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_Purchasing::on_Pass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

genericState* ST_Purchasing::on_NoMoney(genericEvent *ev, usefulInfo * Info)
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 
	return ret;
}

/////////////////////////////// ST_WaitingLocation ///////////////////////////////

genericState* ST_WaitingLocation::on_Tile(genericEvent* ev, usefulInfo * Info)
{
	cout << "ST_WaitingLocation::on_Tile" << endl;
	genericState *ret;
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getBuilding())!=NULL)&&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getBuilding()->getType()).compare("m"))==0)&&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getBuilding()->getTeam()) == (Info->gameInterface->playerMe->getTeam()))&&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL))
	{
		Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());
		ret = (genericState *) new ST_WaitingPurchaseConfirmation();
		Info->gameInterface->purchasing = true;
	}
	else
	{//Si el tile presionado es uno invalido para meterle una nueva unit, quedarse en este estado
		ret = (genericState *) new ST_WaitingLocation();
		Info->gameInterface->purchasing = false;
	}
	return ret;
}

genericState* ST_WaitingLocation::on_NewUnit(genericEvent* ev, usefulInfo * Info)
{
	cout << "waiting location: on new unit" << endl;
	genericState *ret;

	if ((stoi(Info->gameInterface->getNewUnit()->getCost())) <= (Info->gameInterface->playerMe->getMoney()))
	{//Si alcanza la plata para comprar esa unidad, cambio de estado
		ret = (genericState *) new ST_WaitingLocation();
	}
	else
	{//Si no alcanza la plata para comprar esa unidad, espera que se elija una nueva unidad.
		ret = (genericState *) new ST_Purchasing();
	}
	return ret;
}

genericState* ST_WaitingLocation::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "ST_WaitingLocation::on_Pass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}
		}
	}
	//COMPLETAR 

	return ret;
}

genericState* ST_WaitingLocation::on_NoMoney(genericEvent* ev, usefulInfo * Info)
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
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
genericState* ST_WaitingLocation::on_Timeout(genericEvent *ev, usefulInfo * Info)
{
genericState *ret = (genericState *) new ST_Moving();

//COMPLETAR

return ret;
}
*/

/////////////////////////////// ST_YouMoving ///////////////////////////////

genericState* ST_YouMoving::on_RMove(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_YouMoving:: on_RMOVE" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();

	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit())->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
	{
		//ACA SE ROMPE:
		//Info->gameInterface->myMap->possibleMoves((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getDefender().j)->getUnit()), Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j);
		if (1)//(Info->gameInterface->myMap->canMove[Info->gameInterface->getDefender().i][Info->gameInterface->getDefender().j]) == true)
		{
			Info->gameInterface->move();
		}
		else 
		{
			//COMPLETAR: TIRAR ERROR O VER QUE SE HACE (QUIZAS NO SE HACE NADA)
		}
	}

	//COMPLETAR 
	return ret;
}

genericState* ST_YouMoving::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouAttacking();

	//HACER: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->getAttacker().i != NULL) &&
		(Info->gameInterface->getAttacker().j != NULL) &&
		(Info->gameInterface->getDefender().i != NULL) &&
		(Info->gameInterface->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->attack();
		}
		//else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getBuilding()) != NULL)
		//{
		//	Info->gameInterface->captureProperty(Info->gameInterface->playerYou, Info->gameInterface->playerMe);
		//}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)

	//COMPLETAR 

	return ret;
}

genericState* ST_YouMoving::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	cout << "CORDENADAS DEL DEFENDER (PURCHASE):    (i=" << Info->gameInterface->getDefender().i << "  ; j=  " << Info->gameInterface->getDefender().j << "   )" << endl;
	cout << "BUILDING DEL DEFENDER (PURCHASE):   "<<Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getName() << endl;
	//ESTE IF PASARLO AL GENERADOR DE EVENTOS PROVENIENTES DE LA FSM DE NETWORKING,CUANDO SE RECIBE PAQUETE DE PURCHASE!!!!!!!!!!!!!!!!!!!!!!!!
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getType()).compare("m")) == 0) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getTeam()) == (Info->gameInterface->playerYou->getTeam()))&&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()) == NULL)&&
		((stoi(Info->gameInterface->getNewUnit()->getCost()))<=(Info->gameInterface->playerYou->getMoney())))
	{
		//EL DEFENDER YA ESTA SETEADO cuando se recibe el mensaje de networking
		Info->gameInterface->purchase(Info->gameInterface->playerYou);	//SI SACAMOS EL IF PARA LA PARTE DEL GENERADOR DE EVENTOS, QUEDARIA ACA SOLO ESTA LINEA

	}

	//COMPLETAR 

	return ret;
}

genericState* ST_YouMoving::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	cout << "entra a on_RPass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
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

	//HACER EN IS THERE EVENT DE NETWORKING: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->getAttacker().i != NULL) &&
		(Info->gameInterface->getAttacker().j != NULL) &&
		(Info->gameInterface->getDefender().i != NULL) &&
		(Info->gameInterface->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->attack();
		}
		//else if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getBuilding()) != NULL)
		//{
		//	Info->gameInterface->captureProperty(Info->gameInterface->playerYou, Info->gameInterface->playerMe);
		//}
	}
	//ver donde iria el COUNTER-ATTACK (ver si se agrega un estado o algo)

	//COMPLETAR 

	return ret;
}

genericState* ST_YouAttacking::on_RPurchase(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouPurchasing();

	cout << "CORDENADAS DEL DEFENDER (PURCHASE):    (i=" << Info->gameInterface->getDefender().i << "  ; j=  " << Info->gameInterface->getDefender().j << "   )" << endl;
	cout << "BUILDING DEL DEFENDER (PURCHASE):   " << Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getName() << endl;
	//ESTE IF PASARLO AL GENERADOR DE EVENTOS PROVENIENTES DE LA FSM DE NETWORKING,CUANDO SE RECIBE PAQUETE DE PURCHASE!!!!!!!!!!!!!!!!!!!!!!!!
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getType()).compare("m")) == 0) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getTeam()) == (Info->gameInterface->playerYou->getTeam())) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()) == NULL) &&
		((stoi(Info->gameInterface->getNewUnit()->getCost())) <= (Info->gameInterface->playerYou->getMoney())))
	{
		//EL DEFENDER YA ESTA SETEADO cuando se recibe el mensaje de networking
		Info->gameInterface->purchase(Info->gameInterface->playerYou);	//SI SACAMOS EL IF PARA LA PARTE DEL GENERADOR DE EVENTOS, QUEDARIA ACA SOLO ESTA LINEA

	}

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
	cout << "ST_YouAttacking::on_RPass" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->playerMe->setAmmountOfCities(Info->gameInterface->myMap);
	Info->gameInterface->playerMe->setMoney(((Info->gameInterface->playerMe->getAmmountOfCities()) + 1) * 5);// se suma 1 porque el HQ tambien aporta $5 al inicio de cada jugada
	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			if (((Info->gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((Info->gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
			{
				Info->gameInterface->myMap->getTile(i, j)->getUnit()->setHp((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
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

	cout << "ST_YouPurchasing::on_RPurchase" << endl;
	genericState *ret = (genericState *) new ST_YouPurchasing();


	
	
	
	
	cout << "CORDENADAS DEL DEFENDER (PURCHASE):    (i=" << Info->gameInterface->getDefender().i << "  ; j=  " << Info->gameInterface->getDefender().j << "   )" << endl;
	cout << "BUILDING DEL DEFENDER (PURCHASE):   "<<Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getName() << endl;
	//ESTE IF PASARLO AL GENERADOR DE EVENTOS PROVENIENTES DE LA FSM DE NETWORKING,CUANDO SE RECIBE PAQUETE DE PURCHASE!!!!!!!!!!!!!!!!!!!!!!!!
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getType()).compare("m")) == 0) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getBuilding()->getTeam()) == (Info->gameInterface->playerYou->getTeam()))&&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()) == NULL)&&
		((stoi(Info->gameInterface->getNewUnit()->getCost()))<=(Info->gameInterface->playerYou->getMoney())))
	{
		//EL DEFENDER YA ESTA SETEADO cuando se recibe el mensaje de networking
		Info->gameInterface->purchase(Info->gameInterface->playerYou);	//SI SACAMOS EL IF PARA LA PARTE DEL GENERADOR DE EVENTOS, QUEDARIA ACA SOLO ESTA LINEA

	}

	
	


	//Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->setUnit(Info->gameInterface->getNewUnit());
	//Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->setTeam(Info->gameInterface->playerYou->getTeam());
	//Info->gameInterface->playerYou->setMoney((Info->gameInterface->playerYou->getMoney())-(stoi(Info->gameInterface->getNewUnit()->getCost())));
	//cout << "plata restante del oponente: " << Info->gameInterface->playerYou->getMoney() << endl;
	////COMPLETAR 

	return ret;
}

genericState* ST_YouPurchasing::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_YouPurchasing::on_RPass" << endl;
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
				if ((Info->gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
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
