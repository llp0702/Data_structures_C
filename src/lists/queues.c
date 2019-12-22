#include "headers/queues.h"
#include <stdlib.h>
Queue *allocQueue(int maxElements){
	Queue *result = malloc(sizeof(Queue));
	result->bottom = NULL;
	result->head = NULL;
	result->maxElement = maxElements;
	result->numberOfElements = 0;
	return result;
}

Queue *reinitializeQueue(Queue *s){
	freeList(s->head);
	s->head = NULL;
	s->bottom = NULL;
	s->numberOfElements = 0;
	return s;
}

int emptyQueue(Queue *s){
	return s->numberOfElements==0;
}

int enqueue(Queue *s, void *element){
	if(s->numberOfElements == s->maxElement)return 0;
	ElementOfList *e = addElement(NULL,element, s->numberOfElements,NULL);
	if(s->bottom){
		s->bottom->next = e;
		s->bottom = e;
	}else{
		s->head = e;
		s->bottom = e;
	}
	s->numberOfElements++;
	return 1;
}

void *dequeue(Queue *s){
	if(emptyQueue(s))return NULL;
	s->numberOfElements--;
	void *result = s->head->element;
	s->head = removeElementByIndex(s->head, 0);
	if(s->numberOfElements == 0){
		s->head = NULL;
		s->bottom = NULL;
	}
	return result;
}