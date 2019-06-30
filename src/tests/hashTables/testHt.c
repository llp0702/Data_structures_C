#include "../../hashTables/headers/ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int objToInt(void *e){
	return ((int)e);
}
int h(int k){
	return k;
}
int eq(void *e, void *a){return !(a==e);}

int main(int argc, char **argv){
	srand(time(NULL));
	fprintf(stderr, "Creation of a hashtable of size 20\n");
	Ht *ht = allocHt(25, objToInt, h);
	fprintf(stderr, "Ok\n");
	fprintf(stderr, "insert 100 elements\n");
	int i=0;
	void *e = malloc(sizeof(int));
	void *f = malloc(sizeof(int));
	int r = insertHt(ht, e);
	if(r==0)fprintf(stderr, "Error in insertion e\n");
	r=insertHt(ht, f);
	if(r==0)fprintf(stderr, "Error in insertion f\n");
	for(i=0;i<98;i++){
		r=insertHt(ht, malloc(sizeof(int)));
		if(r==0)fprintf(stderr, "Error in insertion %d\n", i);
	}

	fprintf(stderr, "Ok\n");

	fprintf(stderr, "Search an element from ht : %p\n", e);
	void *res = searchHt(ht, e, eq);
	if(res == e)fprintf(stderr, "Ok\n");
	else fprintf(stderr, "Ko\n");
	
	fprintf(stderr, "Print a ht\n");
	printHt(ht, NULL);
	fprintf(stderr, "Ok\n");

	fprintf(stderr, "remove an element from ht : %p \n", f);
	removeHt(ht, f, eq);
	fprintf(stderr, "Ok\n");
		
	return 0;
}