#pragma once
#include <iostream>
#include "AllegroSetup.h"
#include "videoplayer.h"

#define DISPLAY_WIDTH		800
#define DISPLAY_HEIGHT		600
#define VIDEO_PATH		"Advance Wars.ogv"
#define MENU_IMAGE_PATH		"banner.png"

class StartMenu
{
public:
	void openGame();
	StartMenu();
	~StartMenu();

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_BITMAP *menuImage;
	video* sw_v;
};

inline void StartMenu::openGame()
{
	sw_v = new video(VIDEO_PATH);
	sw_v->playVideo(display);
	al_clear_to_color(al_map_rgb(146, 132, 247));

	al_draw_scaled_bitmap(menuImage, 0.0, 0.0,
		al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage),
		(al_get_display_width(display)/2) - (DISPLAY_WIDTH /2),
		(al_get_display_height(display) / 2) - (DISPLAY_HEIGHT /2),
		DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);

	al_flip_display();
	al_rest(3.0);
}

StartMenu::StartMenu()
{
	if (allegroStartup())
	{
		fprintf(stderr, "Failed to Start Allegro Configs!\n");
	}
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
	}

	menuImage = al_load_bitmap(MENU_IMAGE_PATH);
	if (!menuImage)
	{
		fprintf(stderr, "failed to create display!\n");
	}
	
	
}

StartMenu::~StartMenu()
{
	delete sw_v;
	al_destroy_display(display);
	allegroShutdown();
}