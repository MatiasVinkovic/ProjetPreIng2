#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "prototype_s.h"

#define NAME_SIZE 150
#define SIZE 42

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

    FILE * file = fopen("../../file/option_s_final_file.txt", "a");
    if(file==NULL){exit(999);}


    //prefix(a);
    infix_(b, file);
    //tail -n 50 option_s_final_file.txt  | tac


    freeMemory(a);
    freeMemory(b);

    return 0;
}
