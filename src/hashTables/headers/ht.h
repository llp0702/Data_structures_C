#ifndef HT_H
#define HT_H
#include "../../lists/headers/lists.h"

/*This module provides an implementation of hashtables
using Lists for resolving collisions*/

/*Definition of a single Cell */
typedef struct htCell{
	List elements;//The list of elements in the Cell
	int numberOfElements;//the number of elements in
						// the cell
}HtCell;

/*Definition of the main struct of the hash table*/
typedef struct ht{
	HtCell **table;//The table, a vector of HtCell 
					//pointers
	int numberOfElements;//Number of elements in the
						//table (for every list in
						// every cell)
	int maxNumberOfElements;//-1 if there is no 
						//limit, otherwise, it's
						//the maximum number of
						//elements in the hash 
						//table
	int maxNumberOfElementsPerCell;//The max number
								//of elements for
								//every Cell. if -1
								//there is no limit
	int numberOfCells;//Number of available Cells in 
					//the table
	int emptyCells;//Number of empty Cells in the 
					//table
	int (*objToInt) (void *);//A function to pass from
							//an object to an int to
							//hash it
	int (*hashFunc) (int);//A function to pass
						//from a key to it hashed version
}Ht;

/*A function that allocs a hashtable of a number of elements
given in parameter. And two pointers to functions. The first
is a function to pass from an object to an int, and the 
second is a function to pass from an integer key to the hash
of this key (as int)*/
Ht *allocHt(int numberCells, int (*objToInt) (void *), 
	int (*hashFunc)(int));

/*A function that inserts an element in a hash table. It 
returns 0 in case of failure and 1 in case of success*/
int insertHt(Ht *table, void *element);

/*A function that search an element in a hash table. To test
the equality, we give a pointer to a function that returns 
0 in case of equality and 1 otherwise. If the pointer to 
the function is NULL, we use the referencial equality it returns
the element searched if found or NULL otherwise*/
void *searchHt(Ht *table, void *element, int (*equals) (void*, void*));

/*A function that removes an element if it founds. the arguments
have the same signification then the previous function*/
void removeHt(Ht *table, void *element, int (*equals)(void *, void *));

/*A function to print a Hash table in stdout. It takes on parameters
the table to print and a pointer to a function that print an element
of the table. If this pointer to function is NULL, we just print 
the adress of elements*/
void printHt(Ht *ht, void (*printElem)(void *) );
#endif