#include <iostream>
#include <ctime>

#include "basicXML.h"
#include "AllegroSetup.h"

#include "PlayerInfo.h"

#include "MapGraphics.h"

#define XML_PATH	"resources.xml"

using namespace std;



int main(int argc, char * argv[])
{
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

	srand(time(NULL));

	allegroStartup();
	
	Player me;
		
	MapGraphics graphics;
	Map map;
	
	map.generateTilesArray(data.getBuildingList(), data.getTerrainList(), data.getUnitList());
	map.updateFogOfWar(me.getTeam());		//FIJARSE DONDE TIENE QUE IR!

	graphics.loadBitmaps(&map);
	graphics.showMap(&map);

	getchar();
	
	
	return EXIT_SUCCESS;
}