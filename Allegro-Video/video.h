#pragma once

#include <iostream>

#include <allegro5\allegro5.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_video.h>

class video
{
public:
	video();
	video(char videoPath[]);
	~video();
	void playVideo(ALLEGRO_DISPLAY *_display);

private:
	ALLEGRO_BITMAP *frame;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_VIDEO * video_s;
	void printVideoFrame(ALLEGRO_DISPLAY *display);
	
};

