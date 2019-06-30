#include "../../graphs/headers/graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "Usage : ./generateRandomGraph [number"
		" of edges] [out filename]\n");
		return 1;
	}
	Graph *g = generateRandomGraph(atoi(argv[1])); 
	saveGraph(g, argv[2]);
	return 0;
}