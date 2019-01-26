#include "eventGenerator.h"

eventGenerator::eventGenerator(usefulInfo* _I) :buffer(16) //VER BUFFER 16 QUE ONDA
{
	I = _I;
}

void eventGenerator::generateEvent()
{

	/*
	if (I->softwareSrc->isThereEvent())
	{
	buffer.push_back(I->softwareSrc->insertEvent());
	}*/

	//cout << "entra a generate Event " << endl;

	if (I->networkSrc->isThereEvent())
	{
		buffer.push_back(I->networkSrc->insertEvent());


		//if ((I->gameSrc->evCode == TILE) || (I->gameSrc->evCode == MOVE) || (I->gameSrc->evCode == NEW_UNIT)) //PARA PROBAR!!!!!!
		//{
		//	I->userSrc->graphics->loadBitmaps(I->gameInterface->myMap);
		//	I->userSrc->graphics->showMap(I->userSrc->gameInterface);
		//}
		////if (I->gameSrc->evCode != NO_EV) //PARA PROBAR!!!!!!
		//else
		//{
		//I->gameInterface->myMap->updateFogOfWar(I->gameInterface->playerMe->getTeam());
		//I->gameInterface->graphics->loadBitmaps(I->gameInterface->myMap);
		//I->gameInterface->graphics->showMap(I->userSrc->gameInterface->data, I->userSrc->gameInterface->myMap, I->userSrc->gameInterface->playerMe->getMoney());
		//}
	}
	if (I->gameSrc->isThereEvent())
	{
		buffer.push_back(I->gameSrc->insertEvent());

		//if ((I->gameSrc->evCode == TILE) || (I->gameSrc->evCode == MOVE) || (I->gameSrc->evCode == NEW_UNIT) || (I->gameSrc->evCode == I_START) || (I->gameSrc->evCode == YOU_START)) //PARA PROBAR!!!!!!
		//{
		//	I->userSrc->graphics->loadBitmaps(I->gameInterface->myMap);
		//	I->userSrc->graphics->showMap(I->userSrc->gameInterface);
		//}
		//if (I->gameSrc->evCode != NO_EV) //PARA PROBAR!!!!!!
		//else
		//{
		//I->gameInterface->myMap->updateFogOfWar(I->gameInterface->playerMe->getTeam());
			//I->gameInterface->graphics->loadBitmaps(I->gameInterface->myMap);
			//I->gameInterface->graphics->showMap(I->userSrc->gameInterface->data, I->userSrc->gameInterface->myMap, I->userSrc->gameInterface->playerMe->getMoney());
			//}
	}
	

	if (I->timeoutSrc->isThereEvent())
	{
	buffer.push_back(I->timeoutSrc->insertEvent());
	}


	if (I->userSrc->isThereEvent())
	{
		buffer.push_back(I->userSrc->insertEvent());

		//if ((I->gameSrc->evCode == TILE) || (I->gameSrc->evCode == MOVE) || (I->gameSrc->evCode == NEW_UNIT) || (I->gameSrc->evCode == I_START) || (I->gameSrc->evCode == YOU_START)) //PARA PROBAR!!!!!!
		//{
		//	I->userSrc->graphics->loadBitmaps(I->gameInterface->myMap);
		//	I->userSrc->graphics->showMap(I->userSrc->gameInterface);
		//}
		////if (I->gameSrc->evCode != NO_EV) //PARA PROBAR!!!!!!
		//else //if (I->gameSrc->evCode != NO_EV)
		//{
		//I->gameInterface->myMap->updateFogOfWar(I->gameInterface->playerMe->getTeam());
			//I->gameInterface->graphics->loadBitmaps(I->gameInterface->myMap);
			//I->gameInterface->graphics->showMap(I->userSrc->gameInterface->data, I->userSrc->gameInterface->myMap, I->userSrc->gameInterface->playerMe->getMoney());
			//}
	//
	}
	

}

genericEvent * eventGenerator::getNextEvent()
{
	genericEvent * ret;
	if (buffer.size() != 0)
	{
		ret = buffer.front();	//carga en re t el primer elemento del buffer
		buffer.pop_front();	//elimina el ultimo elemento del buffer
	}
	else
	{
		ret = nullptr;	//Si no hay eventos en el buffer devuelve nullptr
	}
	return ret;
}
