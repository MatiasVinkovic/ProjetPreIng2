#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NAME_SIZE 150
#define SIZE 42

//2 trees
typedef struct _avl_in{
    struct _avl_in *fd;
    struct _avl_in *fg;
    int route_ID;
    int balance;
}Avl_in;

typedef struct _tree{
    struct _tree *left;
    struct _tree *right;
    int balance;
    char city_name[NAME_SIZE];
    int routeID;
    int size;
    int departCityCount;
    Avl_in *avl_in;
}Tree;

//t_first_avl.c
Tree * createTree(char city_name_param[], int route_ID, int step_ID);
Tree* leftRotation(Tree* a);
Tree* rightRotation(Tree* a);
Tree* doubleRightRot(Tree* a);
Tree* doubleLeftRot(Tree* a);
Tree* balanceAVL(Tree* a);
Tree *insertAvl(Tree *a,int *h, int route_ID,int step_ID, char city_name[]);
Tree* firstAVL(Tree * avl);
void prefix(Tree * a);
void infix(Tree * a, FILE *file_final);
int isEmpty(Tree * a);
void freeMemoryAvlin(Avl_in* t);

void freeMemoryTree(Tree* t);
//t_avl_in.c
Avl_in * createAvlIn(int route_ID);
Avl_in* leftRotation2(Avl_in* a);
Avl_in* rightRotation2(Avl_in* a);
Avl_in* doubleRightRot2(Avl_in* a);
Avl_in* doubleLeftRot2(Avl_in* a);
Avl_in* balanceAVL2(Avl_in* a);
Avl_in *insertAvlIn(Avl_in *a,int *h, int route_ID, int *v);

//t_fifo.c
typedef struct _secondnode{
    Tree *arbre;
    struct _secondnode* pNext;
}SecondNode;

typedef struct{
    SecondNode *pHead;
    SecondNode *pTail;
    int size;
}Fifo;

SecondNode *createSecondNode(Tree *a);
Fifo *createFifo();
void enfiler(Fifo *f, Tree *a);
void defiler(Fifo *f, Tree **b);
void arbreToFile(Tree *a, Fifo *f);
Tree *fileToAvl(Fifo *f);
void afficheNewFile(Fifo *f);

//t_abr.c
typedef struct _abr {
  char city[NAME_SIZE];
  int totalRoutes;
  int totalFirst;
  struct _abr * l;
  struct _abr * r;
}Abr;
Abr * createAbr(char city[], int totalRoutes, int totalFirst);
Abr * recursiveInsertABR(Abr * a, char city_name[], int totalFirst, int totalRoutes);
Abr * constructionFinalAbr(Abr * a);
void infixAbr(Abr * a, FILE *file);
void freeMemoryAbr(Abr* t);


#endif
