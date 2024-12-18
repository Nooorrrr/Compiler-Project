#include <stdio.h>
#include <stdlib.h>
#include "quadruplet.h"
#include <string.h>

int quadIndex =0;

//ajot un quadruplet dans la table
void addQuad (char * o,char* op1,char*op2, char*temp){
    quadTab[quadIndex].operatr = o;
    quadTab[quadIndex].oprend1 = op1;
    quadTab[quadIndex].opernd2 = op2;
    quadTab[quadIndex].temp = temp;
    quadIndex++;
}

//afficher 

void showQuad(){
    for(int i =0; i <quadIndex;i++){
        printf("%d- (%s ,%s ,%s ,%s)\n",quadTab[i].operatr,quadTab[i].oprend1,quadTab[i].opernd2,quadTab[i].temp);
    }
}

