#include "MapGraphics.h"

MapGraphics::MapGraphics()
{
	display = al_create_display(600, 600);
	if (!display)
	{
		printf("Failed to create display!\n");
		throw std::invalid_argument("Failed to create display!\n");
	}
	
}

bool MapGraphics::showMap()
{

	return false;
}
