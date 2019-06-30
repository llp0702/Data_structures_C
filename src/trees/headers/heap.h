#ifndef HEAP_H
#define HEAP_H

/*This module represents an implementation of the data struct
Heap, it's just a binary tree where for every subtree, the 
root has the minimal value. It used for priority lists, because
we can retrieve the minimal element.*/

/*The data type of a cell of the heap, it has an element
and an identifiant*/
typedef struct heapCell{
	void *element;
	int id;
}HeapCell;

/*We implement the tree as a vector of cell heaps managed
to simulate a tree. The first cell will be a HeapCell without
content and as id the number of elements inside the heap.
In the data structure, we have the vector and an integer 
representing the memory size of the vector representing the heap
(when we insert a new element, we check if the heap have the
necessary memory space, in which case we will just insert the
new element. Otherwise, we will check if we don't exceed the
maximal number of elements, next we add space to the heap 
(100 cells). We also have an integer representing the maximal
number of elements in the heap, if its value is -1 we just 
ignore it. (The memory size include the first cell representing
the number of elements inside the heap).*/
typedef struct heap{
	HeapCell **heap;
	int memorySize;
	int maximalNumberOfElements;
 }Heap;

 /*A function to allocate a new heap of given memory size and
 maximalNumberOfElements (if -1 : ignore)*/
Heap *allocHeap(int memorySize, int maximalNumberOfElements);

/*A function that returns 1 if the cell in the given parameter
index has a father, and 0 otherwise*/
int hasFather(Heap *heap, int index);

/*A function that returns 1 if the cell in the given parameter
index has a left son, and 0 otherwise*/
int hasLeftSon(Heap *heap, int index);

/*A function that returns 1 if the cell in the given parameter
index has a right son, and 0 otherwise*/
int hasRightSon(Heap *heap, int index);

/*A function that returns 1 if the cell in the given parameter
index has is a leaf, and 0 otherwise*/
int isLeaf(Heap *heap, int index);

/*A function returning the index of left Son of i*/
int leftSon(int i);

/*A function returning the index of right Son of i*/
int rightSon(int i);

/*A function returning the index of the father of i*/
int father(int i);

/*A function that reinitialize a heap*/
void reinitHeap(Heap *heap);

/*A function that deeply removes a heap (the content too)*/
void deepRemoveHeap(Heap *heap);

/*A function that removes a given heap (without the content)*/
void removeHeap(Heap *heap);

/*A function for swap two cells from a heap of given indexes*/
void swap(Heap *heap, int i, int j);

/*A function to bring up a node in its right place in the heap.
The node is represented by its index in the heap. We give as 
parameter a pointer to a function of comparaison between two
void* elements, in the case where we want to compare attributes
related with the elment. The function returns a positive number
if the first argument is greater, a negative number if the
second argument is greater and 0 otherwise. If this pointer to
function is NULL, we use the id of each node as value for
 comparaison*/
void ascend(Heap *heap, int index, int (*compare)(void*, void*));

/*The same function as ascend, but try to lower the given node*/
void goDown(Heap *heap, int index, int (*compare)(void*, void*));

/*A function that returns -1 if the given node is a leaf, otherwise
it returns the index of the lowest direct son. We can give a 
pointer to function for comparaisons, like ascend function.
If this pointer is set to NULL, we consider id*/
int smallerSon(Heap *heap, int index, int (*compare)(void*, void*));

/*A function to get the minimal element of the heap, NULL if it
does not exist*/
void *minHeap(Heap *heap);

/*A function to insert a new element with a given id into a given
heap. We give (optionnaly) a function for comparaisons*/
void insert(Heap *heap, void *element, int id, 
	int (*compare)(void*, void*));

/*A function to remove the minimal element of a heap. We can give
(optionnaly) a function for comparaisons*/
void removeMinHeap(Heap *p, int (*compare)(void*, void*));

/*A function to draw a heap into a file of a given filename
*/
void drawHeap(Heap *heap, char* filename);

/*A function that generates a random heap of a given number of
elements*/
Heap *generateRandomHeap(int nbElements);  
#endif