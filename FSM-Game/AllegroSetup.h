#pragma once
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_video.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_color.h>

/////////////////////////////////////////////////////////////////////////////////////
//		ALLEGRO STARTUP
//	Inicializa allegro y los addons. Devuelve true si hubo error
////////////////////////////////////////////////////////////////////////////////////
bool allegroStartup(void);


/////////////////////////////////////////////////////////////////////////////////////
//		ALLEGRO SHUTDOWN
//	Apaga allegro y los addons
////////////////////////////////////////////////////////////////////////////////////
void allegroShutdown(void);