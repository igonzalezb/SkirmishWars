#include "AllegroSetup.h"

/////////////////////////////////////////////////////////////////////////////////////
//		ALLEGRO STARTUP
//	Inicializa allegro y los addons. Devuelve true si hubo error
////////////////////////////////////////////////////////////////////////////////////
bool allegroStartup(void)
{
	if (al_init())
	{
		if (al_init_primitives_addon())
		{
			if (al_install_keyboard())
			{
				if (al_install_mouse())
				{
					if (al_init_image_addon())
					{
						al_init_font_addon();   //Void

						if (al_init_ttf_addon())
						{
							if (al_init_video_addon())
							{
								if (al_install_audio())
								{
									if (al_init_acodec_addon())
									{
										return EXIT_SUCCESS;
									}
									else
										printf("Unable to start audiocodec addon \n");
										
								}
								else
									printf("Unable to start audio addon \n");
								//al_shutdown_video_addon();
							}
							else
								printf("Unable to start image addon \n");
							al_shutdown_ttf_addon();
						}
						else
							printf("ERROR: Failed to initialize ttf addon\n");
						al_shutdown_font_addon();
						al_shutdown_image_addon();
					}
					else
						printf("ERROR: Failed to initialize image addon\n");
					al_uninstall_mouse();
				}
				else
					printf("ERROR: Failed to install mouse\n");
				al_uninstall_keyboard();
			}
			else
				printf("ERROR: Failed to install keyboard\n");
			al_shutdown_primitives_addon();
		}
		else
			printf("ERROR: Failed to load primitives addon \n");
		al_uninstall_system();
	}
	else
		printf("ERROR: Failed to initialize allegro system\n");

	return EXIT_FAILURE;
}


/////////////////////////////////////////////////////////////////////////////////////
//		ALLEGRO SHUTDOWN
//	Apaga allegro y los addons
////////////////////////////////////////////////////////////////////////////////////
void allegroShutdown(void)
{
	//al_shutdown_video_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_audio();
	al_shutdown_primitives_addon();
	al_uninstall_system();
}