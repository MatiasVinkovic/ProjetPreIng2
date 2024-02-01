#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "prototype_t.h"

#define NAME_SIZE 150
#define SIZE 42

//FIFO CODE : SAME AS -S OPTION -> TO TRANSFERT FIRST AVL INTO A SECOND SORTED DIFFERENTLY

SecondNode *createSecondNode(Tree *a){
    SecondNode *pNew = malloc(sizeof(SecondNode));
    if(pNew==NULL){exit(8);}
    pNew->pNext = NULL;
    pNew->arbre = a;
    return pNew;
}

Fifo *createFifo(){
    Fifo *pFifo = malloc(sizeof(Fifo));
    if(pFifo==NULL){exit(5);}
    pFifo->pHead = NULL;
    pFifo->pTail = NULL;
    pFifo->size = 0;
    return pFifo;
}

void enfiler(Fifo *f, Tree *a){
    if(isEmpty(a)){exit(5);}
    SecondNode*n = createSecondNode(a);if(n==NULL){exit(88);}
    if(f->pHead==NULL){
        //if fifo empty
        f->pHead=n;
        f->pTail=n;
        f->size+=1;
    }
    else{
        f->pTail->pNext = n;
        f->pTail = f->pTail->pNext;
        f->size+=1;
    }
}

void defiler(Fifo *f, Tree **b){
    if(f==NULL){exit(9);}
    SecondNode *n = f->pHead;
    if(n==NULL){exit(55);}
    *b = n->arbre;
    f->pHead = f->pHead->pNext;

    //if fifo empty after the delete phase
    if(f->pHead==NULL){
        f->pTail=NULL;
    }
    free(n);

}

//Tree into a fifo
void arbreToFile(Tree *a, Fifo *f){
    if(!isEmpty(a)){
        enfiler(f, a);
        arbreToFile(a->right, f);
        arbreToFile(a->left, f);
    }
}

void afficheNewFile(Fifo *f){
    while(f->pHead != NULL){
        printf("City name = [%s] Size of the list : [%d] Departure City = [%d]\n", f->pHead->arbre->city_name, f->pHead->arbre->size, f->pHead->arbre->departCityCount);
        f->pHead = f->pHead->pNext;
    }
}