#include "../../graphs/headers/graph.h"
#include <stdio.h>
void f(void *e){
	Vertex *v=(Vertex *)e;
	printf("%d |",v->id);
}
int main(int argc, char **argv){
	if(argc!=2){
		fprintf(stderr, "Usage : ./browseGraphDepth [graph filename]\n");
		return 1;
	}
	Graph *g = readGraphFromFile(argv[1]);
	browseGraphWidth(g,f);
	printf("\n");
	freeGraph(g);
	return 0;
}