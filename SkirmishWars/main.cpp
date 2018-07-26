#include <iostream>
#include "AllegroSetup.h"
#include "Terrain.h"
int main(void)
{
	if (allegroStartup())
		return EXIT_FAILURE;




	//comentario de prueba


	allegroShutdown();
	return EXIT_SUCCESS;
}