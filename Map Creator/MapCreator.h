#pragma once

#include <iostream>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include "Terrain.h"

class MapCreator
{
public:
	MapCreator() 
	{ 
		display = al_create_display(600, 600);
		if(!display)
		{
			printf("Failed to create display!\n");
			throw std::invalid_argument("Failed to create display!\n");
		}

	}
	~MapCreator() { ; }

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *terrArray[28];
	std::vector<Terrain> terrMatrix;


};