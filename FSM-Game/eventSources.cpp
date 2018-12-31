#include "eventSources.h"
//#include "Screen.h"
#include "Events.h"
//#include <boost\algorithm\string\classification.hpp>
//#include <boost\algorithm\string\split.hpp>
//#include <boost\date_time\posix_time\posix_time.hpp>
using namespace std;

//CAMBIAAAAAAAAAAAR TODO ESTE ARCHIVO ADAPTANDO PARA EL GAAAAAMEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*****  GAME EVENT SOURCE  *****/


GameEventSource::GameEventSource(Game *_gameInterface)
{

}


genericEvent * GameEventSource::insertEvent()
{
	genericEvent * ret;
	
	//COMPLETAR
}

bool GameEventSource::isThereEvent()
{
	//COMPLETAR
}


UserEventSource::UserEventSource()
{
	graphics = new MapGraphics;
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_quieue!\n");
	}
}

bool UserEventSource::isThereEvent()
{
	bool redraw = false;
	bool ret = false;

	al_register_event_source(event_queue, al_get_display_event_source(graphics->getDisplay()));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	if (al_is_event_queue_empty(event_queue))
	{
		ret = false;
	}
	else
	{
		ALLEGRO_EVENT ev;

		//al_wait_for_event(event_queue, &ev);
		al_get_next_event(event_queue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if (ev.mouse.button == 1)		//Para usar solo el click izquierdo
			{
				evCode = dispachClick(ev.mouse.x, ev.mouse.y);

				if (evCode == NO_EV)	//RET?????? VER!
					ret = false;
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				evCode = QUIT;
				ret = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			evCode = QUIT;
			ret = true;
			break;
		default:
			ret = false;
			break;
		}


	}

	return ret;

}

eventCode UserEventSource::dispachClick(int x, int y)
{
	
}


genericEvent * UserEventSource::insertEvent()
{
	genericEvent * ret;

	//COMPLETAR
}


/*
UserEventSource::UserEventSource()
{
}

bool UserEventSource::isThereEvent()
{

}

genericEvent * UserEventSource::insertEvent()
{

}
*/