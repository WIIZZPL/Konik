#pragma once

void szachownica(int szerokosc_okna, int wysokosc_okna);

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
int stackSize(Stack* stos);