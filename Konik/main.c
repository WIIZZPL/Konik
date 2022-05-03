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
	if(!al_install_mouse()) return -1;

	displayWidth = 1000;
	displayHeight = 1000;
	ALLEGRO_DISPLAY* display = al_create_display(displayWidth, displayHeight);

	ALLEGRO_TIMER* timer = al_create_timer(1/100.0);

	ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP* knightBMP = al_load_bitmap("knight.png");
	assert(knightBMP);

	//INICJALIZACJA ALGORYTMU

	Stack* toVisit = stackCreate();    // stos z lista pozycji do odwiedzenia
	Stack* sourceVisit = stackCreate();// stos z pozycjami z ktorych odzwiedzic te w toVisit
	Stack* tour = stackCreate();       // stos z aktualna trasa konika
	
	int tab[boardSize][boardSize];
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			tab[i][j] = 0;
		}
	}

	int running = 1;

	render_chessboard();
	al_flip_display();

	while(running){
		ALLEGRO_EVENT event;
		al_wait_for_event(eventQueue, &event);
			
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = 0;
		}

		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			int mx = event.mouse.x * boardSize / displayWidth;
			int my = event.mouse.y * boardSize / displayHeight;
			stackPush(toVisit, mx + my * boardSize);
			al_start_timer(timer);
		}

		else if (event.type == ALLEGRO_EVENT_TIMER) {

			if (stackSize(tour) != boardSize * boardSize && stackSize(toVisit) > 0) {
				if (stackTop(tour) == stackTop(sourceVisit)) {
					stackPop(sourceVisit);
					int v = stackPop(toVisit);
					int vy = v / boardSize;
					int vx = v % boardSize;
					if (!tab[vy][vx]) {

						stackPush(tour, v);
						tab[vy][vx] = 1;

						for (int ox = 0; ox <= 1; ox++) {
							for (int oy = 0; oy <= 1; oy++) {
								for (int oz = 0; oz <= 1; oz++) {

									int i = vx + (1 + oz) * ((ox) ? -1 : 1);
									int j = vy + (2 - oz) * ((oy) ? -1 : 1);

									if ((!tab[j][i]) && ((0 <= i && i < boardSize) && (0 <= j && j < boardSize))) {
										stackPush(toVisit, i+j*boardSize);
										stackPush(sourceVisit, v);
									}
								}
							}
						}
					}
				}
				
				else {
					int v = stackPop(tour);
					tab[v / boardSize][v % boardSize] = 0;
				}

				render_chessboard();
				render_KnightMoves(tour, knightBMP);
				al_flip_display();
			}
		}
	}

	al_destroy_timer(timer);
	al_destroy_bitmap(knightBMP);
	al_uninstall_mouse();
	al_destroy_display(display);

	return 0;
}