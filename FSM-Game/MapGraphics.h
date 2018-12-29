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
#include "genericEvent.h"

#define NOFOG	//Just for Debug

class MapGraphics
{
public:
	MapGraphics();
	~MapGraphics();
	void showMap(Map * map);
	void loadBitmaps(Map *map);
	//void setMap(Map *map);

	ALLEGRO_DISPLAY* getDisplay();

	eventCode dispatchClick(int x, int y);

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *bitmapArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *unitsArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *attackButton;
	ALLEGRO_BITMAP *purchaseButton;
	ALLEGRO_FONT *menuFont;

	string purchaselist[9] = {
		"Mechs: $3",
		"Infantry: $1",
		"Rocket: $15",
		"Recon: $4",
		"APC: $5",
		"AntiAir: $8",
		"Artillery: $6",
		"Tank: $7",
		"MedTank: $16" };
	//Map *map;

};