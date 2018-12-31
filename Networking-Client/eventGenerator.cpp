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

	if (I->networkSrc->isThereEvent())
	{
		buffer.push_back(I->networkSrc->insertEvent());
	}
	/*
	if (I->timeoutSrc->isThereEvent())
	{
	buffer.push_back(I->timeoutSrc->insertEvent());
	}

	if (I->userSrc->isThereEvent())
	{
	buffer.push_back(I->userSrc->insertEvent());
	}
	*/

}

genericEvent * eventGenerator::getNextEvent()
{
	genericEvent * ret;
	if (buffer.size() != 0)
	{
		ret = buffer.front();	//carga en re t el primer elemento del buffer
		buffer.pop_front();	//elimina el ultimo elemento del buffer
#ifdef DEBUG
		cout << "entra 4: entro a get next event" << endl;
#endif // DEBUG
	}
	else
	{
		ret = nullptr;	//Si no hay eventos en el buffer devuelve nullptr
	}
	return ret;
}
