#include "../../graphs/headers/graph.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc==2){
		srand(time(NULL));
		Graph *g = generateRandomGraph(20);
		drawGraph(g, argv[1]);
		freeGraph(g);
		return 0;
	}else if(argc == 3){
		Graph *g = readGraphFromFile(argv[1]);
		drawGraph(g, argv[2]);
		freeGraph(g);
		return 0;
	}else{
		fprintf(stderr, "Usage : ./drawgraph [Out filename]\n"
		"Or : ./drawgraph [Graph filename] [Out filename]\n");
		return 1;	
	}
}