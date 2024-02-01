#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "prototype_s.h"


//ALGORITHMS OF BINARY TREE AVL

Tree * createAVL(int newId, float distance) { //use only if never seen routeID in avl
    Tree * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    //no value for the moment
    n->routeID = newId;
    n->max = distance;
    n->min = distance;
    n->max_miness_min = 0;
    n->count = 1;
    n->sum = distance;
    n->moy = (n->sum)/n->count;
    //basics parameters
    n -> left = NULL;
    n -> right = NULL;
    n->balance = 0; //cause no child
    return n;
}


Tree * createAVLSecond(int newId, float max, float min, int count, float sum, float moy, float miness_min) { //use only if never seen routeID in avl
    Tree * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    //no value for the moment
    n->routeID = newId;
    n->max = max;
    n->min = min;
    n->max_miness_min = miness_min;
    n->count = count;
    n->sum = sum;
    n->moy = moy;
    //basics parameters
    n -> left = NULL;
    n -> right = NULL;
    n->balance = 0; //cause no child
    return n;
}

Tree* leftRotation(Tree* a){
    if (a==NULL){
        exit(5);
    }
    int eq_a, eq_p;
    Tree* pivot;
    pivot = a->right;
    a->right = pivot->left;
    pivot->left = a;
    eq_a = a->balance;
    eq_p = pivot->balance;

    a->balance = eq_a - fmax(eq_p, 0) - 1;
    pivot->balance = fmin(fmin(eq_a-2, eq_a+eq_p-2), eq_p-1);

    a = pivot;
    return a;
}

Tree* rightRotation(Tree* a) {
    if (a == NULL) {
        exit(84);
    }

    int eq_a, eq_p;
    Tree* pivot;
    pivot = a->left;
    a->left = pivot->right;
    pivot->right = a;
    eq_a = a->balance;
    eq_p = pivot->balance;

    a->balance = eq_a - fmin(eq_p, 0) + 1;
    double first_compare = fmax(eq_a + 2, eq_a + eq_p + 2);
    pivot->balance = fmax(first_compare, eq_p + 1);

    a = pivot;
    return a;
}

Tree* doubleRightRot(Tree* a){
    if (a == NULL) {
        exit(81);
    }
    a->left = leftRotation(a->left);
    //printf("rotation right done in doubleRight");
    return rightRotation(a);
}

Tree* doubleLeftRot(Tree* a){
    if (a == NULL) {
        exit(8);
    }
    a->right = rightRotation(a->right);
    //printf("rotation left done in doubleRight");
    return leftRotation(a);
}

Tree* balanceAVL(Tree* a) {
    if (isEmpty(a)) {
        exit(7); // Ou une gestion d'erreur appropriée
    }

    if (a->balance >= 2) {
        if (a->right->balance >= 0) {
            //printf("rotation left : ");
            return leftRotation(a);
        } else {
            return doubleLeftRot(a);
            //printf("double rotation left : ");
        }
    } else if (a->balance <= -2) {
        if (a->left->balance <= 0) {
            //printf("rotation right : ");
            return rightRotation(a);
        } else {
            //printf("double rotation right : ");
            return doubleRightRot(a);
        }
    }
    return a;
}

//inserting in the first avl
Tree *insertAVL(Tree *a, int routeID, int *h, float distance){//e is routeID
    if(isEmpty(a)){
        *h = 1;
        return createAVL(routeID, distance);
    }
    else if(routeID < a->routeID){
        a->left = insertAVL(a->left, routeID, h, distance);
        *h = -*h;
    }
    else if(routeID > a->routeID){
        a->right = insertAVL(a->right, routeID, h, distance);
    }
    else{ //already in : updating the values into the avl
        *h = 0;
        //update the max/min distance
        a->max = fmax(a->max, distance);
        a->min = fmin(a->min, distance);

        //update max-min
        if( (a->max) ==  (a->min) ){
            a->max_miness_min = 0;
        }
        else{
            a->max_miness_min = a->max - a->min;
        }
        a->sum += distance;
        a->count = a->count + 1;
        a->moy = (a->sum)/a->count; //deduct the average distance value
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
    return a;
}

int isEmpty(Tree * a) {
    //verify if the abr is empty
    return a == NULL;
}

void traiter(Tree * a) {
    //display node
    if (!isEmpty(a)) {
        printf("[%d] ", a -> routeID);
    }
}


//inserting values in the second avl, sorted by max-min value

// a = new tree
//b = old tree
Tree *insertSecondAVL(Tree *a, Tree *b, int *h){
    //printf("in\n");
    if(isEmpty(a)){
        *h = 1;

        return createAVLSecond(b->routeID, b->max, b->min, b->count, b->sum, b->moy, b->max_miness_min);
    }
    else if(b->max_miness_min < a->max_miness_min){

        a->left = insertSecondAVL(a->left,b,h);
        *h = -*h;
    }
    else if(b->max_miness_min > a->max_miness_min){

        a->right = insertSecondAVL(a->right,b, h);
    }
    else{ //already in : doing nothing
        *h = 0;

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
    return a;
}


//creating the first avl, with the data.csv values
Tree* firstAVL(Tree * avl){
    //opening the file with routeID;distance
    FILE * list_file = fopen("../../file/option_s_data.txt","r");
    if(list_file==NULL){
        exit(2);//error
    }

    //Temporary variabless
    int tempRouteID;
    float tempDistance;

    //ok

    //first line into the avl, we could also put a first fscanf
    avl = createAVL(0,0);
    int balance = avl->balance;


    while(fscanf(list_file, "%d %f", &tempRouteID, &tempDistance) == 2){
        avl = insertAVL(avl, tempRouteID, &balance, tempDistance);
    }
    fclose(list_file);
    return avl;
}

//dynamic fifo into an avl
Tree *fileToAvl(Fifo *f){
    Tree *tempTree;
    int h;
    Tree *new = createAVLSecond(0,0,0,0,0,0,0);

    while(f->pHead != NULL){
        defiler(f, &tempTree);
        //printf("defilement de %d\n", tempTree->routeID);
        h = new->balance;
        //printf("balance=%d\n", tempTree->balance);
        new = insertSecondAVL(new, tempTree, &h);
        //f.pHead = f.pHead->pNext;
    }

    return new;
}

int compter(Tree * a, int *i) {
    //prefix display
    if (!isEmpty(a)) {
        printf("%d\n", *i);
        *i = *i+1;
        compter(a -> left, i);
        compter(a -> right, i);
    }
}

void freeMemory(Tree* t){
  if(t!=NULL){
    freeMemory(t->left);
    freeMemory(t->right);
    free(t);
    }
}

