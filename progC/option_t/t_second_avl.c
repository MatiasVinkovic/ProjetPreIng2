#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "prototype_t.h"

#define NAME_SIZE 150
#define SIZE 42

//ALGORITHMS OF BINARY TREE AVL -> in the avl which is into the avl


Tree * createAVLSecond(char city_name[],int departCityCount,int sizeOfTree) { //use only if never seen routeID in avl
    Tree * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    //no value for the moment
    strcpy(n->city_name, city_name);
    n->departCityCount = departCityCount;
    n->size = sizeOfTree;
    //basics parameters
    n -> left = NULL;
    n -> right = NULL;
    n->balance = 0; //cause no child
    return n;
}

// a = nouveau
//b = ancien
Tree *insertSecondAVL(Tree *a, Tree *b, int *h){
    //printf("in\n");
    if(a==NULL){
        *h = 1;
        return createAVLSecond(b->city_name,b->departCityCount,b->size);
    }
    else if(b->size < a->size){
        //printf("in");
        a->left = insertSecondAVL(a->left,b,h);
        *h = -*h;
    }
    else if(b->size > a->size){
        a->right = insertSecondAVL(a->right,b, h);
    }
    else{ //already in
        *h = 0;
        //printf("b SOL is %d and a SOL is %d\n", b->size, a->size);        
        return a;
    }
    if(*h != 0){
        a->balance = a->balance + *h;
        a = balanceAVL(a);
        if(a->balance == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;//ALGORITHMS OF BINARY TREE AVL

}

//fifo into the avl
Tree *fileToAvl(Fifo *f){
    Tree *tempTree;
    int h;

    defiler(f, &tempTree);
    Tree *new = createAVLSecond(tempTree->city_name,tempTree->departCityCount,tempTree->size);
    int i = 0;
    while(f->pHead != NULL){
        defiler(f, &tempTree);
        //printf("defilement de %s %d\n", tempTree->city_name, tempTree->sizeOfList);
        h = new->balance;
        //printf("balance=%d\n", tempTree->balance);
        new = insertSecondAVL(new, tempTree, &h);
    }

    return new;
}