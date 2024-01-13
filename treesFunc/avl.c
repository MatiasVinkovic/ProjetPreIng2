#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct _tree{
    struct _tree *left; 
    struct _tree *right;
    int v;
    int balance;
    int routeID;
    float max;
    float min;
    float sum; //somme des distances
    int nbr; //nombre de trajet
    float moy;
}Tree;

int isEmpty(Tree * a) {
  //verify if the abr is empty
  return a == NULL;
}

void traiter(Tree * a) {
  //display node
  if (!isEmpty(a)) {
    printf("[%d] ", a -> v);
  }
}

Tree * createAVL(int e) {
  Tree * newTree = malloc(sizeof(Tree));
  if (newTree == NULL) {
    exit(3); //problem with allocation
  }
  //no value for the moment
  newTree->v = e;
  newTree -> left = NULL;
  newTree -> right = NULL;
  newTree->balance = 0; //cause no child
  return newTree;
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
            printf("rotation left : ");
            return leftRotation(a);
        } else {
            return doubleLeftRot(a);
            printf("double rotation left : ");
        }
    } else if (a->balance <= -2) {
        if (a->left->balance <= 0) {
            printf("rotation right : ");
            return rightRotation(a);
        } else {
            printf("double rotation right : ");
            return doubleRightRot(a);
        }
    }
    return a;
} 

Tree *insertAVL(Tree *a, int e, int *h){
	if(isEmpty(a)){
		*h = 1;
		return createAVL(e);
	}
	else if(e < a->v){
		a->left = insertAVL(a->left, e, h);
		*h = -*h;
	}
	else if(e > a->v){
		a->right = insertAVL(a->right, e, h);
	}
	else{
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

// -------PARCOURS DE L'ARBRE-----------

void prefix(Tree * a) {
  //prefix display
  if (!isEmpty(a)) {
    traiter(a);
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

void infix(Tree * a) {
  //infix display
  if (!isEmpty(a)) {
    infix(a -> left);
    traiter(a);
    infix(a -> right);
  }
}



int main() {
    Tree *root = createAVL(13);  // Initialize an empty AVL tree
    int height = root->balance;     // Height variable to track changes during insertions

    // Insert elements into the AVL tree and print after each insertion
    root = insertAVL(root, 10, &height);
    printf("After inserting 10:\n");
    prefix(root);
    printf("\n");

    root = insertAVL(root, 5, &height);
    printf("After inserting 5:\n");
    prefix(root);
    printf("\n");   

    root = insertAVL(root, 15, &height);
    printf("After inserting 15:\n");
    prefix(root);
    printf("\n");

    root = insertAVL(root, 145, &height);
    printf("After inserting 145:\n");
    prefix(root);
    printf("\n");

    root = insertAVL(root, 34, &height);
    printf("After inserting 34:\n");
    prefix(root);
    printf("\n");

    root = insertAVL(root, 80, &height);
    printf("After inserting 80:\n");
    prefix(root);
    printf("\n");

    


    // Continue with more insertions and balancing as needed

    return 0;
}
