#include "../../graphs/headers/graph.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc==2){
		srand(time(NULL));
		Graph *g = generateRandomGraph(20);
        Flood *f = fordFulkerson(g, 0, g->n-1);
        drawFlood(f, argv[1]);
		freeGraph(g);
		return 0;
	}else if(argc == 3){
		Graph *g = readGraphFromFile(argv[1]);
		Flood *f = fordFulkerson(g, 0, g->n-1);
        drawFlood(f, argv[2]);
		freeGraph(g);
		return 0;
	}else{
		fprintf(stderr, "Usage : ./drawgraph [Out filename]\n"
		"Or : ./drawgraph [Graph filename] [Out filename]\n");
		return 1;	
	}
}