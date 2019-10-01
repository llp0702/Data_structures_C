#include "headers/ht.h"
#include <stdlib.h>
#include <stdio.h>

Ht *allocHt(int numberCells, int (*objToInt) (void *), 
	int (*hashFunc)(int)){
	Ht *result = calloc(1, sizeof(Ht));
	result->emptyCells = numberCells;
	result->numberOfCells = numberCells;
	result->table = calloc(numberCells, sizeof(HtCell *));
	result->numberOfElements = 0;
	result->maxNumberOfElements = -1;
	result->maxNumberOfElementsPerCell = -1;
	result->objToInt = objToInt;
	result->hashFunc = hashFunc;
	return result;	
}

int insertHt(Ht *table, void *element){
	if(table!=NULL && element!=NULL){
		int hashed = table->hashFunc(table->objToInt(element))
		% table->numberOfCells;
		if(hashed <0)hashed *=-1;
		printf("%d\n",hashed);
		if(table->maxNumberOfElements != -1 &&
		table->maxNumberOfElements <= table->numberOfElements)return 0;
		if(table->table[hashed]){
			if(table->maxNumberOfElementsPerCell != -1 &&
			 	table->table[hashed]->numberOfElements >= 
				table->maxNumberOfElementsPerCell)return 0;
				table->table[hashed]->numberOfElements++;
		}else{
			table->table[hashed] = calloc(1, sizeof(HtCell));
			table->table[hashed]->numberOfElements = 1;
			table->emptyCells --;
			table->table[hashed]->elements = NULL;
		}
		table->numberOfElements++;
		table->table[hashed]->elements = addElement(table->table[hashed]->elements,
			element, table->objToInt(element), NULL);

		return 1;
	}
	else{
		fprintf(stderr, "Warning : We try to insert an element"
		" in a hashtable with NULL arguments \n");
		return 0;
	}
}

void *searchHt(Ht *table, void *element, int (*equals) (void*, void*)){
	if(!table || !element)return NULL;
	int hash = table->hashFunc(table->objToInt(element))
	% table->numberOfCells;
	if(hash <0)hash *=-1;
	if(table->table[hash]){
		List lst = table->table[hash]->elements;
		while(lst){
			if(equals){
				if(equals(element, lst->element)==0)return lst->element;
			}else{
				if(element == lst->element)return lst->element;
			}
			lst = lst->next;
		}
		return NULL;
	}else{
		return NULL;
	}
}


void removeHt(Ht *table, void *element, int (*equals)(void *, void *)){
	if(table && element){
		int hash = table->hashFunc(table->objToInt(element))
		%table->numberOfCells;
		if(hash <0)hash *=-1;
		char found = 0;
		if(table->table[hash]){
			List lst = table->table[hash]->elements;
			while(lst){
				if(equals){
					if(equals(lst->element, element)==0){
						table->table[hash]->elements = 
						removeElement(table->table[hash]->elements, 
						lst->element);
						found = 1;
					}
				}else{
					if(element==lst->element){
						table->table[hash]->elements = 
						removeElement(table->table[hash]->elements, 
						lst->element);
						found = 1;
					}
				}
				if (found==1){
					table->table[hash]->numberOfElements --;
					table->numberOfElements --;
					if(table->table[hash]->numberOfElements==0){
						table->emptyCells++;
						free(table->table[hash]);
						table->table[hash]=NULL;
					}
					return;
				}
				lst = lst->next;
			}
		}else return ;
	}else{
		fprintf(stderr, "Warning : You try to remove from a Ht with wrong"
		" args\n");
		return;
	}
}

void printHt(Ht *ht, void (*printElem)(void *) ){
	if(!ht)fprintf(stdout, "Print a ht in : NULL\n");
	else{
		fprintf(stdout, "Print a ht in : %p\n", ht);
		fprintf(stdout, "Informations about ht : \n"
		"Number of cells : %d\nNumber of empty cells :"
		"%d\nNumber of elements :%d\nMaximum number of"
		" elements : %d (-1 means unlimited)\nMaximum"
		" number of elements per cell :%d (-1 means "
		"unlimited)\n\nContent : \n", ht->numberOfCells,
		ht->emptyCells, ht->numberOfElements, 
		ht->maxNumberOfElements, 
		ht->maxNumberOfElementsPerCell);
		int i=0;
		for(i=0; i<ht->numberOfCells;i++){
			fprintf(stdout, "****************\n%d : ",i);
			if(ht->table[i]!=NULL){
				List e = ht->table[i]->elements;
				fprintf(stdout, "%p\n",ht->table[i]);
				fprintf(stdout, "Contains %d element\n",
				ht->table[i]->numberOfElements);
				fprintf(stdout, "________________\n");
				if(printElem==NULL){
					fprintf(stdout, "\n\nAdress \t\t Id\n");
				}
				while(e){
					if(printElem != NULL){
						printElem(e->element);
						fprintf(stdout, "\n");
					}else{
						fprintf(stdout, "%p \t %d\n", 
						e->element, e->id);
					}
					e=e->next;
					fprintf(stdout, "________________\n");				
				}
			}else fprintf(stdout, "NULL");
			fprintf(stdout, "\n");
		}
	}
}