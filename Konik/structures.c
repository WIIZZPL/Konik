#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "structures.h"


/*! \fn Stack* stackCreate()
	 \brief
	 Funkcja tworzaca stos

	 \return Zwraca wskaznik na stos
*/

Stack* stackCreate() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	if (!newStack) exit(138);
	newStack->top = NULL;
	newStack->size = 0;
	return newStack;
}


/*! \fn void stackDestroy(Stack* thisStack)
	 \brief
	 Funkcja niszczaca stos 

	 \param thisStack

*/

void stackDestroy(Stack* thisStack) {
	Node* iter = thisStack->top;
	while (iter){
		Node* nast = iter->next;
		free(iter);
		iter = nast;
	}
	free(thisStack);
}


/*! \fn void stackPush(Stack* thisStack, int data)
	 \brief
	 Funkcja wkladajaca element na stosu

	 \param thisStack
	 \param data

*/

void stackPush(Stack* thisStack, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) exit(138);
	newNode->data = data;
	newNode->next = thisStack->top;
	thisStack->top = newNode;
	thisStack->size++;
}


/*! \fn int stackPop(Stack* thisStack)
	 \brief
	 Funkcja usuwajaca element znajdujacy sie na gorze stosu, ktory pozniej zwraca

	 \param thisStack


	 \return Zwraca wartosc ktora znajdowala sie na gorze (r)

*/

int stackPop(Stack* thisStack) {
	if (thisStack->size <= 0) return -1;
	Node* temp = thisStack->top;
	thisStack->top = temp->next;
	int r = temp->data;
	free(temp);
	thisStack->size--;
	return r;
}


/*! \fn int stackTop(Stack* thisStack)
	 \brief
	 Funkcja zwracajaca wartosc na gorze

	 \param thisStack

	 \return Zwraca wartosc znajdujaca sie na gorze stosu

*/

int stackTop(Stack* thisStack) {
	if (thisStack->top) return thisStack->top->data;
	return -1;
}


/*! \fn int stackSize(Stack* thisStack)
	 \brief
	 Funkcja zwracajaca rozmiar stosu

	 \param thisStack

	 \return Zwraca rozmiar stosu

*/

int stackSize(Stack* thisStack) {
	return thisStack->size;
}


/*! \fn void stackPrint(Stack* thisStack)
	 \brief
	 Funkcja wypisujaca stos

	 \param thisStack

*/

void stackPrint(Stack* thisStack) {
	Node* iter = thisStack->top;
	while (iter) {
		printf("%d ", iter->data);
		iter = iter->next;
	}
	printf("\n");
}