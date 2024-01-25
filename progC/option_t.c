#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NAME_SIZE 100


typedef struct _avlIn{
    struct _avlIn *left;
    struct _avlIn *right;
    int balance;
    int route_ID;
}AvlIn;


typedef struct _tree{
    struct _tree *left;
    struct _tree *right;
    char* city_name;
    int balance;

    int departCityCount;
    Avl_in *avl_in;

}Tree;


int isEmpty(Tree * a) {
    //verify if the abr is empty
    return a == NULL;
}

AvlIn * createAvl_in(int route_ID) { 
    AvlIn * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    n->left = NULL;
    n->right = NULL;
    n->balance = 0;
    n->route_ID = route_ID;
    return n;
}



Tree * createTree(char * city_name, int route_ID) { 
    Tree * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    n->left = NULL;
    n->right = NULL;
    n->city_name = strcpy(n->city_name, "none");
    n->departCityCount = 0;
    n->balance = 0;
    n->avl_in = createAvl_in(route_ID);

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
//e is routeID
Tree *insertAVL(Tree *a, int routeID, int *h, float distance){
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
    else{ //already in
        *h = 0;
        
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


// -------PARCOURS DE L'ARBRE-----------

void prefix(Tree * a) {
    //prefix display
    if (!isEmpty(a)) {
        printf("route id = [%d] max/min = [%f/%f] max-min = [%f] balance = [%d] count = [%d]\n", a->routeID,a->max, a->min, a->max_miness_min, a->balance, a->count);
        prefix(a -> left);
        prefix(a -> right);
    }
}

void postfix(Tree * a) {
    //postfix display
    if (!isEmpty(a)) {
        postfix(a -> left);
        postfix(a -> right);
        traiter(a);
    }
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
