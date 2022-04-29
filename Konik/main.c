#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "GLOBALS.h"
#include "rendering.h"
#include "structures.h"

int main(void){
	//INICJALIZACJA
	if(!al_init()) return -1;
	if(!al_init_image_addon()) return -1;
	if(!al_init_primitives_addon()) return -1;
	if(!al_install_mouse())return -1;

	ALLEGRO_DISPLAY* display = NULL;
	displayWidth = 1000;
	displayHeight = 1000;
	display = al_create_display(displayWidth, displayHeight);

	ALLEGRO_TIMER* timer;
	timer = al_create_timer(1/100.0);

	ALLEGRO_EVENT_QUEUE* eventQueue;
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP* konikBMP = al_load_bitmap("konik.png");
	assert(konikBMP);
	ALLEGRO_COLOR tourColor = al_map_rgb(206, 45, 79);

	//INICJALIZACJA ALGORYTMU

	Stack* toVisit = stackCreate();
	Stack* sourceVisit = stackCreate();
	Stack* tour = stackCreate();
	int tab[boardSize][boardSize];
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			tab[i][j] = 0;
		}
	}
	int mx, my;

	int running = 1;

	render_chessBoard(displayWidth, displayHeight);
	al_flip_display();
	
	int pruby = 1;
	int cofanie = 0;

	while(running){
		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);
		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			running = 0;
		}
		
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mx = event.mouse.x * boardSize / displayWidth;
			my = event.mouse.y * boardSize / displayHeight;
			stackPush(toVisit, mx + my * boardSize);
			al_start_timer(timer);
		}

		if (event.type == ALLEGRO_EVENT_TIMER){
			//KONIK DFS
			/*
			if (stackSize(toVisit) > 0) {
				int v = stackPop(toVisit);
				int vx = v % 8;
				int vy = v / 8;

				if (!tab[vy][vx]) {

					//Odwiedzanie
					render_chessBoard(displayWidth, displayHeight);
					al_draw_scaled_bitmap(konikBMP, 0, 0, al_get_bitmap_width(konikBMP), al_get_bitmap_height(konikBMP),
						displayWidth / 8.0 * (vx), displayWidth / 8.0 * (vy), displayHeight / 8.0, displayWidth / 8.0, 0);

					tab[vy][vx] = 1;

					//Rejestrowanie krokow

					for (int ox = 0; ox <= 1; ox++) {
						for (int oy = 0; oy <= 1; oy++) {
							for (int oz = 0; oz <= 1; oz++) {

								int i = vx + (1 + oz) * ((ox) ? -1 : 1);
								int j = vy + (2 - oz) * ((oy) ? -1 : 1);

								if ((!tab[j][i]) && ((0 <= i && i < 8) && (0 <= j && j < 8))) {
									stackPush(toVisit, i + j * 8);
								}
							}
						}
					}

					al_flip_display();
				}
			}*/

			//KONIK BRUTEFORCE
			if (stackSize(tour) != boardSize * boardSize && stackSize(toVisit) > 0) {
				if (stackTop(tour) == stackTop(sourceVisit)) {
					stackPop(sourceVisit);
					int v = stackPop(toVisit);
					int vy = v / boardSize;
					int vx = v % boardSize;
					if (!tab[vy][vx]){

						stackPush(tour, v);

						tab[vy][vx] = 1;

						for (int ox = 0; ox <= 1; ox++) {
							for (int oy = 0; oy <= 1; oy++) {
								for (int oz = 0; oz <= 1; oz++) {

									int i = vx + (1 + oz) * ((ox) ? -1 : 1);
									int j = vy + (2 - oz) * ((oy) ? -1 : 1);

									if ((!tab[j][i]) && ((0 <= i && i < boardSize) && (0 <= j && j < boardSize))) {
										stackPush(toVisit, i + j * boardSize);
										stackPush(sourceVisit, v);
									}
								}
							}
						}
					}
					cofanie = 0;
				}
				else {
					int v = stackPop(tour);
					tab[v / boardSize][v % boardSize] = 0;
					if (!cofanie) pruby++;
					cofanie = 1;
				}

				//printf("\ntour: ");
				//stackPrint(tour);
				//printf("toVisit: ");
				//stackPrint(toVisit);
				//printf("sourceVisit: ");
				//stackPrint(sourceVisit);

				render_chessBoard(displayWidth, displayHeight);
				render_KnightMoves(displayWidth, displayHeight, tour, konikBMP);
				al_flip_display();
			}
		}
	}

	printf("Ilosc prub: %d\n", pruby);

	al_destroy_timer(timer);
	al_destroy_bitmap(konikBMP);
	al_uninstall_mouse();
	al_destroy_display(display);

	return 0;
}