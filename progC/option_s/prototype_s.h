#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NAME_SIZE 150
#define SIZE 42


//STRUCTURES
typedef struct _tree{
    struct _tree *left;
    struct _tree *right;

    int balance;
    int routeID;
    float max;
    float min;
    float sum; //somme des distances
    int count; //nombre de trajet
    float moy;

    float max_miness_min;
}Tree;

typedef struct _node{
    Tree *arbre;
    struct _node* pNext;
}Node;

typedef struct{
    Node *pHead;
    Node *pTail;
    int size;
}Fifo;

//s_first_avl.c
void infix_(Tree * a, FILE *file_final);
Tree * createAVL(int newId, float distance); //use only if never seen routeID in avl
Tree * createAVLSecond(int newId, float max, float min, int count, float sum, float moy, float miness_min); //use only if never seen routeID in avl
Tree* leftRotation(Tree* a);
Tree* rightRotation(Tree* a);
Tree* doubleRightRot(Tree* a);
Tree* doubleLeftRot(Tree* a);
Tree* balanceAVL(Tree* a);
Tree *insertAVL(Tree *a, int routeID, int *h, float distance);
int isEmpty(Tree * a);
void traiter(Tree * a);
Tree* firstAVL(Tree * avl);
Tree *fileToAvl(Fifo *f);
void freeMemory(Tree* t);

//s_fifo.c
Node *createNode(Tree *a);
Fifo *createFifo();
void enfiler(Fifo *f, Tree *a);
void defiler(Fifo *f, Tree **b);
void arbreToFile(Tree *a, Fifo *f);
void afficheFile(Fifo f);
void afficheNewFile(Fifo *f);
int compter(Tree * a, int *i);



#endif