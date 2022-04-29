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
void stackPush(Stack* stos, int a);
int stackPop(Stack* stos);
int stackTop(Stack* stos);
int stackSize(Stack* stos);
void stackPrint(Stack* stos);