#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "knightTour.h"

#include "structures.h"
#include "GLOBALS.h"
#include "rendering.h"

Stack* toVisit;     // stos z lista pozycji do odwiedzenia
Stack* sourceVisit; // stos z pozycjami z ktorych odzwiedzic te w toVisit
Stack* tour;        // stos z aktualna trasa konika

unsigned char* tab = NULL;	// tablica odwiedzonych elemntow
double t;	//zmienna przechowujaca czas

ALLEGRO_BITMAP* knightBMP;	// rysunek konika

/*! \fn void initKnightTour(int startingSquare)
	 \brief
	 Funkcja rozpoczynajaca ruch konika

	 \param startingSquare

*/

void initKnightTour(int startingSquare) {
	//Sprawdzanie inicjalizacji
	if (tab) return;

	//Inicjalizacja
	toVisit = stackCreate();
	stackPush(toVisit, startingSquare);
	sourceVisit = stackCreate();
	tour = stackCreate();
	
	tab = (unsigned char*)calloc(boardSize * boardSize, sizeof(unsigned char));
	t = al_get_time();

	knightBMP = al_load_bitmap("knight.png");
	if (!knightBMP) exit(2);
}

/*! \fn void stepKnightTour()
	 \brief
	 Funkcja wykonujaca krok konika

*/

void stepKnightTour() {
	//Sprawdzanie inicjalizacji
	if (!tab) return;
	//Sprawdzanie ukonczenia algorytmu
	if (stackSize(tour) == boardSize * boardSize || stackSize(toVisit) == 0) return;

	//Ruch do przodu
	if (stackTop(tour) == stackTop(sourceVisit)) {
		
		stackPop(sourceVisit);
		int v = stackPop(toVisit);
		if (!tab[v]) {
			//Odwiedzanie
			stackPush(tour, v);
			tab[v] = 1;

			int vy = v / boardSize;
			int vx = v % boardSize;

			//Dane do ustalenia ilosci mozliwych krokow po danym kroku
			unsigned char neighboorsCount = 0;
			int neighboors[8] = { -1, -1, -1, -1, -1, -1, -1, -1};
			unsigned char neighboorsNeighboorsCount[8] = { 0, 0, 0, 0, 0, 0, 0, 0};

			//Pentla ustalajaca kroki
			for (int ox = 0; ox <= 1; ox++) {
				for (int oy = 0; oy <= 1; oy++) {
					for (int oz = 0; oz <= 1; oz++) {

						int i = vx + (1 + oz) * ((ox) ? -1 : 1);
						int j = vy + (2 - oz) * ((oy) ? -1 : 1);

						//Sprawdzanie poprawnosci kroku
						if ((!tab[i + j * boardSize]) && ((0 <= i && i < boardSize) && (0 <= j && j < boardSize))) {
							neighboors[neighboorsCount] = i + j * boardSize;

							//Petla ustalajaca ilosc krokow krokow
							neighboorsNeighboorsCount[neighboorsCount] = 0;
							for (int ox2 = 0; ox2 <= 1; ox2++) {
								for (int oy2 = 0; oy2 <= 1; oy2++) {
									for (int oz2 = 0; oz2 <= 1; oz2++) {

										int i2 = i + (1 + oz2) * ((ox2) ? -1 : 1);
										int j2 = j + (2 - oz2) * ((oy2) ? -1 : 1);
										
										//Sprawdzanie poprawnosci krokow
										if ((!tab[i2 + j2 * boardSize]) && ((0 <= i2 && i2 < boardSize) && (0 <= j2 && j2 < boardSize)))
											neighboorsNeighboorsCount[neighboorsCount]++;
									}
								}
							}

							//Sortowanie tablicy ilosci krokow krokow
							int k = neighboorsCount;
							while (k > 0 && neighboorsNeighboorsCount[k - 1] < neighboorsNeighboorsCount[k]) {
								//Zamiana w tablicy korow krokow
								int temp = neighboorsNeighboorsCount[k - 1];
								neighboorsNeighboorsCount[k - 1] = neighboorsNeighboorsCount[k];
								neighboorsNeighboorsCount[k] = temp;
								//Zamiana w tablicy krokow
								temp = neighboors[k - 1];
								neighboors[k - 1] = neighboors[k];
								neighboors[k] = temp;
								k--;
							}

							neighboorsCount++;
						}
					}
				}
			}

			//Wprowadzanie krokow do stosu
			for (int k = 0; k < neighboorsCount; k++) {
				stackPush(toVisit, neighboors[k]);
				stackPush(sourceVisit, v);
			}
		}
	}

	//Cofanie sie konika
	else {
		int v = stackPop(tour);
		tab[v] = 0;
	}

	//Renderowanie
	render_chessboard();
	render_KnightMoves(tour, knightBMP);
	al_flip_display();

	if (stackSize(tour) == boardSize * boardSize) printf("Time: %lfs", al_get_time()-t);
}

/*! \fn void delKnightTour()
	 \brief
	 Deinicjalizacja

*/

void delKnightTour() {
	if (!tab) return;
	stackDestroy(toVisit);
	stackDestroy(sourceVisit);
	stackDestroy(tour);
	free(tab);
	al_destroy_bitmap(knightBMP);
}