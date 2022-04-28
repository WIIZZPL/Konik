#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "funkcje.h"

void szachownica(int szerokosc_okna, int wysokosc_okna){
	int x = 0;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			x = ++x % 2;
			al_draw_filled_rectangle((szerokosc_okna / 8.0) * i, (wysokosc_okna / 8.0) * j, (szerokosc_okna / 8.0) * (i + 1), (wysokosc_okna / 8.0) * (j + 1), al_map_rgb(255 * x, 255 * x, 255 * x)); //mo¿na dodaæ skopiowaniem polecenia ramke pola szachownicy
		}
		x++;
	}
}

Stack* stackCreate() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	newStack->top = NULL;
	newStack->size = 0;
	return newStack;
}

void stackPush(Stack* stos, int a) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = a;
	newNode->next = stos->top;
	stos->top = newNode;
	stos->size++;
}

int stackPop(Stack* stos) {
	assert(stos->size > 0);
	Node* temp = stos->top;
	stos->top = temp->next;
	int r = temp->data;
	free(temp);
	stos->size--;
	return r;
}

int stackSize(Stack* stos) {
	return stos->size;
}