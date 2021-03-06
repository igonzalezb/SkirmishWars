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
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include "Resources.h"
#include "Map.h"

#define RESERVED_SAMPLES   6

class MapGraphics
{
public:
	MapGraphics();
	MapGraphics(ALLEGRO_DISPLAY *display);
	~MapGraphics();
	void showMap(Resources* data, Map* myMap, int player_money, TeamNumber my_team, unsigned int time);
	void loadBitmaps(Map *map);
	void setDisplayName(string _name);
	void showDice(int _dice);
	void playTenSecSound();
	void playThirtySecSound();
	void playOneMinSound();
	void playGameOverSound();
	ALLEGRO_DISPLAY* getDisplay();
	bool doIwantToPlayAgain();
	void setPurchaseWarningShown(bool a);
	void setAttackWarningShown(bool a);
	bool wasPurchaseWarningShown();
	bool wasAttackWarningShown();

	ALLEGRO_FONT* getMenuFont();
	void setBackgroundMusicOnOff(bool a);
	bool getBackgroundMusicOnOff();
	void setSoundEffectsOnOff(bool a);
	void setWarningsOnOff(bool a);
	bool getWarningsOnOff();

	ALLEGRO_SAMPLE* getBackgroundSample();


private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *bitmapArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *unitsArray[FILA][COLUMNA];
	ALLEGRO_BITMAP *attackButton = NULL;
	ALLEGRO_BITMAP *purchaseButton = NULL;
	ALLEGRO_BITMAP *passButton = NULL;
	ALLEGRO_BITMAP *diceFace = NULL;
	ALLEGRO_FONT *hpFont = NULL;
	ALLEGRO_FONT *menuFont = NULL;
	ALLEGRO_SAMPLE *beep = NULL;
	ALLEGRO_SAMPLE *gameover = NULL;
	ALLEGRO_SAMPLE *backgroundMusic = NULL;
	bool purchaseWarningShown;
	bool attackWarningShown;

	bool warningsOnOff;
	bool backgroundMusicOnOff;
	bool soundEffectsOnOff;
};