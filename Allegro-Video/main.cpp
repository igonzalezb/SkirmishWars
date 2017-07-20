#include <iostream>

#include "video.h"

#define VIDEO_PATH	"Advance Wars.ogv"

int main (void)
{
	ALLEGRO_DISPLAY *display = NULL;
	
//=============================================================================================================================================
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_video_addon())
	{
		fprintf(stderr, "Unable to start image addon \n");
		al_uninstall_system();
		return -1;
	}

	if (!al_install_audio())
	{
		fprintf(stderr, "Unable to start audio addon \n");
		al_uninstall_system();
		return -1;
	}
	if (!al_install_keyboard())
	{
		fprintf(stderr, "Unable to start audio addon \n");
		al_uninstall_audio();
		al_uninstall_system();
		return -1;
	}

//=============================================================================================================================================	
	
	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	display = al_create_display(1000, 650);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_uninstall_audio();
		al_uninstall_keyboard();
		al_uninstall_system();
		return -1;
	}
	
//=============================================================================================================================================	

	video* pixar = new video(VIDEO_PATH);
	pixar->playVideo(display);
	delete pixar;

	al_destroy_display(display);
	
	
	
	//al_shutdown_video_addon();
	al_uninstall_keyboard();
	al_uninstall_audio();
	al_uninstall_system();

	return EXIT_SUCCESS;
}