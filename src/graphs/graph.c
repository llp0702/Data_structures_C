#include "headers/graph.h"
#include "../lists/headers/lists.h"
#include "../lists/headers/stacks.h"
#include "../lists/headers/queues.h"
#include "../trees/headers/heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Edge *allocEdge(int id, int u, int v, char *label, double weight){
	Edge *e=malloc(sizeof(Edge));
	e->id = id;
	e->u=u;
	e->v=v;
	e->label=label;
	e->weight=weight;
	return e;
}

Vertex *allocVertex(int id, char *label, void *content, int nbNeighbors, 
List neighbors){
	Vertex *v=malloc(sizeof(Vertex));
	v->id=id;
	v->label=label;
	v->content=content;
	v->nbNeighbors=nbNeighbors;
	v->neighbors=neighbors;
	return v;
}

void addVertex(Graph *g, Vertex *v){
	g->n++;
	g->vertices = realloc(g->vertices, g->n*sizeof(Vertex *));
	g->vertices[g->n-1] = v;
}

void addEdge(Graph *g, Edge *e){
	g->m++;
	g->edges = realloc(g->edges, g->m*sizeof(Edge *));
	g->edges[g->m-1] = e;
}

Graph *readGraphFromFile(char *filename){
	FILE *f=fopen(filename,"r");
	if(!f){
		fprintf(stderr,"Warning : Could not read a graph from %s\n",filename);
		return NULL;
	}
	char *line=calloc(255,sizeof(char));
	Graph *result = calloc(1,sizeof(Graph));
	fgets(line,255,f);
	sscanf(line, " %d %d %d", &(result->n), &(result->m), &(result->oriented));
	result->edges = calloc(result->m,sizeof(Edge *));
	result->vertices = calloc(result->n, sizeof(Vertex *));
	int i=0;
	int id,nbNeighbors;
	char *label=calloc(255,sizeof(char));
	while(i++<result->n){
		memset(line,'\0',255);
		memset(label,'\0',255);
		fgets(line,255,f);
		sscanf(line, " %d %d %s", &id, &nbNeighbors, label);
		result->vertices[id] = allocVertex(id, strdup(label), NULL, 
		nbNeighbors, NULL);
	}
	i=0;
	int u,v;
	char *sid=calloc(255, sizeof(char));
	double weight;
	while(i++<result->m){
		memset(line,'\0',255);
		memset(label,'\0',255);
		memset(sid,'\0',255);
		fgets(line, 255, f);
		sscanf(line, " %d %d %d %s %lf", &id, &u, &v, label, &weight);
		sprintf(sid,"%d",id);
		result->edges[id] = allocEdge(id, u, v, strdup(label), weight);
		result->vertices[u]->neighbors = addElement(
			result->vertices[u]->neighbors, result->edges[id], 
			result->edges[id]->id,
			result->edges[id]->label);
		//result->vertices[u]->nbNeighbors++;
		result->vertices[v]->neighbors = addElement(
			result->vertices[v]->neighbors, result->edges[id],
			result->edges[id]->id,
			result->edges[id]->label);
		//result->vertices[v]->nbNeighbors++;
	}
	free(sid);
	free(line);
	fclose(f);
	return result;
}

void saveGraph(Graph *g, char *filename){
	FILE *f = fopen(filename, "w");
	if(!f){
		fprintf(stderr, "Warning : Can't open the file %s\n", filename);
		return ;
	}
	fprintf(f, "%d %d %d\n", g->n, g->m, g->oriented);
	int i;
	Vertex *v =NULL;
	for(i=0;i<g->n;i++){
		v=g->vertices[i];
		fprintf(f, "%d %d %s\n", v->id, v->nbNeighbors, 
		(v->label && strlen(v->label))?v->label:"None");
	}
	Edge *e=NULL;
	for(i=0;i<g->m;i++){
		e=g->edges[i];
		fprintf(f, "%d %d %d %s %lf\n", e->id, e->u, e->v,
		 (e->label && strlen(e->label))?e->label:"None", e->weight);
	}
}

void drawGraph(Graph *g, char *filename){
	char *fn=calloc(255,sizeof(char));
	sprintf(fn,"%s.ps",filename);
	FILE *f=fopen(fn, "w");
	free(fn);
	if (!f){
		fprintf(stderr, "Warning : Can't open the file %s\n", filename);
		return;
	}
	fprintf(f,"digraph G {\n");
	int i;
	Vertex *u=NULL,*v=NULL;
	Edge *e=NULL;
	char *s_idu = calloc(32,sizeof(char)),*s_idv=calloc(32,sizeof(char));
	char *s_ew = calloc(32, sizeof(char));
	for(i=0; i<g->m; i++){
		e=g->edges[i];
		u=g->vertices[e->u];
		v=g->vertices[e->v];
		sprintf(s_ew, "%f", e->weight);
		sprintf(s_idu, "%d", u->id);
		sprintf(s_idv, "%d", v->id);
		fprintf(f, "%s -> %s [ label=\"%s\" %s]\n",
		 (u->label && strlen(u->label) && strcmp(u->label,"None"))?
		 u->label:s_idu,
		 (v->label && strlen(v->label) && strcmp(v->label,"None"))?
		 v->label:s_idv,
		 (e->label && strlen(e->label) && strcmp(e->label,"None"))?
		 e->label:s_ew,
		 (g->oriented)?"":"dir=\"both\"");
	}
	for(i=0; i<g->n; i++)if(g->vertices[i]->nbNeighbors==0){
		//Isolated vertices need to be drawen
		u=g->vertices[i];
		sprintf(s_idu, "%d", u->id);
		fprintf(f, " %s",
		 (u->label && strlen(u->label) && strcmp(u->label, "None"))?
		 u->label:s_idu);
	}
	free(s_ew);
	free(s_idu);
	free(s_idv);
	fprintf(f,"}");
	fclose(f);
	char *cmd = calloc(255,sizeof(char));
	sprintf(cmd, "dot -Tps  %s.ps -o %s", filename, filename);
	system(cmd);
	memset(cmd,'\0',255);
	sprintf(cmd,"rm -f %s.ps",filename);
	system(cmd);
	memset(cmd,'\0',255);
	sprintf(cmd,"xdg-open %s",filename);
	system(cmd);
}

void freeGraph(Graph *g){
	if(g){
		int i;
		for(i=0; i<g->n; i++){
			free(g->vertices[i]->label);
			freeList(g->vertices[i]->neighbors);
			free(g->vertices[i]);
		}
		free(g->vertices);
		for(i=0; i<g->m; i++){
			free(g->edges[i]->label);
			free(g->edges[i]);
		}
		free(g->edges);
		free(g);
	}
}

void browseGraphDepth(Graph *g, void (*f)(void *)){
	char *visit = calloc(g->n, sizeof(char));
	int begining=0;
	void *currentElement=NULL;
	Vertex *neighbour=NULL,*currentVertex=NULL;
	Edge *currentEdge=NULL;
	List neighbours=NULL;
	Stack *s = allocStack(-1);
	while(1){
		begining=0;
		while(begining<g->n){
			if(visit[begining]==0)break;
			begining++;
		}
		if(begining==g->n)break;
		s=reinitialize(s);
		visit[begining]=1;
		push(s,g->vertices[begining]);
		while(!emptyStack(s)){
			currentElement=pop(s);
			f(currentElement);
			currentVertex =(Vertex*)currentElement;
			neighbours = currentVertex->neighbors;
			while(neighbours){
				currentEdge = (Edge *)(neighbours->element);
				if(currentEdge->u==currentVertex->id)
					neighbour=g->vertices[currentEdge->v];
				else if(currentEdge->v==currentVertex->id)
					neighbour=g->vertices[currentEdge->u];
				else{
					fprintf(stderr, "Warning : Incoherent graph browsed\n");
					return;
				}
				if(visit[neighbour->id]==0){
					visit[neighbour->id]=1;
					push(s, g->vertices[neighbour->id]);
				}
				neighbours=neighbours->next;
			}
		}
	}
}

void auxDepth(Graph *g, int i, void (*f)(void *), char *visit){
	Vertex *neighbor=NULL,*v=g->vertices[i];
	Edge *currentEdge=NULL;
	f(v->content);
	
	List neighbors=v->neighbors;
	while(neighbors){
		currentEdge = (Edge *)(neighbors->element);
		if(currentEdge->u==i)neighbor = g->vertices[currentEdge->v];
		else if(currentEdge->v==i)neighbor = g->vertices[currentEdge->u];
		else {
			fprintf(stderr, "Warning : illogical graph\n");
			return ;
		}
		if(visit[neighbor->id]==0){
			auxDepth(g, neighbor->id, f, visit);
		}
		neighbors = neighbors->next;
	}
}

void browseGraphDepthRecursive(Graph *g, void (*f)(void *)){
	char  *visit = calloc(g->n, sizeof(char));
	int debut=0;
	while(1){
		while(debut < g->n){
			if(visit[debut]==0)break;
			debut++;
		}
		if(debut == g->n)break;
		auxDepth(g, debut, f, visit);
	}
	free(visit);
}

void browseGraphWidth(Graph *g, void (*f)(void *)){
	char *visit = calloc(g->n, sizeof(char));
	int begining=0;
	void *currentElement=NULL;
	Vertex *neighbour=NULL,*currentVertex=NULL;
	Edge *currentEdge=NULL;
	List neighbours=NULL;
	Queue *s = allocQueue(-1);
	while(1){
		begining=0;
		while(begining<g->n){
			if(visit[begining]==0)break;
			begining++;
		}
		if(begining==g->n)break;
		s=reinitializeQueue(s);
		visit[begining]=1;
		enqueue(s,g->vertices[begining]);
		while(!emptyQueue(s)){
			currentElement=dequeue(s);
			f(currentElement);
			currentVertex =(Vertex*)currentElement;
			neighbours = currentVertex->neighbors;
			while(neighbours){
				currentEdge = (Edge *)(neighbours->element);
				if(currentEdge->u==currentVertex->id)
					neighbour=g->vertices[currentEdge->v];
				else if(currentEdge->v==currentVertex->id)
					neighbour=g->vertices[currentEdge->u];
				else{
					fprintf(stderr, "Warning : Incoherent graph "
					"browsed\n");
					return;
				}
				if(visit[neighbour->id]==0){
					visit[neighbour->id]=1;
					enqueue(s, g->vertices[neighbour->id]);
				}
				neighbours=neighbours->next;
			}
		}
	}
}

int containsCycleRec(Graph *g, int pere, int r,char *visit){
	int detected=0;
	visit[r]=1;
	List neighbors=NULL;
	int neighbor;
	Edge *cur_edge=NULL;
	neighbors = g->vertices[r]->neighbors;
	while(neighbors && !detected){
		cur_edge = (Edge *)neighbors->element;
		if(cur_edge->u==r)neighbor=cur_edge->v;
		else if(cur_edge->v==r)neighbor=cur_edge->u;
		else{fprintf(stderr,"illogical graph\n");return 0;}
		if(neighbor != pere || g->oriented){
			if(visit[neighbor]==1){
				detected = 1;
			}else if(visit[neighbor]==0){
				detected = containsCycleRec(g, r, neighbor, visit);
			}
		}
		neighbors=neighbors->next;
	}
	visit[r]=2;
	return detected;	
}
int containsCycle(Graph *g){
	if(!g)return 0;
	char *visit=calloc(g->n, sizeof(char));
	int deb=0;
	while(1){
		deb=0;
		while(deb<g->n && visit[deb]!=0)deb++;
		if (deb==g->n)break;				
		if(containsCycleRec(g, -1, deb, visit))return 1;
	}
	return 0;
}

Graph *generateRandomGraph(int numberVertices){
	Graph *result = calloc(1, sizeof(Graph));
	result->oriented=1;
	result->n = numberVertices;
	result->vertices = calloc(numberVertices, sizeof(Vertex *));
	int i=0,j=0,v,u;
	while(numberVertices>0){
		if(!result->vertices[i]){
			result->vertices[i] = 
			allocVertex(i, NULL, NULL, 0, NULL);
		}
		numberVertices--;
		if(rand()%100 < 40){
			v = rand() % result->n;
			while(v==i)v=rand() % result->n;
			Edge *check=NULL,*e=NULL;
			List p=NULL;
			if(result->vertices[v]){
				p = result->vertices[v]->neighbors;
				while(p){
					check = (Edge *)p->element;
					if(check && ((v==check->v && i==check->u)|| 
					(v==check->u && i==check->v))){
						break;
					}
					p=p->next;
				}
				if(!check){
					e = allocEdge(j++, i, v, NULL, rand()%1000);
					addEdge(result, e);
					result->vertices[i]->nbNeighbors++;
					result->vertices[i]->neighbors =
					addElement(result->vertices[i]->neighbors, e, 0, NULL);	
					result->vertices[v]->nbNeighbors++;
					result->vertices[v]->neighbors = 
					addElement(result->vertices[v]->neighbors, 
					e, 0, NULL);
				}else free(e);
			}else{
				result->vertices[v] = 
				allocVertex(v, NULL, NULL, 0, NULL);
				e = allocEdge(j++, i, v, NULL, rand()%1000);
				addEdge(result, e);
				result->vertices[i]->nbNeighbors++;
				result->vertices[i]->neighbors =
				addElement(result->vertices[i]->neighbors, e, 0, NULL);
				result->vertices[v]->nbNeighbors = 1;
				result->vertices[v]->neighbors = 
				addElement(result->vertices[v]->neighbors, e, 
				0, NULL);
			}
		}
		i++;
	}
	numberVertices = result->n * 4;
	while(numberVertices-->0){
		if(rand()%100 < 30){
			u = rand()%result->n;
			v = rand()%result->n;
			while(u==v)v=rand()%result->n;
			for(j=0;j<result->m;j++){
				if( result->edges[j] &&
				((result->edges[j]->u==u && 
				result->edges[j]->v==v)
				||(result->edges[j]->u==v && 
				result->edges[j]->v==u) ))break;
			}if(j==result->m){
				addEdge(result, allocEdge(result->m, u, v, 
				NULL, rand()%1000));
				result->vertices[u]->nbNeighbors++;
				result->vertices[v]->nbNeighbors++;
				result->vertices[u]->neighbors = 
				addElement(result->vertices[u]->neighbors, 
				result->edges[result->m-1],0, NULL);
				result->vertices[v]->neighbors = 
				addElement(result->vertices[v]->neighbors, 
				result->edges[result->m-1], 0, NULL);
			}
		}
	}
	return result;
}

void updateBorder(Heap *bord, Graph *g, int s, int *seen, int *lambda, 
	int *targets){
	List neighbors = g->vertices[s]->neighbors;
	Edge *curEdge=NULL;
	Vertex *neighbor=NULL;
	while(neighbors){
		curEdge = neighbors->element;
		if(g->oriented==0){
			if(curEdge->u == s)neighbor = g->vertices[curEdge->v];
			else if(curEdge->v == s)neighbor = g->vertices[curEdge->u];
			else{
				fprintf(stderr, "Warning : illogic graph\n");
				return;
			}
		}else{
			neighbor = g->vertices[curEdge->v];
		}
		if(seen[neighbor->id]==0){

			if((lambda[neighbor->id]==-1) ||
			 (lambda[neighbor->id] > 
			 lambda[s] + curEdge->weight)){
				lambda[neighbor->id] = lambda[s] + curEdge->weight;
				targets[neighbor->id] = s;
				int i;
				for(i=1; i<=bord->heap[0]->id; i++){
					if(
						bord->heap[i] && 
						(*((int*)(bord->heap[i]->element))==neighbor->id)
					){
						bord->heap[i]->id = lambda[neighbor->id];
						ascend(bord, i, NULL);
						break;
					}
				}
				if(i > bord->heap[0]->id)
				insert(bord, &(neighbor->id), lambda[neighbor->id], NULL);
			}
		}
		neighbors = neighbors->next;
	}
}

void dijkstraSmallestTarget(Graph *g, int origin, int *lambda,
 int *targets){
	 if(g==NULL){
		 fprintf(stderr, "Warning : you try to apply Dijkstra "
		 "algorithm on a NULL graph\n");
		 return ;
	 }
	int i, *min;
	int *seen=calloc(g->n, sizeof(int));
	for(i=0;i<g->n; i++){
		lambda[i] = -1;
		targets[i] = -1;
	}
	Heap *border = allocHeap(g->n+1, -1);
	lambda[origin] = 0;
	insert(border, &origin, 0, NULL);
	seen[origin]=1;
	while(border->heap[0]->id > 0){
		min = minHeap(border);
		removeMinHeap(border, NULL);
		seen[*min] = 1;
		updateBorder(border, g, *min, seen, lambda, targets);
	}
}

void findAllPathsRec(Graph *g, int from, int to, int *visited, 
	List *currentPath, List *result){
	visited[from] = 1;
	*currentPath = addElement(*currentPath, NULL, g->vertices[from]->id, NULL);
	if (from==to){
		*result = addElement(*result, invertList( *currentPath), 0, NULL);
		//printList(invertList(*currentPath));
	}else{
		List neighbors = g->vertices[from]->neighbors;
		Edge *curEdge=NULL;
		Vertex *neighbor=NULL;
		while(neighbors){
			curEdge = neighbors->element;
			if(g->oriented==0){
				if(curEdge->u == from)neighbor = g->vertices[curEdge->v];
				else if(curEdge->v == from)neighbor = g->vertices[curEdge->u];
				else{
					fprintf(stderr, "Warning : illogic graph\n");
					return;
				}
			}else{
				neighbor = g->vertices[curEdge->v];
			}
			if(visited[neighbor->id]==0){
				findAllPathsRec(g, neighbor->id, to, visited, currentPath, result);
			}
			neighbors = neighbors->next;
		}
	}
	//printList(*currentPath);
	*currentPath = removeElementByIndex(*currentPath, 0);
	visited[from] = 0;
}
List findAllPaths(Graph *g, int from, int to){
	if(g==NULL){
		fprintf(stderr, "Warning : we try to find path in a NULL graph\n");
		return NULL;
	}
	List result =  NULL;
	int *visited = calloc(g->n, sizeof(int));
	List currentPath = NULL;
	findAllPathsRec(g, from, to, visited, &currentPath, &result);
	return result;
}

List findAPathRec(Graph *g, int from, int to, int *visited, List currentPath){
	visited[from] = 1;
	currentPath = addElement(currentPath, NULL, g->vertices[from]->id, NULL);
	if (from==to){
		//printList(currentPath);
		return duplicateList( currentPath);	
	}else{
		List neighbors = g->vertices[from]->neighbors;
		Edge *curEdge=NULL;
		Vertex *neighbor=NULL;
		while(neighbors){
			curEdge = neighbors->element;
			if(g->oriented==0){
				if(curEdge->u == from)neighbor = g->vertices[curEdge->v];
				else if(curEdge->v == from)neighbor = g->vertices[curEdge->u];
				else{
					fprintf(stderr, "Warning : illogic graph\n");
					return NULL;
				}
			}else{
				neighbor = g->vertices[curEdge->v];
			}
			if(visited[neighbor->id]==0){
				List res = findAPathRec(g, neighbor->id, to, visited, currentPath);
				if(res != NULL)return res;
			}
			neighbors = neighbors->next;
		}
	}
	freeList(currentPath);
	return NULL;
}

List findAPath(Graph *g, int from, int to){
	if(g==NULL){
		fprintf(stderr, "Warning : we try to find path in a NULL graph\n");
		return NULL;
	}
	int *visited = calloc(g->n, sizeof(int));
	List currentPath = NULL;
	return invertList(findAPathRec(g, from, to, visited, currentPath));

}

Flood *allocFlood(Graph *g, int departure, int arrival){
	if(g==NULL){
		fprintf(stderr, "Warning : We try to alloc a flood from a NULL"
		" graph\n");
		return NULL;
	}
	Flood *result = calloc(1, sizeof(Flood));
	result->network = g;
	result->floodVect = calloc(g->m, sizeof(double));
	result->departure = departure;
	result->arrival = arrival;
	return result;
}

Flood *readFloodFromGraphFile(char *filename, int departure, int arrival){
	if(filename==NULL){
		fprintf(stderr, "Warning : We try to read a flood from"
		" a NULL filename\n");
		return NULL;
	}
	Graph *g = readGraphFromFile(filename);
	if(g==NULL){
		fprintf(stderr, "Error : Error when we read a graph from file");
		return NULL;
	}
	return allocFlood(g, departure, arrival);
}

Graph *buildGapGraph(Flood *f){
	if(f==NULL){
		fprintf(stderr, "Warning : We try to build the gap graph from"
		" invalid arguments\n");
		return NULL;
	}
	Graph *result = calloc(1, sizeof(Graph));
	result->oriented = 1;
	result->n = f->network->n;
	result->vertices = calloc(result->n, sizeof(Vertex *));
	int i;
	for(i=0; i<result->n; i++){
		result->vertices[i] = calloc(1, sizeof(Vertex));
		result->vertices[i]->id = f->network->vertices[i]->id;
		result->vertices[i]->nbNeighbors = 0;
		result->vertices[i]->neighbors = NULL;
		result->vertices[i]->label = NULL;
		result->vertices[i]->content = NULL;
	}
	result->m = 0;
	result->edges = NULL;
	for(i=0; i<f->network->m; i++){
		if(f->floodVect[i]>0){
			addEdge(result, allocEdge(i, f->network->edges[i]->v,
			 f->network->edges[i]->u, strdup("None"), f->floodVect[i]));
			result->vertices[result->edges[result->m-1]->v]->nbNeighbors++;
			result->vertices[result->edges[result->m-1]->v]->neighbors =
			addElement(result->vertices[result->edges[result->m-1]->v]->neighbors,
			result->edges[result->m-1], result->edges[result->m-1]->id, 
			result->edges[result->m-1]->label);
		}if(f->floodVect[i]<f->network->edges[i]->weight){
			addEdge(result, allocEdge(i, f->network->edges[i]->u,
			f->network->edges[i]->v, NULL, 
			f->network->edges[i]->weight - f->floodVect[i] ));
			result->vertices[result->edges[result->m-1]->u]->nbNeighbors++;
			result->vertices[result->edges[result->m-1]->u]->neighbors =
			addElement(result->vertices[result->edges[result->m-1]->u]->neighbors,
			result->edges[result->m-1], result->edges[result->m-1]->id, 
			result->edges[result->m-1]->label);
		}
	}
	return result;
}

List fromVerticesToEdges(Graph *g, List path){
	if(g==NULL || path==NULL || g->oriented==0){
		fprintf(stderr, "Warning you call fromVerticesToEdges with wrong args\n");
		return NULL;
	}
	//printList(path);
	List result=NULL;
	Vertex *currentVertex=NULL;
	Edge * currentEdge = NULL;
	List neighbors=NULL;
	while(path && path->next){
		currentVertex = g->vertices[path->id];
		neighbors = currentVertex->neighbors;
		while(neighbors){
			currentEdge = neighbors->element;
			if(currentEdge->u != path->id){
				fprintf(stderr, "Error : %d %d incoherent graph or path used\n",currentEdge->u, path->id);
				return NULL;
			}
			if(currentEdge->v == path->next->id){
				result = addElement(result, currentEdge, currentEdge->u, NULL);
				break;
			}
			neighbors = neighbors->next;
		}
		if(neighbors == NULL){
				fprintf(stderr, "Ersror : %d %d incoherent graph or path used\n",currentEdge->u, path->id);
				return NULL;
		}
		path = path->next;
	}
	return invertList(result);
}

double minValuation(List path){
	if(path==NULL){
		fprintf(stderr, "Warning : you try to get the min valuation of"
		" a NULL path\n");
		return -1;
	}
	double min = ((Edge *)path->element)->weight;
	path = path->next;
	while(path){
		if(min > ((Edge *)path->element)->weight)
		min = ((Edge *)path->element)->weight;
		path = path->next;
	}
	return min;
}

Flood *fordFulkerson(Graph *g, int departure, int arrival){
	//char *gN = calloc(25, sizeof(char));
	//int i=1;
	Flood *f = allocFlood(g, departure, arrival);
	Graph *gapGraph = buildGapGraph(f);
	List pathsAsVertices = findAllPaths(gapGraph, f->departure, f->arrival);
	List curPathVert = NULL;
	List pathAsEdges = NULL;
	List curPathEdges= NULL;
	Edge *curEdge = NULL;
	double min = 0;
	while(pathsAsVertices){
		//printf("hii\n");
		curPathVert = pathsAsVertices;
		while(curPathVert){
			pathAsEdges = fromVerticesToEdges(gapGraph, curPathVert->element);
			/*List tst=pathAsEdges;
			while(tst){
				printf("%f %d  %d| ",((Edge*)tst->element)->weight, tst->id, ((Edge*)tst->element)->id);
				tst=tst->next;
			} */
			min = minValuation(pathAsEdges);
			//printf("\n%f\n", min);
			curPathEdges = pathAsEdges;
			while(curPathEdges){
				curEdge = curPathEdges->element;
				if(curEdge->label == NULL){
					//printf(" %d : %f to %f\n",curEdge->id,f->floodVect[curEdge->id],f->floodVect[curEdge->id]+min);
					f->floodVect[curEdge->id] += min;
					gapGraph->edges[curEdge->id]->weight -= min;
				}else if(strcmp("None", curEdge->label)==0){
					//printf(" %d : %f to %f\n",curEdge->id,f->floodVect[curEdge->id],f->floodVect[curEdge->id]-min);
					f->floodVect[curEdge->id] -= min;
					gapGraph->edges[curEdge->id]->weight += min;
				}else{
					fprintf(stderr, "Warning : illogical manipulation in"
					" ford fulkerson algorithm\n");
					return NULL;
				}
				curPathEdges = curPathEdges->next;
			}
			curPathVert = curPathVert->next;
			freeList(pathAsEdges);
			pathAsEdges = NULL;
		}
		gapGraph = buildGapGraph(f);
		//sprintf(gN, "%d", i++);
		//drawGraph(gapGraph, gN);
		//drawFlood(f, gN);
		freeList(pathsAsVertices);
		pathsAsVertices = NULL;
		pathsAsVertices = findAllPaths(gapGraph, f->departure, f->arrival);
	} 
	/* List pathAsVertices = findAPath(gapGraph, departure, arrival);
	//printList(pathAsVertices);
	List pathAsEdges = NULL;
	List curElementEdge = NULL;
	Edge *curEdge = NULL;
	double min;
	while(pathAsVertices){	
		//printList(pathAsVertices);
		pathAsEdges = fromVerticesToEdges(gapGraph, pathAsVertices);
		min = minValuation(pathAsEdges);
		curElementEdge = pathAsEdges;
		while(curElementEdge){
				curEdge = curElementEdge->element;
				if(curEdge->label == NULL){
					//printf(" %d : %f to %f\n",curEdge->id,f->floodVect[curEdge->id],f->floodVect[curEdge->id]+min);
					f->floodVect[curEdge->id] += min;
				}else if(strcmp("None", curEdge->label)==0){
					//printf(" %d : %f to %f\n",curEdge->id,f->floodVect[curEdge->id],f->floodVect[curEdge->id]-min);
					f->floodVect[curEdge->id] -= min;
				}else{
					fprintf(stderr, "Warning : illogical manipulation in"
					" ford fulkerson algorithm\n");
					return NULL;
			}
			curElementEdge = curElementEdge->next;
		}
		//freeGraph(gapGraph);
		gapGraph = NULL;
		gapGraph = buildGapGraph(f);
		//freeList(pathAsVertices);
		pathAsVertices = NULL;
		pathAsVertices = findAPath(gapGraph, departure, arrival);
	}
//	drawGraph(gapGraph, "a"); */
	return f;
}

void drawFlood(Flood *flood, char *filename){

	if( flood==NULL || filename==NULL ){
		fprintf(stderr, "Warning : We try to draw a flood with wrong arguments\n");
		return;
	}
	char *cmd = calloc(255,sizeof(char));
	sprintf(cmd, "%s.ps",filename);	
	FILE *f = fopen(cmd, "w");
	memset(cmd, '\0', 255);
	if(f==NULL){
		fprintf(stderr, "Error : we can't open %s\n",filename);
		return ;
	}
	fprintf(f, "digraph G{\n");
	int i;
	char *s_idu = calloc(25, sizeof(char));
	char *s_idv = calloc(25, sizeof(char));
	for(i=0; i<flood->network->m; i++){
		sprintf(s_idu, "%d", flood->network->vertices[flood->network->edges[i]->u]->id);
		sprintf(s_idv, "%d", flood->network->vertices[flood->network->edges[i]->v]->id);
		fprintf(f,"%s -> %s [ label=\"%f/%f\"]\n", 
		((flood->network->vertices[flood->network->edges[i]->u]->label)
		&&(strcmp(flood->network->vertices[flood->network->edges[i]->u]->label, "None")
		!=0) 	
		)?
		flood->network->vertices[flood->network->edges[i]->u]->label:s_idu,
		((flood->network->vertices[flood->network->edges[i]->v]->label)
		&&(strcmp(flood->network->vertices[flood->network->edges[i]->v]->label, "None")
		!=0)		
		)?
		flood->network->vertices[flood->network->edges[i]->v]->label:s_idv,
		flood->floodVect[i],
		flood->network->edges[i]->weight
		);
	}
	free(s_idu);
	free(s_idv);
	fprintf(f, "}\n");
	fclose(f);
	sprintf(cmd, "dot -Tps  %s.ps -o %s", filename, filename);
	system(cmd);
	memset(cmd,'\0',255);
	sprintf(cmd,"rm -f %s.ps",filename);
	system(cmd);
	memset(cmd,'\0',255);
	sprintf(cmd,"xdg-open %s",filename);
	system(cmd);
}