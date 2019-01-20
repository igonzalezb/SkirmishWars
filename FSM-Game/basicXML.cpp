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
	else if (strcmp(name, "code") == false)
	{
		switch (myData->getFeedSate())
		{
		case BUILDING_ITEM:
			myData->setFeedState(B_TYPE);
			break;
		case TERRAIN_ITEM:
			myData->setFeedState(T_TYPE);
			break;
		case UNIT_ITEM:
			myData->setFeedState(U_TYPE);
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
	else if (strcmp(name, "cost") == false)
	{
		myData->setFeedState(COST);
	}
	else if (strcmp(name, "symbol") == false)
	{
		myData->setFeedState(U_SYMBOL);
	}
	else if (strcmp(name, "mp") == false)
	{
		myData->setFeedState(MP);
	}
	else if (strcmp(name, "defense") == false)
	{
		myData->setFeedState(DEFENSE);
	}
	else if (strcmp(name, "rangemin") == false)
	{
		myData->setFeedState(RANGEMIN);
	}
	else if (strcmp(name, "rangemax") == false)
	{
		myData->setFeedState(RANGEMAX);
	}
	else if (strcmp(name, "plaincost") == false)
	{
		myData->setFeedState(PLAINCOST);
	}
	else if (strcmp(name, "roadcost") == false)
	{
		myData->setFeedState(ROADCOST);
	}
	else if (strcmp(name, "forestcost") == false)
	{
		myData->setFeedState(FORESTCOST);
	}
	else if (strcmp(name, "rivercost") == false)
	{
		myData->setFeedState(RIVERCOST);
	}
	else if (strcmp(name, "hillscost") == false)
	{
		myData->setFeedState(HILLSCOST);
	}
	else if (strcmp(name, "fpnormal") == false)
	{
		myData->setFeedState(FPNORMAL);
	}
	else if (strcmp(name, "fpreduced") == false)
	{
		myData->setFeedState(FPREDUCED);
	}
	else if (strcmp(name, "moon") == false)
	{
		switch (myData->getFeedSate())
		{
		case FPREDUCED:
			myData->setFeedState(R_MOON);
			break;
		case FPNORMAL:
			myData->setFeedState(N_MOON);
			break;
		}
	}
	else if (strcmp(name, "star") == false)
	{
		switch (myData->getFeedSate())
		{
		case FPREDUCED:
			myData->setFeedState(R_STAR);
			break;
		case FPNORMAL:
			myData->setFeedState(N_STAR);
			break;
		}
	}
	else if (strcmp(name, "square") == false)
	{
		switch (myData->getFeedSate())
		{
		case FPREDUCED:
			myData->setFeedState(R_SQUARE);
			break;
		case FPNORMAL:
			myData->setFeedState(N_SQUARE);
			break;
		}
	}
	else if (strcmp(name, "triangle") == false)
	{
		switch (myData->getFeedSate())
		{
		case FPREDUCED:
			myData->setFeedState(R_TRIANGLE);
			break;
		case FPNORMAL:
			myData->setFeedState(N_TRIANGLE);
			break;
		}
	}
	else if (strcmp(name, "circle") == false)
	{
		switch (myData->getFeedSate())
		{
		case FPREDUCED:
			myData->setFeedState(R_CIRCLE);
			break;
		case FPNORMAL:
			myData->setFeedState(N_CIRCLE);
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
//	cout << d << endl;


	switch (myData->getFeedSate())
	{
	case B_NAME:
		myData->getLastBuilding().setName(d);	//set name
		break;
	case B_PATH:
		myData->getLastBuilding().setPath(d);	//set path
		break;
	case B_HP:
		myData->getLastBuilding().setCp(stoi(d));	//set hp
		break;
	case B_TYPE:
		myData->getLastBuilding().setType(d);
	case T_NAME:
		myData->getLastTerrain().setName(d);	//set name
		break;
	case T_PATH:
		myData->getLastTerrain().setPath(d);	//set path
		break;
	case T_TYPE:
		myData->getLastTerrain().setType(d);	//set name
		break;

	case U_PATH:
		myData->getLastUnit().setPath(d);	//set path
		break;
	case U_NAME:
		myData->getLastUnit().setName(d);	//set path
		break;
	case U_SYMBOL:
		myData->getLastUnit().setSymbol(d);	//set path
		break;
	case U_TYPE:
		myData->getLastUnit().setType(d);
		break;
	case U_HP:
		//printf("%i", stoi(d));
		myData->getLastUnit().setHp(stoi(d));		//set path
		break;
	case COST:
		myData->getLastUnit().setCost(d);	//set path
		break;
	case MP:
		myData->getLastUnit().setMp(d);	//set path
		break;
	case DEFENSE:
		myData->getLastUnit().setdefense(d);	//set path
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
	case N_CIRCLE:
		myData->getLastUnit().setFpNormalCircle(d);	//set path
		break;
	case N_SQUARE:
		myData->getLastUnit().setFpNormalSquare(d);	//set path
		break;
	case N_TRIANGLE:
		myData->getLastUnit().setFpNormalTriangle(d);	//set path
		break;
	case N_MOON:
		myData->getLastUnit().setFpNormalMoon(d);	//set path
		break;
	case N_STAR:
		myData->getLastUnit().setFpNormalStar(d);	//set path
		break;
	case R_CIRCLE:
		myData->getLastUnit().setFpReducedCircle(d);	//set path
		break;
	case R_SQUARE:
		myData->getLastUnit().setFpReducedSquare(d);	//set path
		break;
	case R_TRIANGLE:
		myData->getLastUnit().setFpReducedTriangle(d);	//set path
		break;
	case R_MOON:
		myData->getLastUnit().setFpReducedMoon(d);	//set path
		break;
	case R_STAR:
		myData->getLastUnit().setFpReducedStar(d);	//set path
		break;
	case _IGNORE:
		break;
	}

}

void endTagCallback(void *userData, const XML_Char *name)		//</ >
{
	Resources* myData = (Resources*)userData;

	if (strcmp(name, "resources") == false)
	{
		myData->setFeedState(IDLE);
	}
	else if (strcmp(name, "buildings") == false)
	{
		myData->setFeedState(RESOURCES);
	}
	else if (strcmp(name, "terrains") == false)
	{
		myData->setFeedState(RESOURCES);
	}
	else if (strcmp(name, "units") == false)
	{
		myData->setFeedState(UNIT);
	}
	else if (strcmp(name, "item") == false)
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
	
	else if (strcmp(name, "name") == false)
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
	else if (strcmp(name, "code") == false)
	{
		switch (myData->getFeedSate())
		{
		case B_TYPE:
			myData->setFeedState(BUILDING_ITEM);
			break;
		case T_TYPE:
			myData->setFeedState(TERRAIN_ITEM);
			break;
		case U_TYPE:
			myData->setFeedState(UNIT_ITEM);
			break;
		}
	}
	else if (strcmp(name, "hp") == false)
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
	else if (strcmp(name, "path") == false)
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
	else if (strcmp(name, "cost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "mp") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "defense") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "symbol") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "rangemin") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "rangemax") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "plaincost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "roadcost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "forestcost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "hillscost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "rivercost") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "fpnormal") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "fpreduced") == false)
	{
		myData->setFeedState(UNIT_ITEM);
	}
	else if (strcmp(name, "moon") == false)
	{
		switch (myData->getFeedSate())
		{
		case R_MOON:
			myData->setFeedState(FPREDUCED);
			break;
		case N_MOON:
			myData->setFeedState(FPNORMAL);
			break;
		}
	}
	else if (strcmp(name, "star") == false)
	{
		switch (myData->getFeedSate())
		{
		case R_STAR:
			myData->setFeedState(FPREDUCED);
			break;
		case N_STAR:
			myData->setFeedState(FPNORMAL);
			break;
		}
	}
	else if (strcmp(name, "square") == false)
	{
		switch (myData->getFeedSate())
		{
		case R_SQUARE:
			myData->setFeedState(FPREDUCED);
			break;
		case N_SQUARE:
			myData->setFeedState(FPNORMAL);
			break;
		}
	}
	else if (strcmp(name, "triangle") == false)
	{
		switch (myData->getFeedSate())
		{
		case R_TRIANGLE:
			myData->setFeedState(FPREDUCED);
			break;
		case N_TRIANGLE:
			myData->setFeedState(FPNORMAL);
			break;
		}
	}
	else if (strcmp(name, "circle") == false)
	{
		switch (myData->getFeedSate())
		{
		case R_CIRCLE:
			myData->setFeedState(FPREDUCED);
			break;
		case N_CIRCLE:
			myData->setFeedState(FPNORMAL);
			break;
		}
	}
	
	else
		myData->setFeedState(RESOURCES);

}
