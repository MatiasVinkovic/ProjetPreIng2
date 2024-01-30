#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>




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

//FILES

typedef struct _node{
    Tree *arbre;
    struct _node* pNext;
}Node;

Node *createNode(Tree *a){
    Node *pNew = malloc(sizeof(Node));
    if(pNew==NULL){exit(8);}
    pNew->pNext = NULL;
    pNew->arbre = a;
    return pNew;
}

typedef struct{
    Node *pHead;
    Node *pTail;
    int size;
}Fifo;

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


// a = nouveau
//b = ancien
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
    else{ //already in
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


Tree* firstAVL(Tree * avl){

    //on ouvre le fichier contenant routeID;distance
    FILE * list_file = fopen("../file/option_s_data.txt","r");
    if(list_file==NULL){
        exit(2);//error
    }

    //Temporary variabless
    int tempRouteID;
    float tempDistance;

    //ok

    //on rentre la premiere ligne dans l'avl
    avl = createAVL(404,404);
    int balance = avl->balance;


    while(fscanf(list_file, "%d %f", &tempRouteID, &tempDistance) == 2){
        avl = insertAVL(avl, tempRouteID, &balance, tempDistance);
    }
    fclose(list_file);
    return avl;

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

void infix(Tree * a, FILE *file_final) {
    //infix display
    if (!isEmpty(a)) {
        infix(a -> left, file_final);
        //printf("route id = [%d] max/min = [%f/%f] max-min = [%f] balance = [%d] count = [%d]\n", a->routeID,a->max, a->min, a->max_miness_min, a->balance, a->count);
        fprintf(file_final,"%d;%.4f;%.4f;%.4f;%.4f\n",a->routeID, a->min, a->moy, a->max, a->max_miness_min);
        infix(a -> right, file_final);
    }
    //tail -50 final_file.txt | tac
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

int main(void) {

    Tree* a;
    a = firstAVL(a);
    //premiere ligne

    //premier avl que l'on met dans la file :
    Fifo f = {NULL, NULL};
    arbreToFile(a, &f); //l'ancienne arbre est dans la file

    //on se ramene a une file pointée
    Fifo *newFifo = createFifo();
    Tree *temp;
    while(f.pHead != NULL){
        defiler(&f,&temp);
        enfiler(newFifo, temp);
    }
    //afficheNewFile(newFifo);

    Tree*b;
    b = fileToAvl(newFifo);

    FILE * file = fopen("../file/option_s_final_file.txt", "a");
    if(file==NULL){exit(999);}


    //prefix(a);
    infix(b, file);
    //tail -n 50 option_s_final_file.txt  | tac


    freeMemory(a);
    freeMemory(b);

    return 0;
}
