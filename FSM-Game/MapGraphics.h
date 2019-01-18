#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>

#include "Map.h"
#include "genericEvent.h"
#include "Game.h"

#define NOFOG	//Just for Debug

class MapGraphics
{
public:
	MapGraphics();
	~MapGraphics();
	void showMap(Game* gameInfo);
	void loadBitmaps(Map *map);
	//void setMap(Map *map);

	ALLEGRO_DISPLAY* getDisplay();

	eventCode dispatchClick(int x, int y, Game *gameInfo);

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *bitmapArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *unitsArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *attackButton;
	ALLEGRO_BITMAP *purchaseButton;
	ALLEGRO_BITMAP *passButton;
	ALLEGRO_FONT *menuFont;

};