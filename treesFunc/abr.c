#include <stdio.h>

#include <stdlib.h>

#include <time.h>

typedef struct tttree {
  int v;
  struct tttree * left;
  struct tttree * right;
}
Tree;

typedef Tree * pTree;

int isEmpty(pTree a) {
  return a == NULL;
}

int existLeftChild(pTree a) {
  return !isEmpty(a) && a -> left != NULL;
}

int existRightChild(pTree a) {
  return !isEmpty(a) && a -> right != NULL;
}

void traiter(Tree * a) {
  if (!isEmpty(a)) {
    printf("[%d] ", a -> v);
  }
}

void prefix(Tree * a) {
  if (!isEmpty(a)) {
    traiter(a);
    prefix(a -> left);
    prefix(a -> right);
  }
}

void postfix(Tree * a) {
  if (!isEmpty(a)) {
    postfix(a -> left);
    postfix(a -> right);
    traiter(a);
  }
}

void infix(Tree * a) {
  if (!isEmpty(a)) {
    infix(a -> left);
    traiter(a);
    infix(a -> right);
  }
}

pTree createTree(int e) {
  pTree newTree = malloc(sizeof(Tree));
  if (newTree == NULL) {
    exit(3); //problem with allocation
  }
  newTree -> v = e;
  newTree -> left = NULL;
  newTree -> right = NULL;
  return newTree;
}

int recherche(pTree a, int e) {
  if (isEmpty(a)) {
    exit(1);
  }
  int i = 0;
  pTree a2 = a;
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

pTree recursiveInsertABR(pTree a, int e) {
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

pTree nonrecursiveInsertABR(pTree a, int e) {
  if (isEmpty(a)) {
    return createTree(e);
  }
  pTree b = a;
  while (b -> left != NULL && b -> right != NULL) {
    if (e > b -> v) {
      b = b -> right;
    }
    if (e < b -> v) {
      b = b -> left;
    }
  }
  b = createTree(e);
  return b;
}

pTree suppressElement(pTree a, int e);

pTree suppressMax(pTree a, int * pe) {
  pTree tmp;
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

pTree suppressElement(pTree a, int e) {
  pTree tmp;
  if (isEmpty(a)) {
    return a;
  }
  if (e > a -> v) {
    a -> right = suppressElement(a -> right, e);
  } else if (e < a -> v) {
    a -> left = suppressElement(a -> left, e);
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

void prefixButStopsWhenElementIsFound(pTree a, int e, int * found) {
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

int checkABR_rec(pTree b, int i) {
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

int verifyABR(pTree b) {
  if (isEmpty(b)) {
    printf("You sent an empty tree so technically it could an ABR\n\n");
    return 1;
  }
  pTree c = b;
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

pTree modifyTreeToABR(pTree a) {
  if (isEmpty(a)) {
    return a;
  }
  pTree abrTree;

}

int main(void) {
  pTree abr = createTree(10);

  //add nodes
  abr = recursiveInsertABR(abr, 3);
  abr = recursiveInsertABR(abr, 5);
  abr = recursiveInsertABR(abr, 15);
  abr = recursiveInsertABR(abr, 20);
  abr = recursiveInsertABR(abr, 12);
  abr = recursiveInsertABR(abr, 7);
  abr = recursiveInsertABR(abr, 45);
  abr = recursiveInsertABR(abr, 9);

  // infix traversal
  infix(abr);
  printf("\n\n");

  //postfix
  postfix(abr);
  printf("\n\n");

  //prefix
  prefix(abr);
  printf("\n\n");

  int h, j;
  h = 20;
  j = 3;
  int a = recherche(abr, h);
  int b = recherche(abr, j);

  if (a == 0) {
    printf("[%d] n'est pas le dedans\n\n", h);
  }
  if (b == 0) {
    printf("[%d] n'est pas le dedans\n\n", j);
  }

  if (a == 1) {
    printf("[%d] est dedans\n\n", h);
  }
  if (b == 1) {
    printf("[%d] est dedans\n\n", j);
  }

  //pTree golassooooooo = abr;

  int prefixVerification = 0;
  prefixButStopsWhenElementIsFound(abr, 10, & prefixVerification);
  prefixVerification = 0;
  printf("\n\n");
  prefixButStopsWhenElementIsFound(abr, 7, & prefixVerification);
  prefixVerification = 0;
  printf("\n\n");
  prefixButStopsWhenElementIsFound(abr, 22, & prefixVerification);
  printf("\n\n");
  abr = suppressElement(abr, 15);

  prefix(abr);
  printf("\n\n");

  int t = checkABR_rec(abr, 1);
  if (t == 0) {
    printf("not a ABR\n\n");
  } else if (t == 1) {
    printf("not not a ABR\n\n");
  }

  return 0;
}
