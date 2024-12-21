VAR_GLOBAL {
    INTEGER A,B,C;
    INTEGER Q;  
    FLOAT X,L;
    CONST INTEGER Z = 3;
    
}

DECLARATION { %%affectations
   CONST INTEGER N= 6;
   INTEGER I;
}

INSTRUCTION {
     C = 1;
     
    IF ((A > B) && (A > B)){
        C = A + 1;
         C = A- 1;
    } ELSE {
        C = A + 2 ;
         C = A- 1;
    }
 FOR ( I = 0 : 1 : 10) {
    X = X + 1;
}

N = 32767 ;
}