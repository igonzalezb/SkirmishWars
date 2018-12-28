
#include "Game.h"


Game::Game()
{
	player1 = new Player();
	player2 = new Player();
	map = new Map();
	graphics = new MapGraphics();

	char * xml_path = XML_PATH;
	XML_Parser P = XML_ParserCreate(NULL);
	FILE * fp = fopen(xml_path, "rb");
	Resources data;

	XML_SetStartElementHandler(P, startTagCallback);	// Función que va a encontrar cuando aparece un Start tag;
	XML_SetEndElementHandler(P, endTagCallback);		//Función que va a encontrar cuando aparece un End tag;
	XML_SetCharacterDataHandler(P, chararacterDataCallback);
	XML_SetUserData(P, &data);
	readFileToBuffer(P, fp);
	fclose(fp);

	map->generateTilesArray(data.getBuildingList(), data.getTerrainList(), data.getUnitList());
	
	
	map->updateFogOfWar(player1->getTeam());	//VER ESTO!!!


	graphics->loadBitmaps(map);
	graphics->showMap(map);
}

Game::~Game()
{
	delete player1;
	delete player2;
	delete map;
	delete graphics;
}