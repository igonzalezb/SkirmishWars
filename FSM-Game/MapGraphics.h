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

#define M_HEIGHT	al_get_display_height(display)
#define M_WIDTH		(al_get_display_width(display)*3.0/4.0)
#define R_WIDTH		al_get_display_width(display)/4.0
#define T_HEIGHT	M_HEIGHT/FILA
#define T_WIDTH		M_WIDTH/COLUMNA
#define FOG_IMAGE	"resources/images/fog.png"
#define FONT_MENU	"resources/BAUHS93.otf"

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