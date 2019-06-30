#include "../../trees/headers/bSTrees.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv){
	if(argc != 3){
		fprintf(stderr, "Usage : ./generateRandomBStree [number"
		" of elements] [out filename]\n");
		return 1;
	}
	Btree *bt = generateRandomBSTree(atoi(argv[1])); 
	saveBSTree(bt, argv[2]);
	return 0;
}