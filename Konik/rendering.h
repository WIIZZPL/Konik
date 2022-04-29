#pragma once

#include "structures.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

ALLEGRO_COLOR al_map_hsv(float h, float s, float v);

void render_chessBoard(int displayWidth, int displayHight);

void render_KnightMoves(int displayWidth, int displayHeight, Stack* tour, ALLEGRO_BITMAP* konikBMP);