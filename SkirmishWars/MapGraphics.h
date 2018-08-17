#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>

#include "Map.h"


#define T_HEIGHT	al_get_display_height(display)/FILA
#define T_WIDTH		al_get_display_width(display)/COLUMNA
#define FOG_IMAGE	"resources/images/fog.png"


#define NOFOG	//Just for Debug

class MapGraphics
{
public:
	MapGraphics();
	~MapGraphics();
	void showMap(Map * map);
	void loadBitmaps(Map *map);
	//void setMap(Map *map);

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *bitmapArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *unitsArray[FILA][COLUMNA];
	//Map *map;

};