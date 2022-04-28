#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "funkcje.h"

int main(void){
	assert(al_init()); //initialising the library
	assert(al_init_image_addon());
	assert(al_init_primitives_addon());

	assert(al_install_keyboard());
	assert(al_install_mouse());
	int mx, my;

	ALLEGRO_DISPLAY* display = NULL;
	display = al_create_display(720, 720); //creating a window, providing its width and height in pixels

	int szerokosc_okna = al_get_display_width(display); //pobieranie szerokoœci okna
	int wysokosc_okna = al_get_display_height(display);

	ALLEGRO_TIMER* timer;
	timer = al_create_timer(1/10.0);

	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP* bitmap = NULL;
	assert(bitmap = al_load_bitmap("konik.png"));

	//INICJALIZACJA ALGORYTMU

	Stack* stos = stackCreate();
	int tab[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tab[i][j] = 0;
		}
	}
	int kx = 0;
	int ky = 0;
	int konikStart = 0;

	int running = 1;
	al_start_timer(timer);

	while(running){
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || al_key_down(&keyState, ALLEGRO_KEY_END)){
			running = 0;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			mx = event.mouse.x * 8 / szerokosc_okna;
			my = event.mouse.y * 8 / wysokosc_okna;
			stackPush(stos, mx + my * 8);
			konikStart = min(2, konikStart + 1);
		}
		
		if (event.type == ALLEGRO_EVENT_TIMER){
			
			szachownica(szerokosc_okna, wysokosc_okna); //tlo

			/*if (konikStart == 2) {
				if ((abs(mx - kx) + abs(my - ky)) == 3) {
					kx = mx;
					ky = my;
				}
				al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
					szerokosc_okna / 8.0 * (kx), wysokosc_okna / 8.0 * (ky), szerokosc_okna / 8.0, wysokosc_okna / 8.0, NULL);
			} else if (konikStart == 1) {
				kx = mx;
				ky = my;
				konikStart = 2;
				al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
					szerokosc_okna / 8.0 * (kx), wysokosc_okna / 8.0 * (ky), szerokosc_okna / 8.0, wysokosc_okna / 8.0, NULL);
			}*/

			if (stackSize(stos) > 0) {
				//ALGORYTM
				int v = stackPop(stos);
				int x = v % 8;
				int y = v / 8;
				tab[y][x] = 1;

				//Odwiedzanie

				al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),
					szerokosc_okna / 8.0 * (x), wysokosc_okna / 8.0 * (y), szerokosc_okna / 8.0, wysokosc_okna / 8.0, NULL);

				//Rejestrowanie krokow

				for (int ox = 0; ox <= 1; ox++) {
					for (int oy = 0; oy <= 1; oy++) {
						for (int oz = 0; oz <= 1; oz++) {
							
							int i = x + (1+oz) * ((ox)?-1:1);
							int j = y + (2-oz) * ((oy)?-1:1);
							
							if (!(tab[j][i]) && ((0 <= i && i < 8) && (0 <= j && j < 8))) {
								stackPush(stos, i + j * 8);
							}
						}
					}
				}
			}

			al_flip_display();

		}
	}

	al_destroy_timer(timer);
	al_destroy_bitmap(bitmap);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_display(display);

	return 0;
}