#include "rendering.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "GLOBALS.h"
#include <math.h>

ALLEGRO_COLOR al_map_hsv(float h, float s, float v) {
	h = fmod(h, 360);
	float C = s * v / 10000;
	float X = C * (1 - fabs(fmod((h / 60), 2) - 1));
	float m = v / 100 - C;
	
	float r, g, b;

	if (h < 60) {
		r = C; g = X; b = 0;
	}
	else if (h < 120) {
		r = X, g = C, b = 0;
	}
	else if (h < 180) {
		r = 0, g = C, b = X;
	}
	else if (h < 240) {
		r = 0, g = X, b = C;
	}
	else if (h < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}

	return al_map_rgb((r+m)*255, (g+m)*255, (b+m)*255);
}

void render_chessBoard(int displayWidth, int displayHeight) {
	
	int p = 0;

	ALLEGRO_COLOR kafelek0 = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR kafelek1 = al_map_rgb(45, 49, 66);

	for (int j = 0; j < boardSize; j++)
	{
		for (int i = 0; i < boardSize; i++)
		{
			p = ++p % 2;
			al_draw_filled_rectangle((displayWidth / boardSize) * i, (displayHeight / boardSize) * j, (displayWidth / boardSize) * (i + 1), (displayHeight / boardSize) * (j + 1), (p)?kafelek0:kafelek1); //mo¿na dodaæ skopiowaniem polecenia ramke pola szachownicy
		}
		p += (boardSize+1) % 2;
	}
}

void render_KnightMoves(int displayWidth, int displayHeight, Stack* tour, ALLEGRO_BITMAP* konikBMP) {
	if(!tour->size) return;
	Node* lastMove = tour->top;
	int tourThickness = displayHeight/boardSize/10;

	int kx = lastMove->data % boardSize;
	int ky = lastMove->data / boardSize;

	float h = 347, s = 78.2, v = 80.8;
	h += 360.0 * (tour->size-1) / boardSize / boardSize;
	ALLEGRO_COLOR tourColor = al_map_hsv(h, s, v);

	//Rysowanie trasy
	while (lastMove->next){
		al_draw_filled_circle((lastMove->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.5) * (displayHeight / boardSize),
			tourThickness / 2.0, tourColor);
		
		al_draw_line((lastMove->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.5) * (displayHeight / boardSize),
			(lastMove->next->data % boardSize + 0.5) * (displayWidth / boardSize), (lastMove->next->data / boardSize + 0.5) * (displayHeight / boardSize),
			tourColor, tourThickness);

		lastMove = lastMove->next;

		h -= 360.0 / boardSize / boardSize;
		tourColor = al_map_hsv(h, s, v);
	}

	//X miejsca rozpoczecia
	al_draw_line((lastMove->data % boardSize + 0.25) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.25) * (displayHeight / boardSize),
		(lastMove->data % boardSize + 0.75) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.75) * (displayHeight / boardSize),
		tourColor, tourThickness);

	al_draw_line((lastMove->data % boardSize + 0.25) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.75) * (displayHeight / boardSize),
		(lastMove->data % boardSize + 0.75) * (displayWidth / boardSize), (lastMove->data / boardSize + 0.25) * (displayHeight / boardSize),
		tourColor, tourThickness);

	//Rysowanie konika
	al_draw_scaled_bitmap(konikBMP, 0, 0, al_get_bitmap_width(konikBMP), al_get_bitmap_height(konikBMP),
		displayWidth / boardSize * (kx), displayWidth / boardSize * (ky), displayHeight / boardSize, displayWidth / boardSize, 0);
}