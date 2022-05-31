#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "GLOBALS.h"
#include "rendering.h"
#include "structures.h"
#include "knightTour.h"


//Cale polecenie projektu

int main(int argc, char **argv){
	//Inicjalizacja
	if(!al_init()) return -1;
	if(!al_init_image_addon()) return -1;
	if(!al_init_primitives_addon()) return -1;
	if(!al_install_mouse()) return -1;

	if (argc == 1) {
		boardSize = 8;
	}
	else {
		boardSize = atoi(argv[1]);
	}
	displayWidth = 1000;
	displayHeight = 1000;
	ALLEGRO_DISPLAY* display = al_create_display(displayWidth, displayHeight);

	ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	ALLEGRO_EVENT event;

	int running = 1;

	render_chessboard();
	al_flip_display();

	al_install_keyboard();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	while (running) {

		while (al_get_next_event(eventQueue, &event)) {

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = 0;
			}

			else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				int mx = event.mouse.x * boardSize / displayWidth;
				int my = event.mouse.y * boardSize / displayHeight;
				initKnightTour(mx + my * boardSize);
			}

			/*
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				ALLEGRO_KEYBOARD_STATE keyboardState;
				al_get_keyboard_state(&keyboardState);
				if (al_key_down(&keyboardState, ALLEGRO_KEY_SPACE)) {
					stepKnightTour();
					printf("Step\n");
				}
			}*/

		}

		stepKnightTour();
	}

	delKnightTour();
	al_destroy_event_queue(eventQueue);
	al_uninstall_mouse();
	al_destroy_display(display);
	return 0;
}