#ifndef GRAPH_H
#define GRAPH_H 
/*This module contains definitions of graph structures and very
 general algorithms about graphs, without considering if the 
 graph is weighted or not, neither if the graph is oriented 
 or not*/

#include "../../lists/headers/lists.h"

typedef struct edge {
	int id;//An id for the edge (the index inside the graph)

	int u;//The index of the first vertex (inside the graph)
	int v;//The index of the second vertex (inside the graph)
	
	char *label;//A label describing the edge
	double weight;//The weight of the edge
}Edge;

typedef struct vertex{
	int id;
	
	char *label;
	void *content;

	int nbNeighbors;
	List neighbors;

}Vertex;

typedef struct graph{
	int oriented;//1 if yes 0 if no
	int n;//Number of vertices
	int m;//Number of edges

	Vertex **vertices;
	Edge **edges;
}Graph;

/*A type for floods, it consists on an oriented and weighted 
graph. We associate to it a vector of doubles, containig for 
every edge, a value of flood. A flood also contains 2 integerss
one for departure, the other for arrival*/
typedef struct flood{
	Graph *network;
	double *floodVect;
	int departure;
	int arrival;
}Flood;

/*This function creates an edge from it's informations*/
Edge *allocEdge(int id, int u, int v, char *label, double weight);

/*This function creates a vertex from its informations*/
Vertex *allocVertex(int id, char *label, void *content, int nbNeighbors, List neighbors);

/*This function adds a vertex in a graph*/
void addVertex(Graph *g, Vertex *v);

/*This function adds a edge in a graph*/
void addEdge(Graph *g, Edge *e);

/*This function generate a graph from a file*/
Graph *readGraphFromFile(char *filename);

/*This function saves a Graph in a file*/
void saveGraph(Graph *g, char *filename);

/*This function draws a Graph in a file*/
void drawGraph(Graph *g, char *filename);

/*This function free all the memory allocated to the graph*/
void freeGraph(Graph *g);

/*A function that executes a modification inside the elements
of a graph, taking on parameters (optionnaly) it's id and it's
label. We browse the graph using the depth method*/
void browseGraphDepth(Graph *g, void (*f)(void *));

/*The recursive version of the function browseGraphDepth*/
void browseGraphDepthRecursive(Graph *g, void (*f)(void *));

/*Same as the function browseGraphDepth but using the width
method*/
void browseGraphWidth(Graph *g, void (*f)(void *));

/*The recursive version of the function browseGraphWidth*/
void browseGraphWidthRecursive(Graph *g, void (*f)(void*));

/*A function that returns 0 if the graph given as parameter
does'nt contains a cycle, and 1 if it contains a cycle*/
int containsCycle(Graph *g);

/*A function that generate a random instance of a graph, */
Graph *generateRandomGraph(int numberVertices);

/*A function that implements Dijkstra algorithm. We give as 
parameters the graph concerned, the id of the origin node, 
and pointer to a vector lambda that will contain the smaller
distance to the origin, and another vector that will contain
for every node the smallest target from the origin to it*/
void dijkstraSmallestTarget(Graph *g, int origin, int *lambda,
 int *targets);

/*A function to find all the paths between two vertices in a 
graph. We give as parameters the concerned graph and 2 integers
for id of the origin and the arrival. We return a list of lists
of integers, representing every path as a list of id of vertices
composing each path*/
List findAllPaths(Graph *g, int from, int to);

/*A function to find a path between two vertices in a 
graph. We give as parameters the concerned graph and 2 integers
for id of the origin and the arrival. We return a list 
of integers, representing the path as a list of id of vertices
composing the path*/
List findAPath(Graph *g, int from, int to);

/*A function to create a flood from a given graph (the graph
must be oriented and we assume it weighted)*/
Flood *allocFlood(Graph *g, int departure, int arrival);

/*A function to read a flood from a graph given in a file (we
just need to give the name of the file). We give 2 integers
as*/
Flood *readFloodFromGraphFile(char *filename, int departure, 
int arrival);

/*A function that applies Ford-Fulkerson algorithm for a given
Graph in parameter, to generate the optimal flood*/
Flood *fordFulkerson(Graph *g, int departure, int arrival);

/*A function to draw a flood in a file of given filename*/
void drawFlood(Flood *f, char *filename);
#endif