#include "StartMenu.h"

StartMenu::StartMenu()
{
	//ALLEGRO_MONITOR_INFO info;
	//al_get_monitor_info(0, &info);
	//printf("%i x %i", info.x2 - info.x1, info.y2 - info.y1);

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	//display = al_create_display(info.x2 - info.x1, info.y2 - info.y1);
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
	}

	al_set_window_title(display, "SKIRMISH WARS");
	//al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);	//ACORDARSE DE ACTIVAR!!!
	displayIcon = al_load_bitmap("resources/images/icon.png");
	if (!displayIcon)
	{
		printf("Failed to create displayIcon!\n");
	}
	al_set_display_icon(display, displayIcon);


	menuImage = al_load_bitmap(MENU_IMAGE_PATH);
	if (!menuImage)
	{
		fprintf(stderr, "failed to create display!\n");
	}

	event_queue1 = al_create_event_queue();
	if (!event_queue1) {
		fprintf(stderr, "failed to create event_quieue1!\n");
	}

	menuFont = al_load_font(FONT_MENU, 50, 0);
	if(!menuFont){
		fprintf(stderr, "failed to create menuFont!\n");
	}
	onIpNameInput = false;
	redraw = false;
	do_exit = false;
	boxInput = IP_BOX;
	maxLenIp = "000.000.000.000";

}

void StartMenu::openApp()
{
	sw_v = new video(VIDEO_PATH);
	sw_v->playVideo(display);
	
	onIpNameInput = false;
	redraw = false;
	do_exit = false;
	boxInput = IP_BOX;

	updateMenuDisplay();

	MenuEvents();

	
}

void StartMenu::MenuEvents()
{
	al_register_event_source(event_queue1, al_get_display_event_source(display));
	al_register_event_source(event_queue1, al_get_keyboard_event_source());
	al_register_event_source(event_queue1, al_get_mouse_event_source());

	while (!do_exit)
	{
		al_wait_for_event(event_queue1, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (!onIpNameInput)
			{
				if (ev.mouse.button == 1)		//Para usar solo el click izquierdo
				{
					optionClicked = dispachClick(ev.mouse.x, ev.mouse.y);
					dispachOption();
				}
			}
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			if (!onIpNameInput)
				dispachMovement(ev.mouse.x, ev.mouse.y);
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(display);
			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			if (1 == al_show_native_message_box(
				display,
				"Warning",
				"Are you sure you want to quit the game?",
				"", NULL, ALLEGRO_MESSAGEBOX_YES_NO))
			{
				do_exit = true;
			}
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			if (onIpNameInput) {
				dispacherIpNameMenu(ev);
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				do_exit = true;
			}
			break;
		}
		if (redraw)
		{
			if (onIpNameInput)
				printIpNameMenu();
			else
				updateMenuDisplay();
			redraw = false;
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


	for (int i = 0; i< MAX_OPTIONS; i++)
	{
		al_get_text_dimensions(menuFont, Option[i], &bbx, &bby, &bbw, &bbh);
		
#ifdef DEBUG
		printf(Option[i]);
#endif // DEBUG

		bbx += 15;
		bbw += 20;
		bby += (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont));
		bbh += (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont));

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
	for (int i = 0; i< MAX_OPTIONS; i++)
	{
		al_get_text_dimensions(menuFont, Option[i], &bbx, &bby, &bbw, &bbh);
		bbx += 20;
		bbw += 20;
		bby += (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont));
		bbh += (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont));

		if ((x >= bbx && x <= bbw) && (y >= bby && y <= bbh))
		{
#ifdef DEBUG
			printf("Move - Opcion: %s\n", Option[i]);
#endif // DEBUG

			al_draw_text(menuFont, al_map_rgb(FONT_COLOR_2), 20.0, (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont)), 0.0, Option[i]);
			
		}
		else
			al_draw_text(menuFont, al_map_rgb(FONT_COLOR_1), 20.0, (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont)), 0.0, Option[i]);
		al_flip_display();
	}
}

void StartMenu::updateMenuDisplay()
{
	redraw = false;
	al_clear_to_color(al_map_rgb(BACKGROUND_COLOR));

	al_draw_scaled_bitmap(menuImage, 0.0, 0.0,
		al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage), 0.0,0.0,
		al_get_display_width(display), al_get_display_height(display), 0);

	for (int i=0; i< MAX_OPTIONS; i++)
		al_draw_text(menuFont, al_map_rgb(FONT_COLOR_1), 20.0, (al_get_display_height(display) / 2.5) + (i * al_get_font_line_height(menuFont)), 0.0, Option[i]);

	al_flip_display();
}

void StartMenu::dispachOption()		//HAY QUE SACAR LOS TEXT Y PONER QUE HAGA LAS ACCIONES
{
	switch (optionClicked)
	{
	case START_NEW_GAME:
		redraw = true;
		onIpNameInput = true;
		printIpNameMenu();
		//dispacherIpNameMenu(ev);
		break;
	case SETTINGS:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Settings...");
		redraw = true;
		break;
	case CREDITS:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(menuFont, al_map_rgb(100, 100, 100), 0.0, 0.0, 0.0, "Credits...");
		redraw = true;
		break;
	case QUIT_GAME:
		al_clear_to_color(al_map_rgb(0, 0, 0));
		do_exit = true;
		redraw = false;
		exit(EXIT_SUCCESS);		//HACERLO LINDO
		break;
	}

	al_flip_display();
	
}

ALLEGRO_DISPLAY * StartMenu::getDisplay()
{
	return display;
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

void StartMenu::dispacherIpNameMenu(ALLEGRO_EVENT ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_ESCAPE:
		onIpNameInput = false;
		boxInput = IP_BOX;
		redraw = true;
		break;
	case ALLEGRO_KEY_BACKSPACE:
		if (boxInput == IP_BOX)
		{
			if (userIp.size() > 0) {
				userIp.pop_back();
				redraw = true;
			}
		}
		else if (boxInput == NAME_BOX)
		{
			if (userName.size() > 0) {
				userName.pop_back();
				redraw = true;
			}
		}
		break;
	case ALLEGRO_KEY_ENTER: case ALLEGRO_KEY_PAD_ENTER:
		if (boxInput == IP_BOX)
		{
			redraw = true;
			boxInput = NAME_BOX;
		}
		else if (boxInput == NAME_BOX)
		{
			boxInput = IP_BOX;
			redraw = false;
			onIpNameInput = false;						//ACA SE TENDRIA QUE ENVIAR LOS DATOS Y SALIR DEL MENU!!!
			do_exit = true;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(menuFont, al_map_rgb(100, 100, 100),
				(al_get_display_width(display) / 2) - al_get_text_width(menuFont, "LOADING...")/2,
				(al_get_display_height(display) / 2) - al_get_font_line_height(menuFont)/2,
				0.0, "LOADING...");
			al_flip_display();
		
		}
		break;
	default:
		if ((ev.keyboard.unichar >= 32) && (ev.keyboard.unichar <= 122))
		{
			if (boxInput == IP_BOX)
			{
				userIp += ev.keyboard.unichar;
			}
			else if (boxInput == NAME_BOX)
			{
				userName += ev.keyboard.unichar;
			}
			redraw = true;
		}
		break;
	}
	if ((boxInput == IP_BOX) && (userIp.size() >= maxLenIp.size()))
	{
		boxInput = NAME_BOX;
	}
	else if ((boxInput == NAME_BOX) && (userName.size() >= MAX_NAME_LEN))
	{
		boxInput = IP_BOX;
		onIpNameInput = false;	
	}

}

void StartMenu::printIpNameMenu()
{
	al_clear_to_color(al_color_name("blue"));

	al_draw_text(menuFont, al_color_name("white"), 0.0, 0.0, 0.0, "Insert Partners IP: ");
	al_draw_rectangle(5.0, al_get_font_line_height(menuFont), al_get_text_width(menuFont, maxLenIp.c_str()) + 15.0, al_get_font_line_height(menuFont) * 2, al_color_name("white"), 5.0);
	al_draw_text(menuFont, al_color_name("white"), 10.0, al_get_font_line_height(menuFont), 0.0, userIp.c_str());

	al_draw_text(menuFont, al_color_name("white"), 0.0, al_get_font_line_height(menuFont) * 3, 0.0, "Insert Name: ");
	al_draw_rectangle(5.0, al_get_font_line_height(menuFont) * 4, al_get_text_width(menuFont, "A") * MAX_NAME_LEN, al_get_font_line_height(menuFont) * 5, al_color_name("white"), 5.0);
	al_draw_text(menuFont, al_color_name("white"), 10.0, al_get_font_line_height(menuFont) * 4, 0.0, userName.c_str());
	al_flip_display();
	redraw = false;
}

string StartMenu::getUserIP()
{
	return userIp;
}

string StartMenu::getUserName()
{
	return userName;
}