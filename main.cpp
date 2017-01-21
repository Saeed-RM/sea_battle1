#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BOUNCER_SIZE = 20;
enum MYKEYS {
	KEY_UP, KEY_DOWN
};




void clear_selecter(ALLEGRO_DISPLAY *display, 
	ALLEGRO_BITMAP *bouncer, 
	int bouncer_x, 
	int bouncer_y) {
	
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
	
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(0, 200, 0));
	al_set_target_bitmap(al_get_backbuffer(display));

	al_flip_display();
}
int main(int l, char **argv) {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	bool key[4] = { false, false, false, false };
	float bouncer_x = 100;
	float bouncer_y = 160;
	bool redraw = true;
	bool doexit = false;
	int selecter_state = 0; // 0-1-2 : New game - High score - Exit

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();


	timer = al_create_timer(1.0/60.0);
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	display = al_create_display(WIDTH, HEIGHT);
	event_queue = al_create_event_queue();
	font = al_load_ttf_font("arial.ttf", 25, 0);


	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(0, 200, 0));
	al_set_target_bitmap(al_get_backbuffer(display));


	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(timer);


	al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

	al_draw_text(font,
		al_map_rgb(255, 255, 0), 155, 155, 0,
		"New Game");

	al_draw_text(font,
		al_map_rgb(255, 255, 0), 155, 255, 0,
		"High Score");
	al_draw_text(font,
		al_map_rgb(255, 255, 0), 155, 355, 0,
		"Exit");

	al_flip_display();
	

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP]) {
				//printf("salam");
				clear_selecter(display, bouncer, bouncer_x, bouncer_y);
				switch (selecter_state) {
					case 0: 
						bouncer_y = 360;
						selecter_state = 2;
						break;
					
					case 1: 
						bouncer_y = 160;
						selecter_state = 0;
						break;
					
					case 2: 
						bouncer_y = 260;
						selecter_state = 1;
						break;
					
				}

				key[KEY_UP] = false;
			}

			if (key[KEY_DOWN]) {
				clear_selecter(display, bouncer, bouncer_x, bouncer_y);
				
				switch (selecter_state) {
					case 0: 
						bouncer_y = 260;
						selecter_state = 1;
						break;
					
					case 1: 
						bouncer_y = 360;
						selecter_state = 2;
						break;
					
					case 2: 
						bouncer_y = 160;
						selecter_state = 0;
						break;
					
				}

				key[KEY_DOWN] = false;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			//al_clear_to_color(al_map_rgb(0, 0, 0));


			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

			al_flip_display();
		}
	}


}