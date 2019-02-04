
#include "StatesGame.h"
#include "Game.h"
#include "usefulInfo.h"
#include "Events.h"
#include <fstream>
#include <sstream>

void setCaptureProperty(Player* player, Game* gameInterface);

/////////////////////////////// ST_GameIdle ///////////////////////////////
genericState* ST_GameIdle::on_IStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "GAME IDLE: ON I START" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->setIamPlaying(true);
	Info->timeoutSrc->startTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->playerMe->setMoney(5);
	Info->gameInterface->playerYou->setMoney(0);
	return ret;
}

genericState* ST_GameIdle::on_YouStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "GAME IDLE: ON you START" << endl;
#endif // DEBUG
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->playerYou->setMoney(5);
	Info->gameInterface->playerMe->setMoney(0);
	return ret;
}

genericState* ST_GameIdle::on_RyouStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "GAME IDLE: ON R you START" << endl;
#endif // DEBUG	
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->setIamPlaying(true);
	Info->timeoutSrc->startTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->playerMe->setMoney(5);
	Info->gameInterface->playerYou->setMoney(0);
	return ret;
}

genericState* ST_GameIdle::on_RIStart(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "GAME IDLE: ON R ISTART" << endl;
#endif // DEBUG	
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->playerYou->setMoney(5);
	Info->gameInterface->playerMe->setMoney(0);
	return ret;
}

genericState* ST_GameIdle::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_GameIdle::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_GameIdle::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}


/////////////////////////////// ST_Moving ///////////////////////////////
genericState* ST_Moving::on_Tile(genericEvent *ev, usefulInfo * Info)
{
#ifdef DEBUG
	cout << "G MOVING: ON TILE" << endl;
#endif // DEBUG
	genericState *ret;
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getTeam()) == (Info->gameInterface->playerMe->getTeam())))
	{
		Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
		//VER si hay que borrar tileSelected (?)
		Info->gameInterface->moving = false;
		ret = (genericState *) new ST_WaitingDestination();
#ifdef DEBUG
		cout << "ENTRO AL IF DEL ON_TILE" << endl;
#endif // DEBUG

		
	}
	else
	{
		ret = (genericState *) new ST_Moving();
		Info->gameInterface->moving = false;
#ifdef DEBUG
		cout << "ENTRO AL else DEL ON_TILE (no apretre ninguna unit)" << endl;
#endif // DEBUG

		
	}
	return ret;
}

genericState* ST_Moving::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{	
#ifdef DEBUG
	cout << "G MOVING: ATTACK" << endl;
#endif // DEBUG	
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_Moving::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
#ifdef DEBUG
	cout << "G MOVING: ON PURCHASE" << endl;
#endif // DEBUG	
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}


genericState* ST_Moving::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
#ifdef DEBUG
	cout << "G MOVING: ON PASS" << endl;
#endif // DEBUG	
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Moving::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
#ifdef DEBUG
	cout << "G MOVING: ON 1 MIN TIMEOUT" << endl;
#endif // DEBUG	
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Moving::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	cout << "pongo end playing true" << endl;
	Info->gameInterface->setEndPlaying(true);
	return ret;
}

genericState* ST_Moving::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_Moving::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

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
		////////////////////////////////////////// VIEJO, SIN APC ////////////////////////////////////////// !!!!!!!!!!!!!!!!!!!!!!

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "DEFENDER:ES UNA UNIDAD Y ES PROPIA" << endl;
		cout << "UNIDAD ATACANTE:" << Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType() << endl;
		cout << "UNIDAD DEFENDER:" << Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType() << endl;


		////////////////////////////////////////// nuevo con apc /////////////////////////////////////
		if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap1")==0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap2")==0)) &&
			((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("ap1") == 0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("ap2") == 0)) &&
				(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j) == Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)) &&
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->arregloNaveAPCisEmpty() == false))
			//habilita el desembarco de unidad
		{
			cout << "ATTACKER Y DEFENDER  APC... ENTRA AL IF" << endl;
			Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());//se setea el defender en APC 
			//tanto el defender como el attacker son APC!!!
			ret = (genericState *) new ST_WaitingUnboardingConfirmation;
			Info->gameInterface->unboardingAPC = true;//ver por las dudas!!!!!!!!!!
		}
		else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("in1") == 0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("in2") == 0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("me1") == 0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("me2") == 0)) &&
			((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap1")==0) ||
			(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap2")==0)) &&
				(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->arregloNaveAPChavePlace() == true))
			//habilito la carga de unidad al apc
		{

			cout << "HAY LUGAR EN EL ARREGLO   " << endl;;
			cout << "ATTACKER ES UN IN O ME Y DEFENDER ES UN APC... ENTRA AL ELSE IF" << endl;
			//movimiento in o me a acp -> abordar acp
			Info->gameInterface->setDefender(Info->gameInterface->getTileSelected());


			//meter los casos arr ab izq der...
			if (Info->gameInterface->getDefender().i == 0) //ARRIBA
			{
				cout << "ARRIBA ";
				if (Info->gameInterface->getDefender().j == 0) //arriba a la izq
				{
					cout << "A LA IZQ   ";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j + 1)))
					{
							cout << "CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;
					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}
				else if (Info->gameInterface->getDefender().j == (COLUMNA - 1)) //arriba a la derecha
				{
					cout << "A LA DER   ";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j - 1)))
					{

							cout << "CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;
					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}

				}
				else //arriba en el medio
				{
					cout << "EN EL MEDIO";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j - 1)) ||
							((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j + 1)))
					{

							cout << "CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;

					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}
			}//////
			else if ((Info->gameInterface->getDefender().i) == (FILA - 1)) //ABAJO
			{
				cout << "ABAJO   ";
				if (Info->gameInterface->getDefender().j == 0) //abajo a la izq
				{
					cout << "A LA IZQ";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j + 1)))
					{

							cout << " CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;

					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}//////////////
				else if ((Info->gameInterface->getDefender().j) == (COLUMNA - 1)) //abajo a la derecha
				{
					cout << "A LA DER";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j - 1)))
					{

							cout << " CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;
					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}
				else //abajo en el medio
				{///////////////////
					cout << "EN EL MEDIO";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j - 1)) ||
							((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j + 1)))
					{

							cout << " CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;
					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}
			}
			else //NI ARRIBA NI ABAJO
			{//////////////////
				cout << "NI ARRIBA NI ABAJO  ";
				if (Info->gameInterface->getDefender().j == 0) //a la izq
				{
					cout << "  ->  A LA IZQ";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
							Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
							((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j + 1)))
					{

							cout << "CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;

					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}////////////
				else if ((Info->gameInterface->getDefender().j) == (COLUMNA - 1)) //a la der
				{
					cout << "->A LA DER";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
						((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
							Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j) ||
							((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j - 1)))
					{
						
							cout << " CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;

					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}//////////////
				else //ni arriba ni abajo ni a la izq ni a la der
				{
					cout << "NI ARR NI AB NI IZQ NI DER   ";
					if (((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) + 1)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j)) ||
						((Info->gameInterface->getAttacker().i == ((Info->gameInterface->getDefender().i) - 1)) &&
						(Info->gameInterface->getAttacker().j == Info->gameInterface->getDefender().j)) ||
							((Info->gameInterface->getAttacker().i == Info->gameInterface->getDefender().i) &&
						(Info->gameInterface->getAttacker().j == ((Info->gameInterface->getDefender().j + 1)))) ||
								((Info->gameInterface->getAttacker().i == (Info->gameInterface->getDefender().i)) &&
						(Info->gameInterface->getAttacker().j == (Info->gameInterface->getDefender().j - 1))))
					{

							cout << " CUMPLE COND" << endl;
							Info->gameInterface->boardingAPC = true;
							ret = (genericState *) new ST_WaitingBoardingConfirmation;
							Info->gameInterface->moving = false;
					}
					else
					{
						cout << "NO CUMPLE COND 2" << endl;
						Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
						ret = (genericState *) new ST_WaitingDestination();
						Info->gameInterface->moving = false;
					}
				}
			}

			//casos en los q se cumple la cond
			/*Info->gameInterface->boardingAPC = true;
			ret = (genericState *) new ST_WaitingBoardingConfirmation;
			Info->gameInterface->moving = false;*/
		}
		/////////////////////////////////////////////////// /n/ue/vo //hasta aca
		else
		{
			//casos en los q no se cumple la cond
			Info->gameInterface->setAttacker(Info->gameInterface->getTileSelected());
			//VER si hay que borrar tileSelected (?)
			ret = (genericState *) new ST_WaitingDestination();
			Info->gameInterface->moving = false;
		}
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
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingDestination::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING DESTINATION: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingDestination::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingDestination::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingDestination::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingBoardingConfirmation::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING boarding CONFIRMATION: ON MOVE" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->boardUnit();
	Info->timeoutSrc->startTimer1();
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) 
{
	cout << "G WAITING boarding congirm: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{
	cout << "G MOVING: ATTACK" << endl;
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_WaitingBoardingConfirmation::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
	cout << "G MOVING: ON PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}


genericState* ST_WaitingBoardingConfirmation::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G MOVING: ON PASS" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}
/////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingUnboardingConfirmation::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING boarding CONFIRMATION: ON waiting unboarding location" << endl;
	genericState *ret = (genericState *) new ST_WaitingUnboardingLocation();
	//Info->timeoutSrc->startTimer1();
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{
	cout << "G MOVING: ATTACK" << endl;
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
	cout << "G MOVING: ON PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}


genericState* ST_WaitingUnboardingConfirmation::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G MOVING: ON PASS" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) 
{
	cout << "G WAITING unboarding confirm: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingUnboardingConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}


//////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingUnboardingLocation::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	cout << "on ST_WaitingUnboardingLocation::on_Tile" << endl;
	genericState *ret;

	//if (((Info->gameInterface->getTileSelected().i > 0)&& //HACER ANALISIS PARA CADA CASO DE LOS CUATRO, POR SEPARADO!!!!!!!!!!
	
	if (Info->gameInterface->getAttacker().i == 0) //ARRIBA
	{
		cout << "ARRIBA ";
		if (Info->gameInterface->getAttacker().j == 0) //arriba a la izq
		{
			cout << "A LA IZQ   ";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j + 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << "CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}

			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
		else if (Info->gameInterface->getAttacker().j == (COLUMNA - 1)) //arriba a la derecha
		{
			cout << "A LA DER   ";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j - 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << "CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}

		}
		else //arriba en el medio
		{
			cout << "EN EL MEDIO";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j - 1))||
					((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j + 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << "CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
	}
	else if ((Info->gameInterface->getAttacker().i) == (FILA-1)) //ABAJO
	{
		cout << "ABAJO   ";
		if (Info->gameInterface->getAttacker().j == 0) //abajo a la izq
		{
			cout << "A LA IZQ";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j + 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << " CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
		else if ((Info->gameInterface->getAttacker().j) == (COLUMNA - 1)) //abajo a la derecha
		{
			cout << "A LA DER";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j - 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << " CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
		else //abajo en el medio
		{
			cout << "EN EL MEDIO";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j - 1))||
				((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j + 1)))
			{
					if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
					{
						cout << " CUMPLE COND" << endl;
						Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
						ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
						Info->gameInterface->unboardingAPC = true;
					}
					else
					{
						cout << "NO CUMPLE COND" << endl;
						Info->gameInterface->unboardingAPC = false;
						ret = (genericState *) new ST_WaitingUnboardingLocation();
					}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
	}
	else //NI ARRIBA NI ABAJO
	{
		cout << "NI ARRIBA NI ABAJO  ";
		if (Info->gameInterface->getAttacker().j == 0) //a la izq
		{
			cout << "  ->  A LA IZQ";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
					Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j)||
					((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j + 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << "CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
		else if ((Info->gameInterface->getAttacker().j) == (COLUMNA - 1)) //a la der
		{
			cout << "->A LA DER";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
				Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
				((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
					Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j) ||
					((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j - 1)))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << " CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
		else //ni arriba ni abajo ni a la izq ni a la der
		{
			cout << "NI ARR NI AB NI IZQ NI DER   ";
			if (((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) + 1)) &&
				(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j)) ||
				((Info->gameInterface->getTileSelected().i == ((Info->gameInterface->getAttacker().i) - 1)) &&
					(Info->gameInterface->getTileSelected().j == Info->gameInterface->getAttacker().j)) ||
					((Info->gameInterface->getTileSelected().i == Info->gameInterface->getAttacker().i) &&
				(Info->gameInterface->getTileSelected().j == ((Info->gameInterface->getAttacker().j + 1)))) ||
						((Info->gameInterface->getTileSelected().i == (Info->gameInterface->getAttacker().i)) &&
				(Info->gameInterface->getTileSelected().j == (Info->gameInterface->getAttacker().j - 1))))
			{
				if ((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) == NULL)
				{
					cout << " CUMPLE COND" << endl;
					Info->gameInterface->setDefender(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j);
					ret = (genericState *) new ST_WaitingUnboardingLocationConfirmation();
					Info->gameInterface->unboardingAPC = true;
				}
				else
				{
					cout << "NO CUMPLE COND 1" << endl;
					Info->gameInterface->unboardingAPC = false;
					ret = (genericState *) new ST_WaitingUnboardingLocation();
				}
			}
			else
			{
				cout << "NO CUMPLE COND 2" << endl;
				Info->gameInterface->unboardingAPC = false;
				ret = (genericState *) new ST_WaitingUnboardingLocation();
			}
		}
	}
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{
	cout << "G MOVING: ATTACK" << endl;
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
	cout << "G MOVING: ON PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}


genericState* ST_WaitingUnboardingLocation::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G MOVING: ON PASS" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING unboarding location: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingUnboardingLocation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
genericState* ST_WaitingUnboardingLocationConfirmation::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING UNboarding CONFIRMATION: ON MOVE" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->unboardUnit();
	Info->timeoutSrc->startTimer1();
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_BoAttack(genericEvent *ev, usefulInfo * Info)//Se entra aca al presionar boton ATTACK en pantalla. Todavia no se hizo el ataque.
{
	cout << "G MOVING: ATTACK" << endl;
	//El ataque se hace despues, una vez que ya se entro a este estado por primera vez.
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_BoPurchase(genericEvent *ev, usefulInfo * Info) //VER
{
	cout << "G MOVING: ON PURCHASE" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}


genericState* ST_WaitingUnboardingLocationConfirmation::on_Pass(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G MOVING: ON PASS" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) 
{
	cout << "G WAITING unboarding location confirm: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingUnboardingLocationConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////// ST_WaitingMoveConfirmation ///////////////////////////////
genericState* ST_WaitingMoveConfirmation::on_Move(genericEvent *ev, usefulInfo * Info)
{
	cout << "G WAITING MOVE CONFIRMATION: ON MOVE" << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->move();
	Info->timeoutSrc->startTimer1();
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_BoPurchase(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_BoAttack(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Attacking();
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "G Waiting move confirm::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}


genericState* ST_WaitingMoveConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING MOVE CONFIRMATION: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingMoveConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_Attacking ///////////////////////////////
genericState* ST_Attacking::on_Tile(genericEvent *ev, usefulInfo * Info)
{
	cout << "G Attacking::on_Tile" << endl;
	genericState *ret;
	//HACER: cuando el mouse ve que se toca un tile del mapa,
	//guardar esa info en la clase game en tileSelected y generar el evento TILE
	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()) != NULL) &&
		(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap1")!=0)  &&
		(Info->gameInterface->myMap->getTile(Info->gameInterface->getTileSelected().i, Info->gameInterface->getTileSelected().j)->getUnit()->getType().compare("ap2") != 0) &&
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
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Attacking::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G ATTACKING: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Attacking::on_RYouWon(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G ATTACKING: ON r you won" << endl;
	genericState *ret = (genericState *) new ST_G_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIWantToPlayAgain(Info->gameInterface->graphics->doIwantToPlayAgain());
	
	Info->gameInterface->setAnalysePlayAgain(true);
	
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Attacking::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_Attacking::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_Attacking::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

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
	return ret;
}

genericState* ST_WaitingDefender::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "ST_WaitingDefender::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingDefender::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING DEFENDER: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingDefender::on_RYouWon(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G waiting defender: ON r you won" << endl;
	genericState *ret = (genericState *) new ST_G_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIWantToPlayAgain(Info->gameInterface->graphics->doIwantToPlayAgain());
	
	Info->gameInterface->setAnalysePlayAgain(true);
	
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingDefender::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingDefender::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingDefender::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}
/////////////////////////////// ST_WaitingAttackConfirmation ///////////////////////////////
genericState* ST_WaitingAttackConfirmation::on_Attack(genericEvent *ev, usefulInfo * Info)
{
	int temp_i = 0, temp_j = 0;
	cout << "ST_WaitingAttackConfirmation::on_Attack" << endl;
	genericState *ret = (genericState *) new ST_Attacking(); //CAMBIO 2: esta linea cambiada por la de abajo
	//genericState *ret = (genericState *) new ST_();
	if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
	{
		Info->gameInterface->setDie(rand() % 6 + 1); //VERIFICAR si esto tira un valor random entre 1 y 6.
		Info->gameInterface->graphics->showDice(Info->gameInterface->getDie());
		Info->gameInterface->attack();
		Info->timeoutSrc->startTimer1();

		if (Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit() != NULL)
		{
			Info->gameInterface->myMap->possibleAttack(Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit(), Info->gameInterface->getDefender().i, (Info->gameInterface->getDefender().j), Info->gameInterface->playerYou->getTeam());
			
			if (Info->gameInterface->myMap->canAttack[Info->gameInterface->getAttacker().i][Info->gameInterface->getAttacker().j])
			{
				temp_i = Info->gameInterface->getAttacker().i;
				temp_j = Info->gameInterface->getAttacker().j;
				Info->gameInterface->setAttacker(Info->gameInterface->getDefender());
				Info->gameInterface->setDefender(temp_i, temp_j);
				Info->gameInterface->attack();
				Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->setHp(Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->getHp() + 1);

			}
		}
		Info->gameInterface->setAttacker(NULL, NULL);
		Info->gameInterface->setDefender(NULL, NULL);
		
	
	
	}
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_BoPurchase(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_Purchasing();
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_Pass(genericEvent* ev, usefulInfo * Info)
{
	cout << "G Waiting attack confirm::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}
genericState* ST_WaitingAttackConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING ATTACK CONFIRM: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_RYouWon(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G waiting attack confirm: ON r you won" << endl;
	genericState *ret = (genericState *) new ST_G_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIWantToPlayAgain(Info->gameInterface->graphics->doIwantToPlayAgain());
	
	Info->gameInterface->setAnalysePlayAgain(true);
	
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingAttackConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_Purchasing ///////////////////////////////
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
	return ret;
}

genericState* ST_Purchasing::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_Purchasing::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Purchasing::on_NoMoney(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Purchasing::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G PURCHASING: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_Purchasing::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_Purchasing::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_Purchasing::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
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
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingLocation::on_NoMoney(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingLocation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING LOCATION: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingLocation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingLocation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingLocation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}
/////////////////////////////// ST_WaitingPurchaseConfirmation ///////////////////////////////
genericState* ST_WaitingPurchaseConfirmation::on_Purchase(genericEvent *ev, usefulInfo * Info)
{
	cout << "waiting purchase confirmation: on purchase" << endl;
	genericState *ret = (genericState *) new ST_Purchasing();
	Info->gameInterface->purchase(Info->gameInterface->playerMe);
	Info->timeoutSrc->startTimer1();
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_NoMoney(genericEvent *ev, usefulInfo * Info)
{
	cout << "G waiting purchase confirm::on_NoMoney" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}


genericState* ST_WaitingPurchaseConfirmation::on_Pass(genericEvent *ev, usefulInfo * Info)
{
	cout << "G waiting purchase confirm::on_Pass" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerYou, Info->gameInterface);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_OneMinTimeout(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G WAITING PURCHASE CONRIM: ON 1 MIN TIMEOUT" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_WaitingPurchaseConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_YouMoving ///////////////////////////////

genericState* ST_YouMoving::on_RMove(genericEvent *ev, usefulInfo * Info)
{
	cout << "ST_YouMoving:: on_RMOVE" << endl;
	genericState *ret = (genericState *) new ST_YouMoving();

	if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()) != NULL) &&
		(((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit())->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
	{	
		cout << "ENTRO A MOVER ALGO" << endl;
	
		if (Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit() != NULL)
		{
			if ((((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getType().compare("ap1") == 0) ||
				(Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getType().compare("ap2") == 0)) &&
				((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))&&

				  (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("in1") == 0) ||
					(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("in2") == 0) ||
					(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("me1") == 0) ||
					(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("me2") == 0)) &&
					((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam()))))
			{
				cout << "defender es apc" << endl;
				Info->gameInterface->boardUnit();
				ret= (genericState *) new ST_YouMoving();
			}
	
			else if (((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("ap1") == 0) ||
				(Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getType().compare("ap2") == 0)) &&
				((Info->gameInterface->myMap->getTile(Info->gameInterface->getAttacker().i, Info->gameInterface->getAttacker().j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam()))&&
				((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getType().compare("ap1") == 0) ||
				(Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getType().compare("ap2") == 0)) &&
				((Info->gameInterface->myMap->getTile(Info->gameInterface->getDefender().i, Info->gameInterface->getDefender().j)->getUnit()->getTeam()) == (Info->gameInterface->playerYou->getTeam())))
			{
				cout << "attacker es apc" << endl;
				ret = (genericState *) new ST_YouUnboardingUnit();
			}
		}
		else
		{
			cout << "movimiento normal" << endl;
			Info->gameInterface->move();
			ret = (genericState *) new ST_YouMoving();
		}

	}
	return ret;
}

genericState* ST_YouMoving::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_YouMoving::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_YouMoving::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

////////////////////////////////////////////////////////


genericState* ST_YouMoving::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_YouAttacking();
	int temp_i = 0, temp_j = 0;
	//HACER: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->getAttacker().i != NULL) &&
		(Info->gameInterface->getAttacker().j != NULL) &&
		(Info->gameInterface->getDefender().i != NULL) &&
		(Info->gameInterface->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->graphics->showDice(Info->gameInterface->getDie());
			Info->gameInterface->attack();
			if (Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit() != NULL)
			{
				Info->gameInterface->myMap->possibleAttack(Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit(), Info->gameInterface->getDefender().i, (Info->gameInterface->getDefender().j), Info->gameInterface->playerMe->getTeam());

				if (Info->gameInterface->myMap->canAttack[Info->gameInterface->getAttacker().i][Info->gameInterface->getAttacker().j])
				{
					temp_i = Info->gameInterface->getAttacker().i;
					temp_j = Info->gameInterface->getAttacker().j;
					Info->gameInterface->setAttacker(Info->gameInterface->getDefender());
					Info->gameInterface->setDefender(temp_i, temp_j);
					Info->gameInterface->attack();
					Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->setHp(Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->getHp() + 1);

				}
			}
			Info->gameInterface->setAttacker(NULL, NULL);
			Info->gameInterface->setDefender(NULL, NULL);

			
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
	cout << "g you moving on_RPass" << endl;
	//genericState *ret = (genericState *) new ST_Moving();
	//Info->gameInterface->setIamPlaying(true);
	genericState *ret = (genericState *) new ST_AnalysingVictoryHQ();
	setCaptureProperty(Info->gameInterface->playerMe, Info->gameInterface);
	Info->gameInterface->didHeWin();
	Info->gameInterface->setAnalyseVictory(true); //agrego esto!!!!!!!!!!!!
	Info->timeoutSrc->startTimer1(); //CHEQUEAR
	return ret;
}
genericState* ST_YouMoving::on_RYouWon(genericEvent *ev, usefulInfo * Info) //ESTO PONERLO EN TODOS LOS PASS Y EN TODOS LOS NO MONEY
{
	cout << "G you movinG: ON r you won" << endl;
	genericState *ret = (genericState *) new ST_G_WaitingPlayingAgainConfirmation();
	Info->gameInterface->setIWantToPlayAgain(Info->gameInterface->graphics->doIwantToPlayAgain());

	Info->gameInterface->setAnalysePlayAgain(true);
	
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1(); //CHEQUEAR
	return ret;
}

/////////////////////////////////////////////////////////
genericState* ST_YouUnboardingUnit::on_RMove(genericEvent *ev, usefulInfo * Info)
{
	//HACER
	Info->gameInterface->unboardUnit();
	genericState *ret = (genericState *) new ST_YouMoving();
	return ret;
}


genericState* ST_YouUnboardingUnit::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_YouUnboardingUnit::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_YouUnboardingUnit::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_YouAttacking ///////////////////////////////

genericState* ST_YouAttacking::on_RAttack(genericEvent *ev, usefulInfo * Info)
{
	//genericState *ret = (genericState *) new ST_YouAttacking(); //CAMBIO 3
	genericState *ret = (genericState *) new ST_Attacking();
	int temp_i = 0, temp_j = 0;
	//HACER EN IS THERE EVENT DE NETWORKING: leer el mensaje que me llega del ataque y cargar el tile atacante y el defendido en attacker y defender

	if ((Info->gameInterface->getAttacker().i != NULL) &&
		(Info->gameInterface->getAttacker().j != NULL) &&
		(Info->gameInterface->getDefender().i != NULL) &&
		(Info->gameInterface->getDefender().j != NULL))
	{
		if (((Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j)))->getUnit()) != NULL)
		{
			Info->gameInterface->graphics->showDice(Info->gameInterface->getDie());
			Info->gameInterface->attack();

			if (Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit() != NULL)
			{
				Info->gameInterface->myMap->possibleAttack(Info->gameInterface->myMap->getTile((Info->gameInterface->getDefender().i), (Info->gameInterface->getDefender().j))->getUnit(), Info->gameInterface->getDefender().i, (Info->gameInterface->getDefender().j), Info->gameInterface->playerMe->getTeam());

				if (Info->gameInterface->myMap->canAttack[Info->gameInterface->getAttacker().i][Info->gameInterface->getAttacker().j])
				{
					temp_i = Info->gameInterface->getAttacker().i;
					temp_j = Info->gameInterface->getAttacker().j;
					Info->gameInterface->setAttacker(Info->gameInterface->getDefender());
					Info->gameInterface->setDefender(temp_i, temp_j);
					Info->gameInterface->attack();
					Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->setHp(Info->gameInterface->myMap->getTile(temp_i, temp_j)->getUnit()->getHp() + 1);
				}
			}

			Info->gameInterface->setAttacker(NULL, NULL);
			Info->gameInterface->setDefender(NULL, NULL);


			
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

genericState* ST_YouAttacking::on_RPass(genericEvent *ev, usefulInfo * Info)
{
	cout << "entra a on_RPass" << endl;
	//genericState *ret = (genericState *) new ST_Moving();
	//Info->gameInterface->setIamPlaying(true);
	genericState *ret = (genericState *) new ST_AnalysingVictoryHQ();
	setCaptureProperty(Info->gameInterface->playerMe, Info->gameInterface);
	Info->gameInterface->didHeWin();
	Info->gameInterface->setAnalyseVictory(true); //agrego esto!!!!!!!!!!!!
	Info->timeoutSrc->startTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_YouAttacking::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_YouAttacking::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_YouAttacking::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

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
	//genericState *ret = (genericState *) new ST_Moving();
	//Info->gameInterface->setIamPlaying(true);
	genericState *ret = (genericState *) new ST_AnalysingVictoryHQ();
	setCaptureProperty(Info->gameInterface->playerMe, Info->gameInterface);
	//Info->gameInterface->didHeWin();
	Info->gameInterface->setAnalyseVictory(true); //agrego esto!!!!!!!!!!!!
	Info->timeoutSrc->startTimer1(); //CHEQUEAR
	return ret;
}

genericState* ST_YouPurchasing::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_YouPurchasing::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_YouPurchasing::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_AnalysingVictoryHQ ///////////////////////////////
genericState* ST_AnalysingVictoryHQ::on_YouDidntWin(genericEvent *ev, usefulInfo * Info)
{
	cout << "juego yo. El otro no gano." << endl;
	genericState *ret = (genericState *) new ST_Moving();
	Info->gameInterface->setIamPlaying(true);
	Info->gameInterface->setAnalyseVictory(false); //	CHEQUEAR!!!!!
	return ret;
}

genericState* ST_AnalysingVictoryHQ::on_YouWon(genericEvent *ev, usefulInfo * Info)
{
	cout << "GANO EL OTRO. SE QUEDO CON MI HQ." << endl;
	genericState *ret = (genericState *) new ST_GameIdle(); //VER
	Info->gameInterface->setIamPlaying(false);
	return ret;
}

genericState* ST_AnalysingVictoryHQ::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_AnalysingVictoryHQ::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_AnalysingVictoryHQ::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}

/////////////////////////////// ST_AnalysingVictoryUnits ///////////////////////////////
genericState* ST_AnalysingVictoryUnits::on_YouDidntWin(genericEvent *ev, usefulInfo * Info)
{
	cout << "juego yo. El otro no gano." << endl;
	genericState *ret = (genericState *) new ST_YouAttacking();
	Info->gameInterface->setIamPlaying(true);
	return ret;
}

genericState* ST_AnalysingVictoryUnits::on_YouWon(genericEvent *ev, usefulInfo * Info)
{
	cout << "GANO EL OTRO. SE QUEDO CON Mis UNITS." << endl;
	genericState *ret = (genericState *) new ST_GameIdle(); //VER
	Info->gameInterface->setIamPlaying(false);
	return ret;
}

genericState* ST_AnalysingVictoryUnits::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	//Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_AnalysingVictoryUnits::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_AnalysingVictoryUnits::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}
////////////////////////// ST_WaitingPlayingAgainConfirmation /////////////////////////
genericState* ST_G_WaitingPlayingAgainConfirmation::on_PlayAgain(genericEvent* ev, usefulInfo * Info)
{
	cout << "waiting playing again confirm: on playing again." << endl;
	genericState *ret = (genericState *) new ST_GameIdle(); //VER
	Info->gameInterface->setIamPlaying(false);
	return ret;
}

genericState* ST_G_WaitingPlayingAgainConfirmation::on_GameOver(genericEvent* ev, usefulInfo * Info)
{
	cout << "THE END." << endl;
	genericState *ret = (genericState *) new ST_GameIdle(); //VER
	Info->gameInterface->setIamPlaying(false);
	setCaptureProperty(Info->gameInterface->playerMe, Info->gameInterface);
	//Info->timeoutSrc->startTimer1(); //CHEQUEAR
	return ret;

	//VER SI HACER ALGO MAS!!!!!!!!!!!!!!
}

genericState* ST_G_WaitingPlayingAgainConfirmation::on_Quit(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
//	Info->gameInterface->quit = true;
	return ret;
}

genericState* ST_G_WaitingPlayingAgainConfirmation::on_Rerror(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	return ret;
}

genericState* ST_G_WaitingPlayingAgainConfirmation::on_Error(genericEvent* ev, usefulInfo * Info)
{
	genericState *ret = (genericState *) new ST_GameIdle();
	Info->gameInterface->setIamPlaying(false);
	Info->timeoutSrc->stopTimer1();
	Info->gameInterface->setYouWinning(false);
	Info->gameInterface->error = true;
	return ret;
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// SET CAPTURE PROPERTY TIENE QUE IR A GAME CPP!!!!!!!!!!!!!
void setCaptureProperty(Player* player, Game* gameInterface) 
{
	player->setAmmountOfCities(gameInterface->myMap);
	player->setMoney((player->getMoney()) + (((player->getAmmountOfCities()) + 1) * 5));


	for (int i = 0; i < FILA; i++)
	{
		for (int j = 0; j < COLUMNA; j++)
		{
			if (((gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((gameInterface->myMap->getTile(i, j)->getBuilding()->getTeam()) == player->getTeam()) &&
				((gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (player->getTeam())))
			{

				gameInterface->myMap->getTile(i, j)->getUnit()->setHp((gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) + 2);
				if ((gameInterface->myMap->getTile(i, j)->getUnit()->getHp()) > 8)
				{
					gameInterface->myMap->getTile(i, j)->getUnit()->setHp(8);
				}
			}

			if (((gameInterface->myMap->getTile(i, j)->getUnit()) != NULL)) {
				gameInterface->myMap->getTile(i, j)->getUnit()->resetMp();
			}



			//CAPTURA DE PROPIEDAD
			//antes de llamar a esta funcion debo setear el attacker con la unidad que este encima de un building que no es propio
			if (((gameInterface->myMap->getTile(i, j)->getUnit()) != NULL) && ((gameInterface->myMap->getTile(i, j)->getBuilding()) != NULL) &&
				((((gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("in1")) == 0) ||
				((gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("me1")) == 0)) ||
					(((gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("in2")) == 0) ||
					((gameInterface->myMap->getTile(i, j)->getUnit()->getType().compare("me2")) == 0))) &&
						((gameInterface->myMap->getTile(i, j)->getUnit()->getTeam()) == (player->getTeam())) &&
				(gameInterface->myMap->getTile(i, j)->getBuilding()->getTeam() != (player->getTeam())))
			{

				gameInterface->setAttacker(i, j);
				gameInterface->captureProperty(player);
				if ((gameInterface->myMap->getTile(i, j)->getBuilding()->getCp()) <= 0)
				{
					cout << "SE CAPTURO POR COMPLETO!!!!(I=" << i << "; J=" << j << ")" << endl;
					cout << "CP DEL BUILDING=" << gameInterface->myMap->getTile(i, j)->getBuilding()->getCp() << endl;
					//en el tile donde estaba antes el building del oponente, poner el mismo building pero de mi equipo.
					gameInterface->myMap->getTile(i, j)->getBuilding()->setTeam(player->getTeam());
					gameInterface->myMap->getTile(i, j)->getBuilding()->updatePath();
					if (gameInterface->myMap->getTile(i, j)->getBuilding()->getType() == "q" || gameInterface->myMap->getTile(i, j)->getBuilding()->getType() == "q1" || gameInterface->myMap->getTile(i, j)->getBuilding()->getType() == "q2") {

						cout << "Entro aca a este iffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" << endl;
						//gameInterface->myMap->getTile(i, j)->removeBuilding();
						gameInterface->myMap->getTile(i, j)->getBuilding()->setCp(8);
					}
					else
					{
						gameInterface->myMap->getTile(i, j)->getBuilding()->setCp(4);
					}
					gameInterface->graphics->loadBitmaps(gameInterface->myMap);
//					gameInterface->graphics->showMap(gameInterface->data, gameInterface->myMap, gameInterface->playerMe->getMoney(), gameInterface->playerMe->getTeam());
				}
				cout << "CAPTURE PERO NO DEL TODO EN (I=" << i << ";J=" << j << ")" << endl;
				cout << "CP DEL BUILDING=" << gameInterface->myMap->getTile(i, j)->getBuilding()->getCp() << endl;

			}

			

		}
	}

}