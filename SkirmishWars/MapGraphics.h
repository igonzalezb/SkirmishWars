#pragma once

#include <iostream>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include "Map.h"


#define TILEHEIGHT	al_get_display_height(display)/FILAS
#define TILEWITH	al_get_display_width(display)/COLUMNAS


class MapGraphics
{
public:
	MapGraphics();
	~MapGraphics() { ; }
	bool showMap();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *tilesArray[28];

	Map *map;

};