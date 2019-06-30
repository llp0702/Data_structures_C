#include "headers/lists.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

List addElement(List l, void *newElement, int id, char *label){
	ElementOfList *e=malloc(sizeof(ElementOfList));
	if(label){
		e->label = label;
	}else{
		char *cid = calloc(255,sizeof(char));
		sprintf(cid, "%d", id);
		e->label = strdup(cid);
		free(cid);
		cid = NULL;
	}
	e->id = id;
	e->element = newElement;
	e->next = l;
	return e;
}

List removeElement(List l, void *element){
	ElementOfList *prev=NULL,*curr=l;
	while (curr){
		if(curr->element==element){
			if(prev){
				prev->next = curr->next;
				if(curr->label)free(curr->label);
				curr->label = NULL;
				free(curr);
			}else{
				l = l->next;
				if(curr->label)free(curr->label);
				curr->label = NULL;
				free(curr);
			}
			curr=NULL;
			break;
		}
		prev = curr;
		curr=curr->next;
	}
	return l;
}

List removeElementByIndex(List l, int index){
	if(l){
		ElementOfList *e=l,*prev=NULL;
		int i=0;
		while(e && i<index){
			prev = e;
			e=e->next;
			i++;
		}
		if(e){
			if(prev){
				prev->next = e->next;
				if(e->label)free(e->label);
				e->label =NULL;
				free(e);
			}else{
				l=l->next;
				if(e->label)free(e->label);
				e->label =NULL;
				free(e);
			}
			e=NULL;
		}
	}
	return l;
}

List removeElementsPredicate(List l, char (*f)(void *,int, char*), int i){
	ElementOfList *prev=NULL,*curr=l;
	while (curr && i!=0){
		if(f(curr->element, curr->id, curr->label) && (i==-1 || i>0)){
			if(prev){
				prev->next = curr->next;
				if(curr->label)free(curr->label);
				curr->label = NULL;
				free(curr);
			}else{
				l = l->next;
				if(curr->label)free(curr->label);
				curr->label = NULL;
				free(curr);
			}
			curr=prev->next;
			i--;
		}
		prev = curr;
		curr=curr->next;
	}
	return l;
}

void freeList(List l){
	if(l){
		freeList(l->next);
		if(l->label)free(l->label);
		l->label=NULL;
		free(l);
	}
}

List invertList(List l){
	if(l==NULL)return NULL;
	

	List result= NULL;
	while(l){
		result = addElement(result, l->element, 
		l->id, l->label);
		l = l->next;
	}
	return result;
}

void printList(List l){
	char *s_id = calloc(25, sizeof(char));
	while(l){
		sprintf(s_id, "%d", l->id);
		printf("%s | ", (l->label)?l->label:s_id);
		l=l->next;
	}
	printf("\n");
	free(s_id);
	s_id = NULL;
}

List duplicateList(List l){
	if(l){
		List res = addElement(NULL, l->element,
		l->id, l->label);
		res->next = duplicateList(l->next);
		return res;
	}else return NULL;
}
