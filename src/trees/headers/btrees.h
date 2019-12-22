#ifndef BTREES_H
#define BTREES_H
#define max(a,b) ((a>b)?a:b)
/*This struct represents a very basic representation of binary trees, that
we will use in the future as a base for much complex binary trees configurations
*/
typedef struct btree{
	int id;//Every node has an id
	char *label;//Every node has a label
	void *content;//Every node can contain an object pointed by this element
	int height;//Every tree have a height that we save for later usage (AVL)
	struct btree *left;//The left sub binary tree
	struct btree *right;//The right sub binary tree
	struct btree *father;//A pointer to the father of every node. NULL pointed if root
}Btree;


/*A function that allocates a Btree node with the informations given 
as parameters*/
Btree *allocBtree(int id, char *label, void *content, 
	Btree *left, Btree *right, Btree *father);


/*A function of browsing based on the prefix approach. It applies a function
f given as parameter that returns a void and take a pointer to Btree. This 
function will be applied to every node of the Btree*/
void browsePrefix(Btree *bt, void(*f)(Btree *));

/*A function of browsing based on the suffix approach. It applies a function
f given as parameter that returns a void and take a pointer to Btree. This 
function will be applied to every node of the Btree*/
void browseSuffix(Btree *bt, void(*f)(Btree *));

/*A function of browsing based on the inorder approach. It applies a function
f given as parameter that returns a void and take a pointer to Btree. This 
function will be applied to every node of the Btree*/
void browseInorder(Btree *bt, void(*f)(Btree *));

/*A function to compute the number of nodes inside the Btree*/
int sizeBtree(Btree *bt);

/*Deprecated !
This function computes the height of a btree recursively
If our Btree is AVL, the functions update the heigh key inside the Btree
Object, so we need not to call this function*/
int heightBtree(Btree *bt);

/*A function that free all the space allocated for a btree and it sub btrees*/
void removeBtree(Btree *bt);

/*A function that returns a clone of a btree given as parameter*/
Btree *copyBtree(Btree *bt);

/*A function that searchs a node with a given id inside a random btree (O(n))*/
Btree *containsBtId(Btree *bt, int id);

/*A function that searchs a node with a given label inside a random btree (O(n))*/
Btree *containsBtLabel(Btree *bt, char *label);

/*A function that searchs a node with a given pointer to element inside a 
random btree (O(n))*/
Btree *containsBtElement(Btree *bt, void *element);

/*A function that generates a random Btree with a given number of elements*/
Btree *generateRandomBtree(int numberElements);

/*A function that draws a btree inside a file and show it automatically. It 
will save the result in a file with the given filename extended by .out 
This function is based on the software graphviz. So you need to have it installed*/
void drawBtree(Btree *bt, char *filename);
#endif