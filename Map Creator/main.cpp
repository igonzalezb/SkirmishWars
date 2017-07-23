#include <iostream>
#include "AllegroSetup.h"

int main(void)
{
	if (allegroStartup())
		return EXIT_FAILURE;









	allegroShutdown();
	return EXIT_SUCCESS;
}