#pragma once

#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class MapCreator
{
public:
	MapCreator();
	~MapCreator();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *terrArray[12][16];
};