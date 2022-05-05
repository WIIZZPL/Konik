#pragma once

#include <stdio.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct Stack {
	Node* top;
	int size;
} Stack;

Stack* stackCreate();
void stackDestroy(Stack* thisStack);
void stackPush(Stack* thisStack, int data);
int stackPop(Stack* thisStack);
int stackTop(Stack* thisStack);
int stackSize(Stack* thisStack);
void stackPrint(Stack* thisStack);