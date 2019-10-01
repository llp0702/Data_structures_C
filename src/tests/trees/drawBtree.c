#include "../../trees/headers/btrees.h"
#include "../../trees/headers/bSTrees.h"
#include "../../trees/headers/bAVLTress.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
	if(argc==3){
		srand(time(NULL));
		Btree *bt= NULL;
		if(atoi(argv[1])==0) bt = generateRandomBSTree(20);
		else bt = generateRandomBAVLTree(20);
		drawBtree(bt, argv[2]);
		removeBtree(bt);
		return 0;
	}else if(argc == 4){
		Btree *bt=NULL;
		if(atoi(argv[1])==0)bt = readBSTreeFromFile(argv[2]);
		else bt =readBAVLTreeFromFile(argv[2]);
/*		drawBtree(bt, "1");
		fprintf(stderr,"_______4\n");
		bt=removeAvlId(bt, 4);
		fprintf(stderr, "_______ 4\n");
		drawBtree(bt, "2");
		fprintf(stderr, "_______8\n");
		bt=removeAvlId(bt, 8);
		fprintf(stderr, "_______8\n");
		drawBtree(bt, "3");
		fprintf(stderr, "_______1\n");
		bt=removeAvlId(bt, 1);
		fprintf(stderr, "_______1\n");
*/
		drawBtree(bt, argv[3]);
		removeBtree(bt);
		return 0;
	}else{
		fprintf(stderr, "Usage : ./drawgraph [1 if avl 0 if not avl] [Out filename]\n"
		"Or : ./drawgraph [1 if avl 0 if not avl] [Graph filename] [Out filename]\n");
		return 1;	
	}
}