#include "basicXML.h"

void readFileToBuffer(XML_Parser P, FILE * fp)
{
	char buffer[BUFF_LEN];
	int allFileRead = 0;
	size_t buflen = 0;
	do {
		buflen = fread( buffer, 1, BUFF_LEN, fp);
		allFileRead = (buflen < BUFF_LEN)?1:0;
		if (XML_Parse(P, buffer, buflen, allFileRead) == XML_STATUS_ERROR) {
			printf("CANNOT READ MORE\n");
			break;
		}

	} while (!allFileRead);
	
}

void startTagCallback(void *userData, const XML_Char *name, const XML_Char **atts)	//< >
{
	Resources* myData = (Resources*)userData;
	
	if (strcmp(name, "resources") == false)
	{
		myData->setFeedState(RESOURCES);
	}
	else if (strcmp(name, "buildings") == false)
	{
		myData->setFeedState(BUILDING);		
	}
	else if (strcmp(name, "terrains") == false)
	{
		myData->setFeedState(TERRAIN);
	}
	else if (strcmp(name, "units") == false)
	{
		myData->setFeedState(UNIT);
	}
	else if (strcmp(name, "item") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING:
			myData->setFeedState(BUILDING_ITEM);
			myData->addBuilding();
			break;
		case TERRAIN:
			myData->setFeedState(TERRAIN_ITEM);
			myData->addTerrain();
			break;
		case UNIT:
			myData->setFeedState(UNIT_ITEM);
			myData->addUnit();
			break;
		}
	}
	else if (strcmp(name, "name") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING_ITEM:
			myData->setFeedState(B_NAME);
			break;
		case TERRAIN_ITEM:
			myData->setFeedState(T_NAME);
			break;
		case UNIT_ITEM:
			myData->setFeedState(U_NAME);
			break;
		}
	}
	else if (strcmp(name, "hp") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING_ITEM:
			myData->setFeedState(B_HP);
			break;
		case UNIT_ITEM:
			myData->setFeedState(U_HP);
			break;
		}
	}
	else if (strcmp(name, "path") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING_ITEM:
			myData->setFeedState(B_PATH);
			break;
		case TERRAIN_ITEM:
			myData->setFeedState(T_PATH);
			break;
		case UNIT_ITEM:
			myData->setFeedState(U_PATH);
			break;
		}
	}
	else
		myData->setFeedState(_IGNORE);

}

void chararacterDataCallback(void *userData, const XML_Char *s, int len)
{
	Resources* myData = (Resources*)userData;

	string d(s, s + len);

	switch (myData->getFeedSate())
	{
	case B_NAME:
		myData->getLastBuilding().setName(d);	//set name
		break;
	case B_PATH:
		myData->getLastBuilding().setPath(d);	//set path
		break;
	case B_HP:
		myData->getLastBuilding().setHp(d);	//set hp
		break;
	case T_NAME:
		myData->getLastTerrain().setName(d);	//set name
		break;
	case T_PATH:
		myData->getLastTerrain().setPath(d);	//set path
		break;

	case U_PATH:
		myData->getLastUnit().setPath(d);	//set path
		break;
	case U_NAME:
		myData->getLastUnit().setName(d);	//set path
		break;
	case U_HP:
		myData->getLastUnit().setHp(d);		//set path
		break;
	case COST:
		myData->getLastUnit().setCost(d);	//set path
		break;
	case MP:
		myData->getLastUnit().setMp(d);	//set path
		break;
	case DEFENCE:
		myData->getLastUnit().setDefence(d);	//set path
		break;
	case RANGEMIN:
		myData->getLastUnit().setMinRange(d);	//set path
		break;
	case RANGEMAX:
		myData->getLastUnit().setMaxRange(d);	//set path
		break;
	case PLAINCOST:
		myData->getLastUnit().setPlainCost(d);	//set path
		break;
	case RIVERCOST:
		myData->getLastUnit().setRiverCost(d);	//set path
		break;
	case ROADCOST:
		myData->getLastUnit().setRoadCost(d);	//set path
		break;
	case FORESTCOST:
		myData->getLastUnit().setForestCost(d);	//set path
		break;
	case HILLSCOST:
		myData->getLastUnit().setHillsCost(d);	//set path
		break;
	case FPNORMAL:
		switch (myData->getFeedSate())
		{
		case MOON:
			myData->getLastUnit().setFpNormalMoon(d);
			break;
		case STAR:
			myData->getLastUnit().setFpNormalStar(d);
			break;
		case CIRCLE:
			myData->getLastUnit().setFpNormalCircle(d);
			break;
		case TRIANGLE:
			myData->getLastUnit().setFpNormalTriangle(d);
			break;
		}
		break;
	case FPREDUCED:
		switch (myData->getFeedSate())
		{
		case MOON:
			myData->getLastUnit().setFpReducedMoon(d);
			break;
		case STAR:
			myData->getLastUnit().setFpReducedStar(d);
			break;
		case CIRCLE:
			myData->getLastUnit().setFpReducedCircle(d);
			break;
		case TRIANGLE:
			myData->getLastUnit().setFpReducedTriangle(d);
			break;
		}
		break;
	case _IGNORE:
		break;
	}

}

void endTagCallback(void *userData, const XML_Char *name)		//</ >
{
	Resources* myData = (Resources*)userData;

	if (strcmp(name, "/resources") == false)
	{
		myData->setFeedState(IDLE);
	}
	else if (strcmp(name, "/buildings") == false)
	{
		myData->setFeedState(RESOURCES);
	}
	else if (strcmp(name, "/terrains") == false)
	{
		myData->setFeedState(RESOURCES);
	}
	else if (strcmp(name, "/units") == false)
	{
		myData->setFeedState(UNIT);
	}
	else if (strcmp(name, "/item") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING_ITEM:
			myData->setFeedState(BUILDING);
			break;
		case TERRAIN_ITEM:
			myData->setFeedState(TERRAIN);
			break;
		case UNIT_ITEM:
			myData->setFeedState(UNIT);
			break;
		}
	}
	
	else if (strcmp(name, "/name") == false)
	{
		switch (myData->getFeedSate())
		{
		case B_NAME:
			myData->setFeedState(BUILDING_ITEM);
			break;
		case T_NAME:
			myData->setFeedState(TERRAIN_ITEM);
			break;
		case U_NAME:
			myData->setFeedState(UNIT_ITEM);
			break;
		}
	}
	else if (strcmp(name, "/hp") == false)
	{
		switch (myData->getFeedSate())
		{
		case B_HP:
			myData->setFeedState(BUILDING_ITEM);
			break;
		case U_HP:
			myData->setFeedState(UNIT_ITEM);
			break;
		}
	}
	else if (strcmp(name, "/path") == false)
	{
		switch (myData->getFeedSate())
		{
		case B_PATH:
			myData->setFeedState(BUILDING_ITEM);
			break;
		case T_PATH:
			myData->setFeedState(TERRAIN_ITEM);
			break;
		case U_PATH:
			myData->setFeedState(UNIT_ITEM);
			break;
		}
	}
	else
		myData->setFeedState(_IGNORE);

}
