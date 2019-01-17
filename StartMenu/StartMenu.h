#pragma once
#include <iostream>
#include "AllegroSetup.h"
#include "videoplayer.h"

#define DISPLAY_WIDTH		1000
#define DISPLAY_HEIGHT		600
#define VIDEO_PATH		"Advance Wars.ogv"
#define MENU_IMAGE_PATH		"banner.png"
#define FONT_MENU		"BAUHS93.TTF"

#define MAX_OPTIONS	4
#define OPTION_1	"Start New Game"
#define OPTION_2	"Settings"
#define OPTION_3	"Credits"
#define OPTION_4	"Quit Game"

#define BACKGROUND_COLOR	146, 132, 247
#define FONT_COLOR_1		0, 0, 0
#define FONT_COLOR_2		70, 50, 90

enum OPTIONS
{
	START_NEW_GAME, SETTINGS, CREDITS, QUIT_GAME
};

class StartMenu
{
public:
	void openApp();
	void MenuEvents();
	int dispachClick(int x, int y);
	void dispachMovement(int x, int y);
	void updateMenu();
	void dispachOption();
	StartMenu();
	~StartMenu();

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *menuImage;
	ALLEGRO_EVENT_QUEUE *event_queue1;
	ALLEGRO_FONT *menuFont;
	video* sw_v;
	const char *Option[MAX_OPTIONS] = { OPTION_1, OPTION_2, OPTION_3, OPTION_4 };
	int optionClicked;
};
