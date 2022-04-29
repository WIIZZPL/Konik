#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "structures.h"

Stack* stackCreate() {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	assert(newStack);
	newStack->top = NULL;
	newStack->size = 0;
	return newStack;
}

void stackPush(Stack* stos, int a) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->data = a;
	newNode->next = stos->top;
	stos->top = newNode;
	stos->size++;
}

int stackPop(Stack* stos) {
	if (stos->size <= 0) return -1;
	Node* temp = stos->top;
	stos->top = temp->next;
	int r = temp->data;
	free(temp);
	stos->size--;
	return r;
}

int stackTop(Stack* stos) {
	if (stos->top) return stos->top->data;
	return -1;
}

int stackSize(Stack* stos) {
	return stos->size;
}

void stackPrint(Stack* stos) {
	Node* iter = stos->top;
	while (iter) {
		printf("%d ", iter->data);
		iter = iter->next;
	}
	printf("\n");
}