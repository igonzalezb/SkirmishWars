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



class MapGraphics
{
public:
	MapGraphics();
	~MapGraphics();
	void showMap(Game* gameInfo);
	void loadBitmaps(Map *map);
	void setDisplayName(string _name);
	//void setMap(Map *map);
	void showDice(int _dice);
	ALLEGRO_DISPLAY* getDisplay();

	eventCode dispatchClick(int x, int y, Game *gameInfo);

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *displayIcon = NULL;
	ALLEGRO_BITMAP *bitmapArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *unitsArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *attackButton = NULL;
	ALLEGRO_BITMAP *purchaseButton = NULL;
	ALLEGRO_BITMAP *passButton = NULL;
	ALLEGRO_BITMAP *diceFace = NULL;

	ALLEGRO_FONT *menuFont = NULL;

};