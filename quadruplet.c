#include <stdio.h>
#include <stdlib.h>
#include "quadruplet.h"
#include <string.h>

int index =0;

//ajot un quadruplet dans la table
void addQuad (char * o,char* op1,char*op2, char*temp){
    quadTab[index].operatr = o;
    quadTab[index].oprend1 = op1;
    quadTab[index].opernd2 = op2;
    quadTab[index].temp = temp;
    index++;
}

//afficher 

void showQuad(){
    for(int i =0; i <index;i++){
        printf("%d- (%s ,%s ,%s ,%s)\n",quadTab[i].operatr,quadTab[i].oprend1,quadTab[i].opernd2,quadTab[i].temp);
    }
}