#include "../../graphs/headers/graph.h"
#include <stdlib.h>
#include <stdio.h>

void printTarget(int *targets, int *lambda, int src, int dest){
    if(src==dest){
        printf("%d to %d : distance = %d\n", src, dest, lambda[dest]);
        return;
    }

    if(targets[dest]==-1){
        printf("No path between %d to %d\n", src, dest);
        return;
    }
    printf("%d to %d : distance = %d\nTarget : ", src, dest, lambda[dest]);
    if(src != dest){
        int i=dest;
        while(i != src){
            printf(" %d | ", i);
            i=targets[i];
        }
    }
    printf("%d\n\n",src);
}

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr, "Usage : ./dijkstraSmallestTarget "
        "[graph file target] [id of source node] [id of "
        "arrival node (-1 if we want targets to all nodes)]\n");
    }
    Graph *g = readGraphFromFile(argv[1]);
    int *lambda = calloc(g->n, sizeof(int));
    int *targets = calloc(g->n, sizeof(int));
    dijkstraSmallestTarget(g, atoi(argv[2]), lambda, targets);
    if(atoi(argv[3])==-1){
        int i;

        for(i=0; i<g->n; i++){
            printTarget(targets, lambda, atoi(argv[2]), i);
        }
    }else{
        printTarget(targets, lambda, atoi(argv[2]), atoi(argv[3]));
    }
}