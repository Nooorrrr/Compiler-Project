VAR_GLOBAL {
    INTEGER A,B,C;
    INTEGER Q;  
    FLOAT X;
    CONST INTEGER Z = 5;
    CONST INTEGER L = 1;
    
}

DECLARATION { %%affectations
   CONST INTEGER N= 4;
   INTEGER D;

}

INSTRUCTION {
     C = Z+N;
    D= 15*10;
     
    IF ((A > B) && (A > B)){
        C = A + 1;
         C = A- 1;
    } ELSE {
        C = A- 1;
         C = A- 1;
    }
 FOR (I = 0 : 1 : 10) {
    X = X + 1;
}
}
