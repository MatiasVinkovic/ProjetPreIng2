#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "prototype_s.h"


//FIFO

void infix_(Tree * a, FILE *file_final) {
    //infix display
    if (!isEmpty(a)) {
        infix_(a -> left, file_final);
        //printf("route id = [%d] max/min = [%f/%f] max-min = [%f] balance = [%d] count = [%d]\n", a->routeID,a->max, a->min, a->max_miness_min, a->balance, a->count);
        fprintf(file_final,"%d;%.4f;%.4f;%.4f;%.4f\n",a->routeID, a->min, a->moy, a->max, a->max_miness_min);
        infix_(a -> right, file_final);
    }
    //tail -50 final_file.txt | tac
}

Node *createNode(Tree *a){
    Node *pNew = malloc(sizeof(Node));
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
    Node*n = createNode(a);if(n==NULL){exit(88);}
    if(f->pHead==NULL){
        //si la file est vide
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
    Node *n = f->pHead;
    if(n==NULL){exit(55);}
    *b = n->arbre;
    f->pHead = f->pHead->pNext;

    //si la file est vide apres la suppression du noeud
    if(f->pHead==NULL){
        f->pTail=NULL;
    }
    free(n);

}

void arbreToFile(Tree *a, Fifo *f){
    if(!isEmpty(a)){
        enfiler(f, a);
        arbreToFile(a->right, f);
        arbreToFile(a->left, f);
    }
}

void afficheFile(Fifo f){
    while(f.pHead != NULL){
        printf("[%d]\n", f.pHead->arbre->routeID);
        f.pHead = f.pHead->pNext;
    }
}

void afficheNewFile(Fifo *f){
    while(f->pHead != NULL){
        printf("[%d], max : [%f]\n", f->pHead->arbre->routeID, f->pHead->arbre->min);
        f->pHead = f->pHead->pNext;
    }
}


