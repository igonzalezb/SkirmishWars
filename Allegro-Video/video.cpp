#include "video.h"


video::video() {}

video::video(char videoPath[])
{
	if (al_is_system_installed() && al_is_audio_installed())
	{
		event_queue = al_create_event_queue();
		if (!event_queue) {
			printf("Failed to create event_queue!\n");
			throw std::invalid_argument("Failed to create event_queue for video!\n");
		}

		video_s = al_open_video(videoPath);
		if (!video_s) {
			printf("Failed to open video %s\n", videoPath);
			throw std::invalid_argument("Failed to open video\n");
		}

		if (!al_reserve_samples(1))
		{
			printf("Unable to reserve samples\n");
			throw std::invalid_argument("Unable to reserve samples\n");
		}

	}

	else
	{
		printf("ERROR - Please install allegro system || audio system");
		throw std::invalid_argument("ERROR - Please install allegro system || audio system");
	}
		
}


void video::playVideo(ALLEGRO_DISPLAY *display)
{
	bool do_exit = false;

	al_register_event_source(event_queue, al_get_video_event_source(video_s));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_video(video_s, al_get_default_mixer());

	while (!do_exit)
	{
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		switch (ev.type)
		{
		case ALLEGRO_EVENT_VIDEO_FRAME_SHOW:
			printVideoFrame(display);
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(display);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: case ALLEGRO_EVENT_VIDEO_FINISHED: case ALLEGRO_EVENT_KEY_DOWN:
			al_close_video(video_s);
			do_exit = true;
			break;
		}

	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	
}

void video::printVideoFrame(ALLEGRO_DISPLAY *display)
{
	
	frame = al_get_video_frame(video_s);
	if (!frame)
		return;

	al_draw_scaled_bitmap(frame, 0.0, 0.0,
		al_get_bitmap_width(frame), al_get_bitmap_height(frame),
		0.0, 0.0, al_get_display_width(display), al_get_display_height(display), 0);
	
	al_flip_display();
}

video::~video()
{
	al_destroy_event_queue(event_queue);
}
