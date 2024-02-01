#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


//constantes
#define NAME_SIZE 150
#define SIZE 42


#include "prototype_t.h"


//ALGORITHMS OF BINARY TREE AVL -> the avl inside the first avl

Avl_in * createAvlIn(int route_ID) { 
    Avl_in * n = malloc(sizeof(Avl_in));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    n->fg = NULL;
    n->fd = NULL;
    n->balance = 0;
    n->route_ID = route_ID;
    return n;
}


Avl_in* leftRotation2(Avl_in* a){
    if (a==NULL){
        exit(5);
    }
    int eq_a, eq_p;
    Avl_in* pivot;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    eq_a = a->balance;
    eq_p = pivot->balance;

    a->balance = eq_a - fmax(eq_p, 0) - 1;
    pivot->balance = fmin(fmin(eq_a-2, eq_a+eq_p-2), eq_p-1);

    a = pivot;
    return a;
}



Avl_in* rightRotation2(Avl_in* a) {
    if (a == NULL) {
        exit(84);
    }

    int eq_a, eq_p;
    Avl_in* pivot;
    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    eq_a = a->balance;
    eq_p = pivot->balance;

    a->balance = eq_a - fmin(eq_p, 0) + 1;
    double first_compare = fmax(eq_a + 2, eq_a + eq_p + 2);
    pivot->balance = fmax(first_compare, eq_p + 1);

    a = pivot;
    return a;
}



Avl_in* doubleRightRot2(Avl_in* a){
    if (a == NULL) {
        exit(81);
    }
    a->fg = leftRotation2(a->fg);
    //printf("rotation right done in doubleRight");
    return rightRotation2(a);
}


Avl_in* doubleLeftRot2(Avl_in* a){
    if (a == NULL) {
        exit(8);
    }
    a->fd = rightRotation2(a->fd);
    //printf("rotation left done in doubleRight");
    return leftRotation2(a);
}


Avl_in* balanceAVL2(Avl_in* a) {
    if (a==NULL) {
        exit(7); // Ou une gestion d'erreur appropriée
    }

    if (a->balance >= 2) {
        if (a->fd->balance >= 0) {
            //printf("rotation left : ");
            return leftRotation2(a);
        } else {
            return doubleLeftRot2(a);
            //printf("double rotation left : ");
        }
    } else if (a->balance <= -2) {
        if (a->fg->balance <= 0) {
            //printf("rotation right : ");
            return rightRotation2(a);
        } else {
            //printf("double rotation right : ");
            return doubleRightRot2(a);
        }
    }
    return a;
}

Avl_in *insertAvlIn(Avl_in *a,int *h, int route_ID, int *v){
    //printf("in\n");
    
    if(a==NULL){
        *h = 1;
        return createAvlIn(route_ID);
    }
    else if(route_ID < a->route_ID){

        a->fg = insertAvlIn(a->fg, h, route_ID, v);
        *h = -*h;
    }
    else if(route_ID > a->route_ID){
        a->fd = insertAvlIn(a->fd, h, route_ID, v);
    }
    else{ //already in
        *h = 0;
        *v = -1;
        return a;
    }
    if(*h != 0){
        a->balance = a->balance + *h;
        a = balanceAVL2(a);
        if(a->balance == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

void freeMemoryAvlin(Avl_in* t){
  if(t!=NULL){
    freeMemoryTreeAvlin(t->fg);
    freeMemoryTreeAvlin(t->fd);
    free(t);
    }
}
