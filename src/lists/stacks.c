#include "headers/stacks.h"
#include "headers/lists.h"
#include <stdlib.h>
#include <string.h>

Stack *allocStack(int maxElements){
	Stack *result = calloc(1,sizeof(Stack));
	result->head = NULL;
	result->numberOfElements = 0;
	result->maxElements = maxElements;
	return result; 
}

Stack *reinitialize(Stack *s){
	s->numberOfElements = 0;
	if(s->head)freeList(s->head);
	s->head = NULL;
	return s;
}

int emptyStack(Stack *s){
	return (s->numberOfElements==0)?1:0;
}

int push(Stack *s, void *element){
	if(s->numberOfElements == s->maxElements)return 0;
	s->head = addElement(s->head,element, s->numberOfElements,NULL);
	s->numberOfElements++;
	return 1;
}

void *pop(Stack *s){
	if(emptyStack(s))return NULL;
	void *result = s->head->element;
	s->numberOfElements--;
	s->head = removeElementByIndex(s->head,0);
	return result;
}