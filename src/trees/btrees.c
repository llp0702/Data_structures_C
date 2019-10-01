#include "headers/btrees.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Btree *allocBtree(int id, char *label, void *content, 
	Btree *left, Btree *right, Btree *father){
		Btree *res = malloc(sizeof(Btree));
		res->id=id;
		res->label=label;
		res->content = content;
		res->left = left;
		res->right=right;
		res->father=father;
		res->height=1+max((left)?left->height:0,(right)?right->height:0);
		return res;
}

void browsePrefix(Btree *bt, void(*f)(Btree *)){
	if(bt){
		f(bt);
		browsePrefix(bt->left, f);
		browsePrefix(bt->right, f);
	}
}

void browseSuffix(Btree *bt, void(*f)(Btree *)){
	if(bt){
		browseSuffix(bt->left, f);
		browseSuffix(bt->right, f);
		f(bt);
	}
}

void browseInorder(Btree *bt, void(*f)(Btree *)){
	if(bt){
		browseInorder(bt->left, f);
		f(bt);
		browseInorder(bt->right, f);
	}
}

int sizeBtree(Btree *bt){
	if(bt){
		return 1 + sizeBtree(bt->left) + sizeBtree(bt->right);
	}return 0;
}

int heightBtree(Btree *bt){
	if(bt){
		return 1 + max(heightBtree(bt->left),heightBtree(bt->right));
	}
	return 0;
}

void removeBtree(Btree *bt){
	if(bt){
		removeBtree(bt->left);
		removeBtree(bt->right);
		free(bt);
	}
}

Btree *copyBtree(Btree *bt){
	if(bt){
		return allocBtree(bt->id, bt->label, bt->content, 
		copyBtree(bt->left), copyBtree(bt->right), bt->father);
	}return NULL;
}

Btree *containsBtId(Btree *bt, int id){
	if(!bt)return NULL;
	if(bt->id==id)return bt;
	Btree *res=containsBtId(bt->left, id);
	if(res)return res;
	res=containsBtId(bt->right, id);
	return res;
}

Btree *containsBtLabel(Btree *bt, char *label){
	if(!bt)return NULL;
	if(label && bt->label && !strcmp(bt->label, label))return bt;
	Btree *res=containsBtLabel(bt->left, label);
	if(res)return res;
	res=containsBtLabel(bt->right, label);
	return res;
}

Btree *containsBtElement(Btree *bt, void *element){
	if(!bt)return NULL;
	if(element == bt->content)return bt;
	Btree *res=containsBtLabel(bt->left, element);
	if(res)return res;
	res=containsBtLabel(bt->right, element);
	return res;
}

Btree *generateRandomBtree(int numberElements){
	if(numberElements==0)return NULL;
	if(numberElements==1)return allocBtree(rand(),NULL,NULL,NULL,NULL,NULL);
	Btree *res = allocBtree(rand(), NULL, NULL, NULL, NULL, NULL);
	res->left = generateRandomBtree(numberElements/2);
	if(res->left)res->left->father = res;
	res->right = generateRandomBtree(numberElements-numberElements/2);
	if(res->right)res->right->father = res;
	return res;
}

void auxDraw(Btree *bt, FILE *f){
	if(bt){
		char *labelFather=NULL, *labelLeft=NULL, *labelRight=NULL, *tmp=NULL;
		tmp=calloc(20, sizeof(char));
		if(bt->label!=NULL)labelFather=strdup(bt->label);
		else{
			sprintf(tmp, "%d", bt->id);
			labelFather = strdup(tmp);
			memset(tmp, '\0', 20);
		}
		if(bt->left!=NULL){
			if(bt->left->label)labelLeft = strdup(bt->left->label);
			else{
				sprintf(tmp, "%d", bt->left->id);
				labelLeft = strdup(tmp);
				memset(tmp, '\0', 20);
			}

		}else{
			labelLeft = strdup("NULL");
		}
		if(bt->right!=NULL){
			if(bt->right->label)labelRight = strdup(bt->right->label);
			else{
				sprintf(tmp, "%d", bt->right->id);
				labelRight = strdup(tmp);
				memset(tmp, '\0', 20);
			}
		}else labelRight = strdup("NULL");
		if(strcmp(labelFather,"NULL")){
			fprintf(f, "%s\n",labelFather);
			if(strcmp(labelLeft,"NULL"))fprintf(f, "%s -> %s\n", labelFather, labelLeft);
			if(strcmp(labelRight,"NULL"))fprintf(f, "%s -> %s\n", labelFather, labelRight);
		}else printf("fath : %s\n",labelFather);
		free(labelFather);
		free(labelLeft);
		free(labelRight);
		free(tmp);
		auxDraw(bt->left, f);
		auxDraw(bt->right, f);
	}
}
void drawBtree(Btree *bt, char *filename){
	if(!bt){
		fprintf(stderr, "Warning : NULL Btree\n");
		return;
	}
	FILE *f= fopen(filename, "w");
	if(!f){
		fprintf(stderr, "Error : can not open %s", filename);
		return ;
	}
	fprintf(f, "digraph G {\n");
	auxDraw(bt, f);
	fprintf(f, "}\n");
	fclose(f);
	char *command = calloc(255, sizeof(char));
	sprintf(command, "dot -Tps %s -o %s.out", filename, filename);
	system(command);
	sprintf(command, "xdg-open %s.out", filename);
    system(command);
	return;
}
