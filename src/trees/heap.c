#include "headers/heap.h"
#include <stdlib.h>
#include <stdio.h>
 
Heap *allocHeap(int memorySize, int maximalNumberOfElements){
	if(memorySize<=0){
		fprintf(stderr, "Warning : we try to create a heap"
		"with a non positive memory size");
		return NULL;
	}
	Heap *result = calloc(1, sizeof(Heap));
	result->maximalNumberOfElements =maximalNumberOfElements;
	result->memorySize = memorySize;
	result->heap = calloc(memorySize, sizeof(HeapCell*));
	result->heap[0] = malloc(sizeof(HeapCell));
	result->heap[0]->element = NULL;
	result->heap[0]->id = 0;
	return result;
}

int hasFather(Heap *heap, int index){
	if(heap==NULL)return 0;
	if(index >= heap->memorySize)return 0;
	if(heap->heap[index]==NULL)return 0;
	if(index==1)return 0;
	return 1;
}

int hasLeftSon(Heap *heap, int index){
	if(heap==NULL)return 0;
	if(leftSon(index) > heap->heap[0]->id)return 0;
	if(heap->heap[leftSon(index)]==NULL)return 0;
	return 1;
}

int hasRightSon(Heap *heap, int index){
	if(heap==NULL)return 0;
	if(rightSon(index) > heap->heap[0]->id)return 0;
	if(heap->heap[rightSon(index)]==NULL)return 0;
	return 1;
}

int isLeaf(Heap *heap, int index){
	return (hasRightSon(heap, index)==0 )&& (hasLeftSon(heap, index)==0); 
}

int leftSon(int i){
	return 2*i;
}

int rightSon(int i){
	
	return 2*i+1;

}

int father(int i){
	return i/2;
}

void reinitHeap(Heap *heap){
	if(heap==NULL)return;
	int i;
	for(i=1; i<heap->memorySize; i++){
		if(heap->heap[i]!=NULL){
			free(heap->heap[i]);
			heap->heap[i]=NULL;
		}
	}
	heap->heap[0]->id = 0;
}

void deepRemoveHeap(Heap *heap){
	if(heap==NULL)return;
	int i;
	for(i=1; i<heap->memorySize; i++){
		if(heap->heap[i]!=NULL){
			if(heap->heap[i]->element!=NULL)
			free(heap->heap[i]->element);
			free(heap->heap[i]);
		}
	}
	free(heap->heap[0]);
	free(heap);
}

void removeHeap(Heap *heap){
	reinitHeap(heap);
	if(heap==NULL)return;
	free(heap->heap[0]);
	free(heap->heap);
	free(heap);
	return;
}

void swap(Heap *heap, int i, int j){
	if(heap==NULL)return;
	HeapCell *tmp = heap->heap[i];
	heap->heap[i] = heap->heap[j];
	heap->heap[j] = tmp;
	return;
}

int smallerSon(Heap *heap, int index, 
	int (*compare)(void*, void*)){
	if(isLeaf(heap, index)==1)return -1;
	if(heap==NULL)return -1;
	if(leftSon(index) > heap->heap[0]->id)return rightSon(index);
	if(rightSon(index) > heap->heap[0]->id)return leftSon(index);
	if(heap->heap[leftSon(index)]==NULL)return rightSon(index);
	if(heap->heap[rightSon(index)]==NULL)return leftSon(index);
	if(compare==NULL){
		if(heap->heap[leftSon(index)]->id < 
		heap->heap[rightSon(index)]->id)return leftSon(index);
		else return rightSon(index); 
	}else{
		if(compare(heap->heap[leftSon(index)]->element, 
		heap->heap[rightSon(index)]->element) < 0)
		return leftSon(index);
		else return rightSon(index);
	}
}

void ascend(Heap *heap, int index, int (*compare)(void*, void*)){
	if(heap==NULL)return;
	if(hasFather(heap, index)==0)return;
	int fat = father(index);
	if(compare==NULL){
		if(heap->heap[fat]->id > heap->heap[index]->id){
			swap(heap, fat, index);
			ascend(heap, fat, compare);
		}
	}else{
		if(compare(heap->heap[fat], heap->heap[index])>0){
			swap(heap, fat, index);
			ascend(heap, fat, compare);
		}
	}
	return;
}

void goDown(Heap *heap, int index, int (*compare)(void*, void*)){
	if(heap==NULL)return;
	if(index>=heap->memorySize)return;
	if(index > heap->heap[0]->id)return;
	int lowS = smallerSon(heap, index, compare);
	if(lowS != -1){
		if(compare){
			if(compare(heap->heap[index]->element, 
			heap->heap[lowS]->element)>0){
				swap(heap, index, lowS);
				goDown(heap, lowS, compare);
			}
		}else{
			if(heap->heap[index]->id > heap->heap[lowS]->id){
				swap(heap, index, lowS);
				goDown(heap, lowS, compare);
			}
		}
	}
}

void *minHeap(Heap *heap){
	if(heap==NULL)return NULL;
	if(heap->heap[0]->id==0)return NULL;
	if(heap->heap[1]==NULL)return NULL;
	return heap->heap[1]->element;
}

void insert(Heap *heap, void *element, int id, 
	int (*compare)(void*, void*)){
	if(heap==NULL)return;
	if(heap->heap[0]->id==heap->maximalNumberOfElements)return;
	heap->heap[0]->id++;
	if(heap->memorySize==heap->heap[0]->id){
		heap->heap = realloc(heap->heap, (100+heap->memorySize)*sizeof(HeapCell*));
		heap->memorySize +=100;
	}
	heap->heap[heap->heap[0]->id] = malloc(sizeof(HeapCell));
	heap->heap[heap->heap[0]->id]->id = id;
	heap->heap[heap->heap[0]->id]->element = element;
	ascend(heap, heap->heap[0]->id, compare);
}
void removeMinHeap(Heap *heap, int (*compare)(void*, void*)){
	if(heap==NULL)return;
	if(heap->heap[0]->id==0)return;
	swap(heap, 1, heap->heap[0]->id);
	free(heap->heap[heap->heap[0]->id]);
	heap->heap[heap->heap[0]->id]=NULL;
	heap->heap[0]->id--;
	goDown(heap, 1, compare);
}

void drawHeap(Heap *heap, char* filename){
	if(heap==NULL)return;
	if(filename==NULL)return;
	FILE *f = fopen(filename, "w");
	if(f==NULL)return;
	fprintf(f, "digraph G{\n");

	int i,fat;
	for(i=1;i<=heap->heap[0]->id; i++){
		if(heap->heap[i]){
			if(hasFather(heap, i)){
				fat = father(i);
				fprintf(f, "%d -> %d\n", heap->heap[fat]->id, 
				heap->heap[i]->id );
			}
		}
	}
	fprintf(f, "}\n");
	fclose(f);
	char *command = calloc(255, sizeof(char));
	sprintf(command, "dot -Tps %s -o %s.out", filename, filename);
	system(command);
	sprintf(command, "xdg-open %s.out", filename);
    system(command);
	return;
}

Heap *generateRandomHeap(int nbElements){
	Heap *res = allocHeap(nbElements+1, -1);
	int i=0;
	while(i<nbElements){
		insert(res, NULL, rand()%1000, NULL);
		i++;
	}
	return res;
}