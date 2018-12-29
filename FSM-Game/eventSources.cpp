#include "eventSources.h"
//#include "Screen.h"
#include "Events.h"
//#include <boost\algorithm\string\classification.hpp>
//#include <boost\algorithm\string\split.hpp>
//#include <boost\date_time\posix_time\posix_time.hpp>
using namespace std;

//CAMBIAAAAAAAAAAAR TODO ESTE ARCHIVO ADAPTANDO PARA EL GAAAAAMEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	bool redraw = false;
	bool ret = false;

	al_register_event_source(event_queue, al_get_display_event_source(display));
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

				/*if (optionClicked < MAX_OPTIONS)
				do_exit = true;*/

			}
			break;
			/*case ALLEGRO_EVENT_MOUSE_AXES:
			dispachMovement(ev.mouse.x, ev.mouse.y);
			break;*/
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

eventCode GameEventSource::dispachClick(int x, int y)
{
	



	return eventCode();
}









//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

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