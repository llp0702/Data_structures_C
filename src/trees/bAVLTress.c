#include "headers/bAVLTress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int balanceValue(Btree *bt){
	return (bt)?(((bt->right)?bt->right->height :0)-((bt->left)?bt->left->height:0)):-1;
}

Btree *removeAvl(Btree *bt, Btree *node){
	if(bt && node){
		Btree *currentNode= NULL;
		if(node->left && node->right){
			removeBtsMaxId(node->left, &(node->id), &(node->label), &(node->content));
			currentNode = node->left;
			if(currentNode){
				while(currentNode->right)currentNode=currentNode->right;
			}else currentNode = node;
		}if(!node->left && !node->right){
			currentNode = node->father;
			if(currentNode){
				if(currentNode->left==node){
					currentNode->left = NULL;
				}else if(currentNode->right==node){
					currentNode->right = NULL;
				}else fprintf(stderr, "Warning : Illogic Btree\n");
				node->father = NULL;
			}else bt=NULL;
			if(node->label)free(node->label);
			free(node);
		}if(!node->left && node->right){
			currentNode = node->father;
			if(currentNode){
				if(currentNode->left==node){
					currentNode->left = node->right;
				}else if(currentNode->right==node){
					currentNode->right = node->right;
				}else fprintf(stderr, "Warning : Illogic Btree\n");
				node->right->father = currentNode;
				node->father = NULL;
			}
			else bt = NULL;
			if(node->label)free(node->label);
			free(node);
		}if(node->left && !node->right){
			currentNode = node->father;
			if(currentNode){
				if(currentNode->left==node){
					currentNode->left = node->left;
				}else if(currentNode->right==node){
					currentNode->right = node->left;
				}else fprintf(stderr, "Warning : Illogic Btree\n");
				node->left->father = currentNode;
				node->father = NULL;
			}
			else bt = NULL;
			if(node->label)free(node->label);
			free(node);
		}
		int lastHeight;
		while(currentNode){
			lastHeight = currentNode->height;
		//	fprintf(stderr, "Update h %d\n",currentNode->id);
			updateHeight(currentNode);
			currentNode = rebalance(currentNode);
			if(!currentNode->father)bt = currentNode;
			currentNode = currentNode->father;
		}
		return bt;
	}else{
		fprintf(stderr, "Warning : Trying to remove from NULL avl btree\n");
		return  NULL;
	}
}

Btree *removeAvlId(Btree *bt, int id){
	if(bt){
		Btree *currentNode = bt;
		while(currentNode){
			if(currentNode->id==id)break;
			else if(currentNode->id>id)currentNode=currentNode->left;
			else currentNode=currentNode->right;
		}if(currentNode){
			bt = removeAvl(bt, currentNode);
		}else{
			fprintf(stderr, "Information : %d id not found inside the Btree\n",id);
		}
		return bt;
	}else {
		fprintf(stderr, "Warning : Trying to remove from NULL avl btree\n");
		return NULL;
	}
}

Btree *insertAvl(Btree *bt, int id, char *label, void *content){
	//fprintf(stderr, "Trying to insert %d\n", id);
	if(!bt)return allocBtree(id, label, content, NULL, NULL, 
	NULL);
	Btree *currentNode=bt;
	while(1){
		if(currentNode->id > id){
			if(currentNode->left){
				currentNode = currentNode->left;
			}else{
				currentNode->left = allocBtree(id, label, 
				content, NULL, NULL, currentNode);
				while(currentNode != NULL){
					updateHeight(currentNode);
					currentNode = rebalance(currentNode);
					if(currentNode)updateHeight(currentNode);
					if(!currentNode->father)bt=currentNode;
					currentNode = currentNode->father;
					if(currentNode && 
					(((currentNode->right)?currentNode->right->height:0)==(
					(currentNode->left)?currentNode->left->height:0)))break;
				}
				break;
			}
		}else if(currentNode->id < id){
			if(currentNode->right){
				currentNode = currentNode->right;
			}else{
				currentNode->right = allocBtree(id, label, 
				content, NULL, NULL, currentNode);
				while(currentNode != NULL){
					updateHeight(currentNode);
					currentNode=rebalance(currentNode);
					if(!currentNode->father)bt=currentNode;
					currentNode = currentNode->father;
					if(currentNode &&
					(((currentNode->right)?currentNode->right->height:0)==(
					(currentNode->left)?currentNode->left->height:0)))break;					
				}
				break;
			}
		}else{//case of equality
			fprintf(stderr, "Warning : We don't insert" 
			" elements with same id\n");
			break;
		}
	}
	return bt;
}

Btree *rebalance(Btree *bt){
	if(bt != NULL){
		
		int hL=(bt->left)?bt->left->height:0;
		int hR=(bt->right)?bt->right->height:0;
		//printf("Rebalance %d %d\n",bt->id, hR-hL);
		if(hR-hL==2){
			if(bt->right){
				int hRR = (bt->right->right)?bt->right->right->height:0;
				int hLR = (bt->right->left)?bt->right->left->height:0;
				if(hRR-hLR < 0){
					//printf("R %p %d %d %d\n",bt->right, bt->right->id, bt->right->height, hRR-hLR);
					bt->right = rightRotation(bt->right);
					//printf("r %p %d %d %d\n",bt->right, bt->right->id, bt->right->height, ((bt->right->right)?bt->right->right->height:0)-((bt->right->left)?bt->right->left->height:0));					
				}
				//printf("L %p %d %d %d\n",bt, bt->id, bt->height, hR-hL);
				bt = leftRotation(bt);
				//printf("l %p %d %d %d\n",bt, bt->id, bt->height,((bt->right)?bt->right->height:0)-((bt->left)?bt->left->height:0));
				return bt;
			}else{
				fprintf(stderr,"Warning : Btree avl incoherent\n");
				return NULL;
			}
		}else if(hR-hL==-2){
			if(bt->left){
				int hRL = (bt->left->right)?bt->left->right->height:0;
				int hLL = (bt->left->left)?bt->left->left->height:0;
				if(hRL-hLL>0){
				//	printf("L %p %d %d %d\n",bt->left, bt->left->id, bt->left->height, hRL-hLL);			
					bt->left = leftRotation(bt->left);
				//	printf("l %p %d %d %d\n",bt->left, bt->left->id, bt->left->height, ((bt->left->right)?bt->left->right->height:0)-((bt->left->left)?bt->left->left->height:0));

				}
				//printf("R %p %d %d %d\n",bt, bt->id, bt->height, hR-hL);
				bt = rightRotation(bt);
				//printf("r %p %d %d %d\n",bt, bt->id, bt->height, ((bt->right)?bt->right->height:0)-((bt->left)?bt->left->height:0));
				return bt;
			}else{
				fprintf(stderr,"Warning : Btree avl incoherent\n");
				return NULL;
			}
		}else if(hR-hL==0)return bt;
		else return bt;
	}
	fprintf(stderr, "Warning : a Btree avl incoherent %p\n",bt);
	return NULL;
	
}

Btree *leftRotation(Btree *v){
	if(!v->right){
		fprintf(stderr, "Warning : cant do left rotation to a" 
		"node without right sub-tree\n");
		return NULL;
	}
	Btree *w = v->right;
	w->father = v->father;
	if(v->father){
		if(v->father->left == v)v->father->left = w;
		else if(v->father->right == v)v->father->right = w;
	}
	v->father = w;
	v->right = w->left;
	if(v->right)v->right->father = v;
	w->left = v;
	updateHeight(v);
	updateHeight(w);
	return w;
}

Btree *rightRotation(Btree *w){
	if(!w->left){
		fprintf(stderr, "Warning : cant do left rotation to a" 
		"node without right sub-tree\n");
		return NULL;
	}
	Btree *v = w->left;
	v->father = w->father;
	if(w->father){
		if(w->father->left==w)w->father->left=v;
		else if(w->father->right==w)w->father->right=v;
	}
	w->father = v;
	w->left = v->right;
	if(w->left)w->left->father = w;
	v->right = w;
	updateHeight(w);
	updateHeight(v);
	return v;
}

void updateHeight(Btree *bt){
	if(bt){
		//printf("up H %d  %d %d  %d  %d\n",bt->id,(bt->left)?bt->left->height:0,(bt->right)?bt->right->height:0, 1 + max(((bt->left)?bt->left->height:0),((bt->right)?bt->right->height:0)),max(((bt->left)?bt->left->height:0),((bt->right)?bt->right->height:0)));
		bt->height = 1 + 
		max(((bt->left)?bt->left->height:0),
		((bt->right)?bt->right->height:0));
	}else fprintf(stderr, "Warning : You try to update the height of a NULL"
	" btree\n");
}

Btree *generateRandomBAVLTree(int numberOfElements){
	Btree *result = NULL;
	//char *name = calloc(10,sizeof(char));

	while(numberOfElements-->0){		
		result = insertAvl(result, rand()%1000, NULL, NULL);
	}
	return result;
}

Btree *readBAVLTreeFromFile(char *filename){
	FILE *f = fopen(filename, "r");
	char *line = calloc(255, sizeof(char));
	fgets(line, 255, f);
	int nbElements = atoi(line);
	int id;
	char *label=calloc(50, sizeof(char));
	Btree *result=NULL;
	//char *name=calloc(5,sizeof(char));
	//int i=1;
	while(nbElements>0 && !feof(f)){
		fgets(line, 255, f);
		sscanf(line, " %d %s", &id, label);
		result = insertAvl(result, id, (label && strcmp(label,"NULL"))?label:NULL, NULL);
		/*sprintf(name, "%d", i++);
		drawBtree(result, name);
		*/nbElements--;
	}
	return result;
}