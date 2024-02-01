#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "prototype_s.h"

#define NAME_SIZE 150
#define SIZE 42

int main(void) {

    //first avl with the data.csv values, sorted by routeID
    Tree* a;
    a = firstAVL(a);
    

    //firt avl into a fifo -> to put the values sorted differently in the second avl
    Fifo f = {NULL, NULL};
    arbreToFile(a, &f); //old tree into the fifo

    //previous static fifo into a dynamic one 
    Fifo *newFifo = createFifo();
    Tree *temp;
    while(f.pHead != NULL){
        defiler(&f,&temp);
        enfiler(newFifo, temp);
    }
    
    //the second avl sorted by max-min values
    Tree*b;
    b = fileToAvl(newFifo);

    //final file
    FILE * file = fopen("../../file/option_s_final_file.txt", "a");
    if(file==NULL){exit(999);}

    //putting the values into the second avl, by the file previously opened
    infix_(b, file);
    


    fclose(file);
    freeMemory(a);
    freeMemory(b);
    //no need to free temp : already empty
    return 0;
}
