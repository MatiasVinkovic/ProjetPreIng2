#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define NAME_SIZE 150
#define SIZE 42


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


int isEmpty(Tree * a) {
    //verify if the abr is empty
    return a == NULL;
}

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

Tree * createTree(char city_name_param[], int route_ID, int step_ID) { 
    Tree * n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(3); //problem with allocation
    }
    n->left = NULL;
    n->right = NULL;
    n->balance = 0;
    n->size = 1;
    strcpy(n->city_name, city_name_param);
    
    if(step_ID==1){n->departCityCount = 1;}
    else{n->departCityCount = 0;}

    n->routeID = route_ID;
    n->avl_in = createAvlIn(route_ID);

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

Tree* doubleRightRot(Tree* a){
    if (a == NULL) {
        exit(81);
    }
    a->left = leftRotation(a->left);
    //printf("rotation right done in doubleRight");
    return rightRotation(a);
}

Avl_in* doubleRightRot2(Avl_in* a){
    if (a == NULL) {
        exit(81);
    }
    a->fg = leftRotation2(a->fg);
    //printf("rotation right done in doubleRight");
    return rightRotation2(a);
}

Tree* doubleLeftRot(Tree* a){
    if (a == NULL) {
        exit(8);
    }
    a->right = rightRotation(a->right);
    //printf("rotation left done in doubleRight");
    return leftRotation(a);
}

Avl_in* doubleLeftRot2(Avl_in* a){
    if (a == NULL) {
        exit(8);
    }
    a->fd = rightRotation2(a->fd);
    //printf("rotation left done in doubleRight");
    return leftRotation2(a);
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



Tree *insertAvl(Tree *a,int *h, int route_ID,int step_ID, char city_name[]){
    //printf("in\n");
    if(isEmpty(a)){
        *h = 1;
        return createTree(city_name, route_ID, step_ID);
    }
    else if(strcmp(city_name, a->city_name) < 0){

        a->left = insertAvl(a->left, h, route_ID, step_ID, city_name);
        *h = -*h;
    }
    else if(strcmp(city_name, a->city_name) > 0){
        a->right = insertAvl(a->right, h, route_ID, step_ID, city_name);
    }
    else{ //already in
        *h = 0;
        int x = a->avl_in->balance;
        int v = 0;
        a->avl_in = insertAvlIn(a->avl_in,&x, route_ID, &v);
        if(v != -1){
            a->size++;
        }
        if(step_ID==1){
            a->departCityCount = (a->departCityCount) + 1;
        }
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


Tree* firstAVL(Tree * avl, int size){

    //on ouvre le fichier contenant routeID;distance

    //cat t_test.txt | sed 's/ /-/g' | sed 's/;/ /g' >oui.txt
    FILE * list_file = fopen("../file/data.txt","r");
    if(list_file==NULL){
        exit(2);//error
    }
    int i = 0;
    //Temporary variabless
    char city_a[NAME_SIZE];
    char city_b[NAME_SIZE];
    int tempStepID;
    int tempRouteID;

    // //on rentre la premiere ligne dans l'avl
    avl = createTree("none", 0, 0);
    int balance = avl->balance;


    for(int i = 0; i<size;i++){
        fscanf(list_file, "%d %d %s %s", &tempRouteID, &tempStepID, city_a, city_b);
       

        //printf("%s\n", city_a);
        avl = insertAvl(avl, &balance, tempRouteID, tempStepID, city_a);
        avl = insertAvl(avl, &balance, tempRouteID, 0, city_b);
        
    }
    fclose(list_file);
    return avl;

}

void prefix(Tree * a) {
    //prefix display
    if (!isEmpty(a)) {
        printf("City name = [%s] Size of the list : [%d] Departure City = [%d]\n", a->city_name, a->size, a->departCityCount);
        prefix(a -> left);
        prefix(a -> right);
    }
}

void infix(Tree * a) {
    //infix display
    if (!isEmpty(a)) {
        infix(a -> left);
        printf("City name = [%s] Size of the list : [%d] Departure City = [%d]\n", a->city_name, a->size, a->departCityCount);
        //fprintf(file_final,"%d;%.4f;%.4f;%.4f;%.4f\n",a->routeID, a->min, a->moy, a->max, a->max_miness_min);
        infix(a -> right);
    }
    //tail -50 final_file.txt | tac
}

void postfix(Tree * a) {
    //postfix display
    if (!isEmpty(a)) {
        postfix(a -> left);
        postfix(a -> right);
        printf("City name = [%s] Size of the list : [%d] Departure City = [%d]\n", a->city_name, a->size, a->departCityCount);
    }
}


int main(void){

    Tree *a;//6365541
    a = firstAVL(a, 6365541);
    prefix(a);
    
    
    
   




    return 0;
}
