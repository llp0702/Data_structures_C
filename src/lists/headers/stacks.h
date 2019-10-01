#ifndef STACKS_H
#define STACKS_H
#include "lists.h"
#include <stdlib.h>
#include <stdio.h>
/*This module implements lists as stacks. A stack is just a
list that we insert and remove elements only from the head
(Known as LIFO)*/

typedef struct stack{
	List head;
	int numberOfElements;
	int maxElements;//The maximum number of elements inside the stack, unlimited if -1
}Stack;

/*A function that creates a stack, it takes one parameter, it's
the maximum number of elements on it. Unlimited if -1*/
Stack *allocStack(int maxElements);

/*A function that reinitialize a stack (make it empty)*/
Stack *reinitialize(Stack *s);

/*A function to know if a stack is empty or not, returns 0 if not
and 1 if yes*/
int emptyStack(Stack *s);


/*A function of insertion in Stack, a classic one, returns 0
if the insertion does'nt occur. We insert an element with 
it's id and it's label(Optionnal)*/
int push(Stack *s, void *element);

/*A function to retrieve the element in the head of the stack
given as parameter, returns NULL if the operation failed. the 
id parameter will contain the id of the object that we pop,
and same for the label */
void *pop(Stack *s);

#endif