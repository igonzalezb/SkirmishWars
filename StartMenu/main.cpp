#include <iostream>
#include "StartMenu.h"

ALLEGRO_FONT *font;

int main (void)
{	
	if (allegroStartup())
	{
		fprintf(stderr, "Failed to Start Allegro Configs!\n");
	}

	StartMenu mainMenu;
	mainMenu.openApp();

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