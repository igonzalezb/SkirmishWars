#include <iostream>
#include "basicXML.h"

#include "AllegroSetup.h"

#include "MapGraphics.h"

#define XML_PATH	"resources.xml"

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



	allegroStartup();
	MapGraphics graphics;
	Map map("resources/maps/Nascar.csv");
	map.generateTilesArray(data.getBuildingList(), data.getTerrainList(), data.getUnitList());
	graphics.setMap(&map);
	graphics.loadBitmaps();
	graphics.showMap();

	getchar();
	
	
	return EXIT_SUCCESS;
}