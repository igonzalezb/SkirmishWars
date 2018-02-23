#include <iostream>
#include "AllegroSetup.h"
#include "videoplayer.h"

#define VIDEO_PATH	"Advance Wars.ogv"

int main (void)
{
	ALLEGRO_DISPLAY *display = NULL;
//=============================================================================================================================================	
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	display = al_create_display(1000, 650);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		allegroShutdown();
		return EXIT_FAILURE;
	}	
//=============================================================================================================================================	

	video* sw_v = new video(VIDEO_PATH);
	sw_v->playVideo(display);
	delete sw_v;




	al_destroy_display(display);
	allegroShutdown();
	
	return EXIT_SUCCESS;
}