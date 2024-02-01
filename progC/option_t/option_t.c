#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define NAME_SIZE 150
#define SIZE 42

#include "prototype_t.h"





int main(void){

    Tree *a;
    a = firstAVL(a);    
    //prefix(a);
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

    FILE * file = fopen("../../file/option_t_final_file_not_10.txt", "a");
    if(file==NULL){exit(999);}

    infix(b, file);
    system("head -n10 ../../file/option_t_final_file_not_10.txt | sed 's/;/ /g' > ../../file/option_t_final_file_10.txt");
    //okfile

    FILE * file_sorted_abr = fopen("../../file/option_t_final_file_10.txt", "r");
    if(file_sorted_abr==NULL){exit(999);}


    Abr *abr=NULL;
    abr = constructionFinalAbr(abr);
    
    FILE *final_file = fopen("../../file/t_data.data", "a");
    if(final_file==NULL){exit(567);}
    infixAbr(abr,final_file);

    fclose(file);
    fclose(file_sorted_abr);
    fclose(final_file);
    free(newFifo);

    freeMemoryTree(b);
    
    freeMemoryTree(a);
    freeMemoryAbr(abr);
    
    return 0;
}
