#include "userInput.h"


userInput::userInput()
{
}

userInput::~userInput()
{
}

void userInput::userEvents()
{
	//bool redraw = false, do_exit = false;

	//al_register_event_source(event_queue, al_get_display_event_source(display));
	//al_register_event_source(event_queue, al_get_keyboard_event_source());
	//al_register_event_source(event_queue, al_get_mouse_event_source());

	//while (!do_exit)
	//{
	//	ALLEGRO_EVENT ev;

	//	//al_wait_for_event(event_queue, &ev);
	//	al_get_next_event(event_queue, &ev);

	//	switch (ev.type)
	//	{
	//	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
	//		if (ev.mouse.button == 1)		//Para usar solo el click izquierdo
	//		{
	//			optionClicked = dispachClick(ev.mouse.x, ev.mouse.y);
	//			if (optionClicked < MAX_OPTIONS)
	//				do_exit = true;

	//		}
	//		break;
	//	case ALLEGRO_EVENT_MOUSE_AXES:
	//		//dispachMovement(ev.mouse.x, ev.mouse.y);
	//		break;
	//	case ALLEGRO_EVENT_KEY_UP:
	//		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
	//			do_exit = true;
	//		}
	//		break;
	//	case ALLEGRO_EVENT_DISPLAY_CLOSE:
	//		do_exit = true;
	//		evCode = QUIT;
	//		break;
	//	}

	//}

}
