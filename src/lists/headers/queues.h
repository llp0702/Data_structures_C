#ifndef QUEUES_H
#define QUEUES_H
#include "lists.h"
/*This module is an implementation of queues (FIFO), it's based
on lists. We insert elements from the bottom and we retrieve
elements from head*/

typedef struct queue{
	List head;
	ElementOfList *bottom;
	int numberOfElements;
	int maxElement;
}Queue;

Queue *allocQueue(int maxElements);

Queue *reinitializeQueue(Queue *s);

int emptyQueue(Queue *s);

int enqueue(Queue *s, void *element);

void *dequeue(Queue *s);

#endif