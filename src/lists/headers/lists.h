#ifndef LISTS_H
#define LISTS_H
/*This module contain some functions to manipulate basic linear
lists*/



typedef struct elementOfList{
	int id;
	char *label;
	void *element;
	struct elementOfList *next;
}ElementOfList;

typedef ElementOfList *List;

/*Returns the list l newElement added in the beginning*/
List addElement(List l, void *newElement, int id, char *label);

/*Returns the list l without the element given as parameter*/
List removeElement(List l, void *newElement);

/*Returns the list l without its element in indexth position*/
List removeElementByIndex(List l, int index);

/*Return the list l without elements that verify the
predicate given as parameter. The predicate is a function 
that returns a char (0 if false, another value if true) and take
a void* as parameter (compatible with the elements of every list).
We give an integer i as parameter representing the maximum
number of elements that we can remove in the list. If its value
is -1 we dont limitate the number of removable elements*/
List removeElementsPredicate(List l, char (*f)(void *,int id,char *), int i);

/*This function free all the memory allocated for a list*/
void freeList(List l);

/*A function that returns the list given as parameter but inverted */
List invertList(List l);

/*A function to print a list in stdout */
void printList(List l);

/*A function to duplicate a list */
List duplicateList(List l);
#endif