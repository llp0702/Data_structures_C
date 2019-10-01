#ifndef BAVLTREES_H
#define BAVLTREES_H
#include "bSTrees.h"

/*This module is an extension of the search binary trees, it implements 
a better version of search binary trees, called AVL search binary tree.
For every node in this type of btrees, the difference between the height
of the left and right sub btree don't exceed 1*/

/*A function that inserts an element inside an AVL Btree, with the 
informations given in parameters*/
Btree *insertAvl(Btree *bt, int id, char *label, void *content);

/*A function that removes a node given in parameters from an AVL btree
given in parameter too. It returns the new root of the AVL BStree*/
Btree *removeAvl(Btree *bt, Btree *node);

/*A function that removess an element (if it exists) of a given id
from an AVL Btree*/
Btree *removeAvlId(Btree *bt, int id);

/*This function rebalance the btree given in parameter, it manipulates
the left and right rotations and returns the new root*/
Btree *rebalance(Btree *bt);

/*This function make a left rotation for a given Btree*/
Btree *leftRotation(Btree *bt);

/*This function make a right rotation for a given Btree*/
Btree *rightRotation(Btree *bt);

/*This function update the height of a given btree according with the
heights of the sub btrees */
void updateHeight(Btree *bt);

/*This function generate a random AVL Btree with a given number of 
elements*/
Btree *generateRandomBAVLTree(int numberOfElements);

/*This function reads an AVL from a file of a given name with the same
format described in bstree module*/
Btree *readBAVLTreeFromFile(char *filename);
#endif