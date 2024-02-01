#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "prototype_t.h"

#define NAME_SIZE 150
#define SIZE 42

//ALGORYTHMS OF THE BASIC BINARY TREE OF RESEARCH

Abr * createAbr(char city[], int totalRoutes, int totalFirst) {
  Abr * newTree = malloc(sizeof(Abr));
  if (newTree == NULL) {
    exit(876); //problem with allocation
  }
  strcpy(newTree->city, city);
  newTree->totalRoutes = totalRoutes;
  newTree->totalFirst=totalFirst;
  newTree -> l = NULL;
  newTree -> r = NULL;
  return newTree;
}

Abr * recursiveInsertABR(Abr * a, char city_name[], int totalFirst, int totalRoutes) {
  //insert in an abr (recursive way)
  if (a==NULL) {
    return createAbr(city_name, totalFirst, totalRoutes);
  }
  if (strcmp(city_name, a->city) > 0) {
    a -> r = recursiveInsertABR(a -> r, city_name, totalFirst, totalRoutes);
  }
  if (strcmp(city_name, a->city) < 0) {
    a -> l = recursiveInsertABR(a -> l, city_name, totalFirst, totalRoutes);
  }
  return a;
}

Abr * constructionFinalAbr(Abr * a){
    //Opening the file
    FILE * list_file = fopen("../../file/option_t_final_file_10.txt","r");
    if(list_file==NULL){
        exit(2);//error
    }
    //Temporary variables
    char city[NAME_SIZE];
    int tmpTotalRoutes;
    int tmpTotalFirst;

    // first line into the avl
    fscanf(list_file, "%s %d %d", city, &tmpTotalRoutes, &tmpTotalFirst);
    a = recursiveInsertABR(a, city, tmpTotalRoutes, tmpTotalFirst   );
    
    int k = 0;
    while(fscanf(list_file, "%s %d %d", city, &tmpTotalRoutes, &tmpTotalFirst) == 3 && k!=10){
        a = recursiveInsertABR(a, city, tmpTotalRoutes, tmpTotalFirst);
        k++;
    }
    fclose(list_file);
    
    return a;
}

void infixAbr(Abr * a, FILE *file) {
    //infix display
    if (a!=NULL) {
        infixAbr(a->l, file);
        fprintf(file, "%s;%d;%d\n", a->city,a->totalRoutes,a->totalFirst);
        infixAbr(a->r,file);
    }
}