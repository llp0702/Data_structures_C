#include "../../graphs/headers/graph.h"
#include <stdio.h>

int main(int argc, char **argv){
	if(argc!=2){
		fprintf(stderr, "Usage : ./containsGraphCycle [graph filename]\n");
		return 1;
	}
	Graph *g = readGraphFromFile(argv[1]);
	int contains = containsCycle(g);
	fprintf(stdout, "%s\n",(contains)?"Yes":"No");
	return (contains+1)%2;
}