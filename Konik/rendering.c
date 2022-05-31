#include "rendering.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "GLOBALS.h"
#include <math.h>

/*! \fn ALLEGRO_COLLOR al_map_hsv(float hue, float saturation, float value)
	\brief
	Funkcja do tworzenia gladkich przejsc miedzy kolorami wyznaczajacymi trase konika

	\param hue
	\param saturation
	\param value

	\return aaa

*/

ALLEGRO_COLOR al_map_hsv(float hue, float saturation, float value) {
	hue = fmod(hue, 360);
	float C = saturation * value / 10000;
	float X = C * (1 - fabs(fmod((hue / 60), 2) - 1));
	float m = value / 100 - C;
	
	float r, g, b;

	if (hue < 60) {
		r = C; g = X; b = 0;
	}
	else if (hue < 120) {
		r = X, g = C, b = 0;
	}
	else if (hue < 180) {
		r = 0, g = C, b = X;
	}
	else if (hue < 240) {
		r = 0, g = X, b = C;
	}
	else if (hue < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}

	return al_map_rgb((r+m)*255, (g+m)*255, (b+m)*255);
}

/*! \fn void render_chessboard()
	\brief
	Funkcja tworzaca szachownice

*/

void render_chessboard() {
	ALLEGRO_COLOR kafelek0 = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR kafelek1 = al_map_rgb(45, 49, 66);

	for (int j = 0; j < boardSize; j++){
		for (int i = 0; i < boardSize; i++){
			al_draw_filled_rectangle((displayWidth / boardSize) * i, (displayHeight / boardSize) * j,
				(displayWidth / boardSize) * (i + 1), (displayHeight / boardSize) * (j + 1),
				((i+j)%2)?kafelek1:kafelek0);
		}
	}
}

/*! \fn void render_KnightMoves(Stack* tour, ALLEGRO_BITMAP* knightBMP)
	\brief
	Funkcja renderujaca ruchy skoczka

	\param tour
	\param knightBMP

*/

void render_KnightMoves(Stack* tour, ALLEGRO_BITMAP* knightBMP) {
	if(!tour->size) return;

	float hue = 347.0, saturation = 78.2, value = 80.8;
	hue += 360.0 * (tour->size-1) / boardSize / boardSize;
	ALLEGRO_COLOR tourColor = al_map_hsv(hue, saturation, value);
	
	Node* lastMove = tour->top;
	int tourThickness = displayHeight / boardSize / 10;

	//Rysowanie trasy
	while (lastMove->next){
		al_draw_filled_circle((lastMove->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.5) * (displayHeight / boardSize),
			tourThickness, tourColor);
		
		al_draw_line((lastMove->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.5) * (displayHeight / boardSize),
			(lastMove->next->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->next->data / boardSize + 0.5) * (displayHeight / boardSize),
			tourColor, tourThickness);

		lastMove = lastMove->next;

		hue -= 360.0 / boardSize / boardSize;
		tourColor = al_map_hsv(hue, saturation, value);
	}

	//X miejsca rozpoczecia
	al_draw_line((lastMove->data % boardSize + 0.25) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.25) * (displayHeight / boardSize),
		(lastMove->data % boardSize + 0.75) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.75) * (displayHeight / boardSize),
		tourColor, tourThickness);

	al_draw_line((lastMove->data % boardSize + 0.25) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.75) * (displayHeight / boardSize),
		(lastMove->data % boardSize + 0.75) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.25) * (displayHeight / boardSize),
		tourColor, tourThickness);

	//Rysowanie konika
	int knightX = tour->top->data % boardSize;
	int knightY = tour->top->data / boardSize;
	al_draw_scaled_bitmap(knightBMP, 0, 0, al_get_bitmap_width(knightBMP), al_get_bitmap_height(knightBMP),
		displayWidth / boardSize * knightX, displayWidth / boardSize * knightY, displayHeight / boardSize, displayWidth / boardSize, 0);
}