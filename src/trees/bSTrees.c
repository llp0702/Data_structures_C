#include "headers/bSTrees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Btree *minBST(Btree *bt){
	if(bt){
		while(bt->left)bt=bt->left;
		return bt;
	}return NULL;
}

Btree *maxBST(Btree *bt){
	if(bt){
		while(bt->right)bt=bt->right;
		return bt;
	}return NULL;
}

int checkIfBST(Btree *bt){
	if(!bt)return 1;
	if(bt->left){
		if(!checkIfBST(bt->left))return 0;	
		if(bt->height<=maxBST(bt->left)->height)return 0;
	}
	if(bt->right){
		if(!checkIfBST(bt->right))return 0;	
		if(bt->height>=minBST(bt->right)->height)return 0;	
	}
	return 1;
}

Btree *containsBtsId(Btree *bt, int id){
	if(!bt)return NULL;
	if(bt->id==id)return bt;
	if(bt->id>id)return containsBtsId(bt->left, id);
	return containsBtsId(bt->right, id);
}

Btree *insertBts(Btree *bt, int id, char *label, void *content){
	if(!bt){
		Btree *res=allocBtree(id, label, content,
		NULL, NULL, NULL);
		return res;
	}
	if(bt->id>id){
		bt->left = insertBts(bt->left, id, label, content);
		bt->left->father = bt;
		if(bt->right){
			if(bt->right->height < bt->left->height)bt->height++;
		}else bt->height++;
	}else{
		bt->right = insertBts(bt->right, id, label, content);
		bt->right->father = bt;
		if(bt->left){
			if(bt->left->height < bt->right->height)bt->height++;
		}else bt->height++;
	}
	return bt;
}

Btree *removeBtsMaxId(Btree *bt, int *id, char **label, void **content){
	if(bt){
		Btree *origin=bt;
		while(bt->right)bt=bt->right;
		bt->father->right = NULL;
		*id=bt->id;
		*label=bt->label;
		*content=bt->content;
		free(bt);
		return origin;
	}return NULL;
}

Btree *removeBtsMinId(Btree *bt, int *id, char **label, void **content){
	if(bt){
		Btree *origin=bt;
		while(bt->left)bt=bt->left;
		bt->father->left = NULL;
		*id=bt->id;
		*label=bt->label;
		*content=bt->content;
		free(bt);
		return origin;
	}return NULL;
}

Btree *removeBtsId(Btree *bt, int id){
	if(!bt)return bt;
	Btree *origin = bt;
	while(bt && bt->id != id){
		if(bt->id > id)bt = bt->left;
		else bt=bt->right;
	}
	if(bt){//so bt->id == id
		if(!bt->left && bt->right){
			if(bt->father->left==bt){
			bt->father->left = bt->right;}
			else{ bt->father->right = bt->right;} 
			bt->right->father = bt->father;
			free(bt);
		}else if(!bt->right && bt->left){
			if(bt->father->left==bt){
			bt->father->left = bt->left;}
			else {bt->father->right = bt->left;}
			bt->left->father = bt->father;
			free(bt);
		}else if(!bt->left && !bt->right){
			if(bt->father->left==bt)
			bt->father->left=NULL;
			else bt->father->right=NULL;
			free(bt);
		}else{
			bt->left = removeBtsMaxId(bt->left, &(bt->id),
			&(bt->label), &(bt->content));
		}
	}
	return origin;
}

Btree *generateRandomBSTree(int numberElements){
	Btree *res = NULL;
	while(numberElements--){
		res = insertBts(res, rand(), NULL, NULL);
	}
	return res;
}

Btree *readBSTreeFromFile(char *filename){
	FILE *f = fopen(filename, "r");
	char *line = calloc(255, sizeof(char));
	fgets(line, 255, f);
	int nbElements = atoi(line);
	int id;
	char *label=calloc(50, sizeof(char));
	Btree *result=NULL;
	while(nbElements>0 && !feof(f)){
		fgets(line, 255, f);
		sscanf(line, " %d %s", &id, label);
		result = insertBts(result, id,(label && strcmp(label,"NULL"))?label:NULL, NULL);
		nbElements--;
	}
	return result;
}

void auxSaveBSTree(Btree *bt, FILE *f){
	if(!bt)return;
	fprintf(f, "%d %s\n", bt->id, (bt->label)?bt->label:"NULL");
	auxSaveBSTree(bt->left, f);
	auxSaveBSTree(bt->right, f);
}
void saveBSTree(Btree *bt, char *filename){
	if(!bt)return;
	FILE *f=fopen(filename, "w");
	if(!f){
		fprintf(stderr, "Error : Can not open %s\n", filename);
	}
	int nbElements = sizeBtree(bt);
	fprintf(f, "%d\n",nbElements);
	auxSaveBSTree(bt, f);
	fclose(f);
}