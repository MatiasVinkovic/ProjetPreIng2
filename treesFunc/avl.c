#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _tree {
  int v;
  struct _tree * left;
  struct _tree * right;
  int balance;
}Tree;


int isEmpty(Tree * a) {
  //verify if the abr is empty
  return a == NULL;
}

int existLeftChild(Tree * a) {
  //verify if has left child
  return !isEmpty(a) && a -> left != NULL;
}

int existRightChild(Tree * a) {
  //verify if has right child
  return !isEmpty(a) && a -> right != NULL;
}

void traiter(Tree * a) {
  //display node
  if (!isEmpty(a)) {
    printf("[%d] ", a -> v);
  }
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


Tree * createAVL(int e) {
  Tree * newTree = malloc(sizeof(Tree));
  if (newTree == NULL) {
    exit(3); //problem with allocation
  }
  newTree -> v = e;
  newTree -> left = NULL;
  newTree -> right = NULL;
  newTree->balance = 0; //cause no child
  return newTree;
}

int recherche(Tree * a, int e) {
  //return 1 if value is in abr (non recursive way)
  //S      
  if (isEmpty(a)) {
    exit(1);
  }
  int i = 0;
  Tree * a2 = a;
  while (a2 -> v != e && a2 != NULL) {
    if (e < a2 -> v) {
      a2 = a2 -> left;
    } else {
      a2 = a2 -> right;
    }
    i++;
  }
  printf("{%d}\n\n", i + 1);
  if (a2 != NULL) {
    return 1;
  }
  return 0;
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
		if(a->balance == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}	
	}
	return a;
}











/*
Tree * recursiveInsertABR(Tree * a, int e) {
  //insert in an abr (recursive way)
  if (isEmpty(a)) {
    return createTree(e);
  }
  if (e > a -> v) {
    a -> right = recursiveInsertABR(a -> right, e);
  }
  if (e < a -> v) {
    a -> left = recursiveInsertABR(a -> left, e);
  }
  return a;
}


Tree * suppressElementAbr(Tree * a, int e);

Tree * suppressMax(Tree * a, int * pe) {
  Tree * tmp;
  if (existRightChild(a)) {
    a -> right = suppressMax(a -> right, pe);
  } else {
    * pe = a -> v;
    tmp = a;
    a = a -> left;
    free(tmp);
  }
  return a;
}

Tree * suppressElementAbr(Tree * a, int e) {
  //suppress an element in a abr
  Tree * tmp;
  if (isEmpty(a)) {
    return a;
  }
  if (e > a -> v) {
    a -> right = suppressElementAbr(a -> right, e);
  } else if (e < a -> v) {
    a -> left = suppressElementAbr(a -> left, e);
  } else {
    if (!existLeftChild(a)) {
      tmp = a;
      a = a -> right;
      free(tmp);
    } else if (!existRightChild(a)) {
      tmp = a;
      a = a -> left;
      free(tmp);
    } else {
      a -> left = suppressMax(a -> left, & e);
      a -> v = e;
    }
  }
  return a;
}

void prefixButStopsWhenElementIsFound(Tree * a, int e, int * found) {
  //prefix until the e value is found
  if (!isEmpty(a) && !( * found)) {
    traiter(a);
    if (a -> v == e) {
      * found = 1; // set found to true
    } else {
      prefixButStopsWhenElementIsFound(a -> left, e, found);
      prefixButStopsWhenElementIsFound(a -> right, e, found);
    }
  }
}

int checkABR_rec(Tree * b, int i) {
  //return 1 if tree is an abr   (recursive way)
  if (isEmpty(b)) {
    printf("You sent an empty tree so technically it could be an ABR\n\n");
    return 1;
  }
  if (b != NULL && i != 0) {

    // process
    // if current value is lesser than previous processed node

    // left
    if (existLeftChild(b) && b -> v > b -> left -> v) {
      i = checkABR_rec(b -> left, i); // if left returned 0, return 0
    }

    // =>error
    // right
    if (existRightChild(b) && b -> v < b -> right -> v) {
      i = checkABR_rec(b -> right, i); // if right returned 0, return 0
    }
    // all ok return 1
    else if (existLeftChild(b) && b -> v < b -> left -> v || existRightChild(b) && b -> v > b -> right -> v) {
      return 0;
    }
  }
  if (i == 0) {
    return 0;
  }
  return 1;
}

int verifyABR(Tree * b) {
  //check abr non recursive way
  if (isEmpty(b)) {
    printf("You sent an empty tree so technically it could an ABR\n\n");
    return 1;
  }
  Tree * c = b;
  //printf("cant enter the while\n");
  if (existLeftChild(c) || existRightChild(c)) {
    if (existLeftChild(c) && c -> v > c -> left -> v) {
      c = c -> left;
    } else if (existRightChild(c) && c -> v < c -> right -> v) {
      c = c -> right;
    }
  } else if (c -> v < c -> left -> v || c -> v > c -> right -> v) {
    printf("tf thats not an ABR \n\n");
    return 0;
  }
  return 1;
}

Tree * modifyTreeToABR(Tree * a) {
  if (isEmpty(a)) {
    return a;
  }
  Tree * abrTree;
}


*/

int main(void){
	printf("Hello World");
	Tree *arbre = createAVL(19);
	

	return 0;
}
