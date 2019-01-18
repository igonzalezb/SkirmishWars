#pragma once

#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro5.h>

class userInput
{
public:
	userInput();
	~userInput();
	void userEvents();

private:
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
};

