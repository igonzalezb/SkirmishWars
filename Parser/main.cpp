#include <iostream>
#include "basicXML.h"

int main(int argc, char * argv[])
{
	if (argc == 2)
	{
		XML_Parser P = XML_ParserCreate(NULL);
		FILE * fp = fopen(argv[1], "rb");

		Resources data;
		

		XML_SetStartElementHandler(P, startTagCallback);	// funcion que va a encontrar cuando aparece un Start tag);
		XML_SetEndElementHandler(P, endTagCallback);		//funcion que va a encontrar cuando aparece un End tag);
		XML_SetCharacterDataHandler(P, chararacterDataCallback);
		XML_SetUserData(P, &data);

		readFileToBuffer(P, fp);

		fclose(fp);
	}
	
	return EXIT_SUCCESS;
}