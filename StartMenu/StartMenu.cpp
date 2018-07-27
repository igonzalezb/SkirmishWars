#include "StartMenu.h"

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
	al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);	//ACORDARSE DE ACTIVAR!!!

	menuImage = al_load_bitmap(MENU_IMAGE_PATH);
	if (!menuImage)
	{
		fprintf(stderr, "failed to create display!\n");
	}

	event_queue1 = al_create_event_queue();
	if (!event_queue1) {
		fprintf(stderr, "failed to create event_quieue1!\n");
	}

	menuFont = al_load_font(FONT_MENU, 75, 0);
	if(!menuFont){
		fprintf(stderr, "failed to create menuFont!\n");
	}
}

void StartMenu::openApp()
{
	sw_v = new video(VIDEO_PATH);
	sw_v->playVideo(display);
	
	updateMenu();

	MenuEvents();

	dispachOption();
}

void StartMenu::MenuEvents()
{
	bool redraw = false, do_exit = false;
	
	al_register_event_source(event_queue1, al_get_display_event_source(display));
	al_register_event_source(event_queue1, al_get_keyboard_event_source());
	al_register_event_source(event_queue1, al_get_mouse_event_source());

	while (!do_exit)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue1, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if(ev.mouse.button == 1)		//Para usar solo el click izquierdo
			{
				optionClicked = dispachClick(ev.mouse.x, ev.mouse.y);
				if(optionClicked < MAX_OPTIONS)
					do_exit = true;

			}
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			dispachMovement(ev.mouse.x, ev.mouse.y);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				do_exit = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: 			
			do_exit = true;
			break;
		}

	}

}

int StartMenu::dispachClick(int x, int y)
{
	int bbx, bby, bbw, bbh;
	int click = MAX_OPTIONS + 1;
#ifdef DEBUG
	printf("x:%d y:%d\n", x, y);
#endif // DEBUG


	for (int i = 0, j = 0; i< MAX_OPTIONS; i++, j += 100.0)
	{
		al_get_text_dimensions(menuFont, Option[i], &bbx, &bby, &bbw, &bbh);
		
#ifdef DEBUG
		printf(Option[i]);
#endif // DEBUG

		bbx += 20;
		bbw += 20;
		bby += (al_get_display_height(display) / 2.5) + j;
		bbh += (al_get_display_height(display) / 2.5) + j;

		if ((x >= bbx && x <= bbw) && (y >= bby && y <= bbh))
		{
#ifdef DEBUG
			printf("Click Correcto - Opcion: %s\n", Option[i]);
#endif // DEBUG

			click = i;
		}
	}
	return click;
	
}

void StartMenu::dispachMovement(int x, int y)
{
	int bbx, bby, bbw, bbh;
	for (int i = 0, j = 0; i< MAX_OPTIONS; i++, j += 100.0)
	{
		al_get_text_dimensions(menuFont, Option[i], &bbx, &bby, &bbw, &bbh);
		bbx += 20;
		bbw += 20;
		bby += (al_get_display_height(display) / 2.5) + j;
		bbh += (al_get_display_height(display) / 2.5) + j;

		if ((x >= bbx && x <= bbw) && (y >= bby && y <= bbh))
		{
#ifdef DEBUG
			printf("Move - Opcion: %s\n", Option[i]);
#endif // DEBUG

			al_draw_text(menuFont, al_map_rgb(FONT_COLOR_2), 20.0, (al_get_display_height(display) / 2.5) + j, 0.0, Option[i]);
			
		}
		else
			al_draw_text(menuFont, al_map_rgb(FONT_COLOR_1), 20.0, (al_get_display_height(display) / 2.5) + j, 0.0, Option[i]);
		al_flip_display();
	}
}

void StartMenu::updateMenu()
{
	al_clear_to_color(al_map_rgb(BACKGROUND_COLOR));

	al_draw_scaled_bitmap(menuImage, 0.0, 0.0,
		al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage), 0.0,0.0,
		al_get_display_width(display), al_get_display_height(display), 0);

	for (int i=0, j=0; i< MAX_OPTIONS; i++, j+=100.0)
		al_draw_text(menuFont, al_map_rgb(FONT_COLOR_1), 20.0, (al_get_display_height(display) / 2.5) + j, 0.0, Option[i]);

	al_flip_display();
}

void StartMenu::dispachOption()		//HAY QUE SACAR LOS TEXT Y PONER QUE HAGA LAS ACCIONES
{
	switch (optionClicked)
	{
	case START_NEW_GAME:
		al_clear_to_color(al_map_rgb(0,0,0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Starting Game...");
		break;

	case SETTINGS:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Settings...");
		break;
	case CREDITS:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Credits...");
		break;
	case QUIT_GAME:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Quitting Game...");
		break;
	}

	al_flip_display();
	al_rest(3.0);
}


StartMenu::~StartMenu()
{
	delete sw_v;
	al_destroy_display(display);
	al_destroy_bitmap(menuImage);
	al_destroy_font(menuFont);
	al_destroy_event_queue(event_queue1);

	allegroShutdown();
}