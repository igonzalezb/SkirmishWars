#include <iostream>
#include "StartMenu.h"

#include <string>
using namespace std;
#define MAX_NAME_LEN	30




typedef enum BoxNumber
{
	IP_BOX, NAME_BOX

};


ALLEGRO_DISPLAY* display2 = NULL;
string ip, name, maxIp;

bool redraw, do_exit;

BoxNumber box;

void dispacherIpNameMenu(ALLEGRO_EVENT ev);
void printIpNameMenu();

ALLEGRO_FONT *font;

int main (void)
{	
	//StartMenu mainMenu;
	//mainMenu.openApp();
	if (allegroStartup())
	{
		fprintf(stderr, "Failed to Start Allegro Configs!\n");
	}
	
	ALLEGRO_EVENT_QUEUE *queue = NULL;

	box = IP_BOX;

	queue = al_create_event_queue();
	display2 = al_create_display(800, 400);
	font = al_load_font(FONT_MENU, 30, 0);
	if (!font) {
		fprintf(stderr, "failed to create Font!\n");
	}
	al_clear_to_color(al_color_name("blue"));

	maxIp = "192.168.000.000";
	
	
	printIpNameMenu();


	redraw = false;
	do_exit = false;

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display2));

	while (!do_exit)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(queue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_KEY_CHAR:
			dispacherIpNameMenu(ev);
			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(display2);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			do_exit = true;
			break;
		}

		if (redraw)
		{
			printIpNameMenu();
		}

	}



	al_flip_display();



/////////////////ALLEGRO NATIVE DIALOGS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*ALLEGRO_MESSAGEBOX_WARN
		The message is a warning.This may cause a different icon(or other effects).
	ALLEGRO_MESSAGEBOX_ERROR
		The message is an error.
	ALLEGRO_MESSAGEBOX_QUESTION
		The message is a question.
	ALLEGRO_MESSAGEBOX_OK_CANCEL
		Instead of the "OK" button also display a cancel button.Ignored if buttons is not NULL.
	ALLEGRO_MESSAGEBOX_YES_NO
		Instead of the "OK" button display Yes / No buttons.Ignored if buttons is not NULL.*/
	//0 if the dialog window was closed without activating a button.
	//1 if the OK or Yes button was pressed.
	////2 if the Cancel or No button was pressed.
	/*int button = al_show_native_message_box(
		display2,
		"GAME OVER",
		"Do you want to continue playing?",
		"Click  \"Yes\" for restarting the game.\n"
		"Click  \"No\" for main menu.",
		NULL,
		ALLEGRO_MESSAGEBOX_YES_NO
	);*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		
	al_rest(1.0);

	return EXIT_SUCCESS;
}



void dispacherIpNameMenu(ALLEGRO_EVENT ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_ESCAPE:
		do_exit = true;
		break;
	case ALLEGRO_KEY_BACKSPACE:
		if (box == IP_BOX)
		{
			if (ip.size() > 0) {
				ip.pop_back();
				redraw = true;
			}
		}
		else if (box == NAME_BOX)
		{
			if (name.size() > 0) {
				name.pop_back();
				redraw = true;
			}
		}
		break;
	case ALLEGRO_KEY_ENTER: case ALLEGRO_KEY_PAD_ENTER:
		if (box == IP_BOX)
		{
			redraw = true;
			box = NAME_BOX;
		}
		else if (box == NAME_BOX)
		{
			redraw = true;
			do_exit = true;
		}
		break;
	default:
		if ((ev.keyboard.unichar >= 32) && (ev.keyboard.unichar <= 122))
		{
			if (box == IP_BOX)
			{
				ip += ev.keyboard.unichar;
			}
			else if (box == NAME_BOX)
			{
				name += ev.keyboard.unichar;
			}
			redraw = true;
		}
		break;
	}
	if ((box == IP_BOX) && (ip.size() >= maxIp.size()))
	{
		box = NAME_BOX;
	}
	else if ((box == NAME_BOX) && (name.size() >= MAX_NAME_LEN))
	{
		do_exit = true;
	}

}

void printIpNameMenu()
{
	al_clear_to_color(al_color_name("blue"));

	al_draw_text(font, al_color_name("white"), 0.0, 0.0, 0.0, "Insert Partners IP: ");
	al_draw_rectangle(5.0, al_get_font_line_height(font), al_get_text_width(font, maxIp.c_str()) + 15.0, al_get_font_line_height(font) * 2, al_color_name("white"), 5.0);
	al_draw_text(font, al_color_name("white"), 10.0, al_get_font_line_height(font), 0.0, ip.c_str());

	al_draw_text(font, al_color_name("white"), 0.0, al_get_font_line_height(font) * 3, 0.0, "Insert Name: ");
	al_draw_rectangle(5.0, al_get_font_line_height(font) * 4, al_get_text_width(font, "A") * MAX_NAME_LEN, al_get_font_line_height(font) * 5, al_color_name("white"), 5.0);
	al_draw_text(font, al_color_name("white"), 10.0, al_get_font_line_height(font) * 4, 0.0, name.c_str());
	al_flip_display();
	redraw = false;
}