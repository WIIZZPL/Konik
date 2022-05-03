#pragma once

#include "structures.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

ALLEGRO_COLOR al_map_hsv(float hue, float saturation, float value);

void render_chessboard();

void render_KnightMoves(Stack* tour, ALLEGRO_BITMAP* knightBMP);