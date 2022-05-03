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

void stackPush(Stack* thisStack, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->data = data;
	newNode->next = thisStack->top;
	thisStack->top = newNode;
	thisStack->size++;
}

int stackPop(Stack* thisStack) {
	if (thisStack->size <= 0) return -1;
	Node* temp = thisStack->top;
	thisStack->top = temp->next;
	int r = temp->data;
	free(temp);
	thisStack->size--;
	return r;
}

int stackTop(Stack* thisStack) {
	if (thisStack->top) return thisStack->top->data;
	return -1;
}

int stackSize(Stack* thisStack) {
	return thisStack->size;
}

void stackPrint(Stack* thisStack) {
	Node* iter = thisStack->top;
	while (iter) {
		printf("%d ", iter->data);
		iter = iter->next;
	}
	printf("\n");
}