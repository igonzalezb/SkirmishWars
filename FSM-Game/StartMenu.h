#pragma once
#include <iostream>
#include <string>
#include "AllegroSetup.h"
#include "videoplayer.h"

using namespace std;




#define DISPLAY_WIDTH		1000
#define DISPLAY_HEIGHT		600
#define VIDEO_PATH		"resources/videos/Advance Wars.ogv"
#define MENU_IMAGE_PATH		"resources/images/banner.png"
#define FONT_MENU		"resources/fonts/BAUHS93.TTF"
#define POINTER			"resources/images/pointer.png"

#define MAX_OPTIONS		4
#define OPTION_1		"Start New Game"
#define OPTION_2		"Settings"
#define OPTION_3		"Credits"
#define OPTION_4		"Quit Game"

#define BACKGROUND_COLOR	146, 132, 247
#define FONT_COLOR_1		0, 0, 0
#define FONT_COLOR_2		70, 50, 90

#define MAX_NAME_LEN		30


enum OPTIONS
{
	START_NEW_GAME, SETTINGS, CREDITS, QUIT_GAME
};

typedef enum BoxNumber
{
	IP_BOX, NAME_BOX

};

class StartMenu
{
public:
	StartMenu();
	~StartMenu();
	void openApp();
	void MenuEvents();
	int dispatchClick(int x, int y);
	void dispatchMovement(int x, int y);
	void updateMenuDisplay();
	void dispatchOption();
	ALLEGRO_DISPLAY* getDisplay();

	void dispatcherIpNameMenu(ALLEGRO_EVENT ev);
	void printIpNameMenu();
	void printSettings();
	void dispatcherSettings(int x, int y);
	string getUserIP();
	string getUserName();

	bool getBackgroundMusicOnOff();
	bool getSoundEffectsOnOff();
	bool getWarningsOnOff();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *menuImage = NULL;
	ALLEGRO_BITMAP *pointer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue1 = NULL;;
	ALLEGRO_BITMAP *displayIcon = NULL;
	ALLEGRO_FONT *menuFont = NULL;;
	ALLEGRO_EVENT ev;
	video* sw_v;
	const char *Option[MAX_OPTIONS] = { OPTION_1, OPTION_2, OPTION_3, OPTION_4 };
	int optionClicked;

	string userIp;
	string userName;
	string maxLenIp;

	bool redraw;
	bool do_exit;
	bool onIpNameInput;
	bool onSettings;

	bool backgroundMusic;
	bool sounds;
	bool warnings;
	BoxNumber boxInput;


};
