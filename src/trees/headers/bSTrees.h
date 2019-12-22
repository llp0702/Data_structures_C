#ifndef BSTREES_H
#define BSTREES_H
#include "btrees.h" 

/*This module extends the module btrees. To implement search binary trees.
A more performant type of btree. It specificity is that for every node
of the btree, all the nodes in it left sub btree have an inferior id than him
and all the nodes in it right sub btree have a superior id than him. We can't
have repetitions of id in this type of btrees so we suppose that every node 
have an uniq id*/

/*This functions returns 1  if bt is a search binary tree or 0 if not */
int checkIfBST(Btree *bt);

/*This function returns the node of minimal id in the Btree given in parameter*/
Btree *minBST(Btree *bt);

/*This function returns the node of maximal id in the Btree given in parameter*/
Btree *maxBST(Btree *bt);

/*This function search inside the btree given in parameter a node with a given
id, it returns NULL if not found. This function is of O(btree height) complexity
because the tree is of type search binary tree*/
Btree *containsBtsId(Btree *bt, int id);

/*This function insert a new node inside a search binary tree, with the 
informations given in parameter*/
Btree *insertBts(Btree *bt, int id, char *label, void *content);

/*This function remove a node inside the btree with the maximal Id and puts it
informations inside the pointers given in parameters*/
Btree *removeBtsMaxId(Btree *bt, int *id, char **label, void **content);

/*This function remove a node inside the btree with the minimal Id and puts it
informations inside the pointers given in parameters. It returns the new Root 
of the Btree*/
Btree *removeBtsMinId(Btree *bt, int *id, char **label, void **content);

/*This function remove a node inside a btree with the given id (if it's on it)
it returns the new Root of the Btree*/
Btree *removeBtsId(Btree *bt, int id);

/*This function generate a random search binary tree. with a given size in 
parameter*/
Btree *generateRandomBSTree(int numberElements);

/*It reads a bstree from a file of a name given in parameter. 
The format file is : 
[Number of elements]
[Id] [Label]
[Id] [Label]
[Id] [Label]
[Id] [Label]
...
...
...
[Id] [Label]
*/
Btree *readBSTreeFromFile(char *filename);


/*This function save a btree given in parameter in a file of a given name. 
With the same format previously described*/
void saveBSTree(Btree *bt, char *filename);

#endif