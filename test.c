VAR_GLOBAL {
    INTEGER A,B,C;
    INTEGER Q,I;  
    FLOAT X,L;
    CONST INTEGER Z = 3;
    
}

DECLARATION { %%affectations
   CONST INTEGER N= 6;
  %% CHAR Y[8] = "hello";
}

INSTRUCTION {
     C = 1;
     A =5;
     B=3;
    IF (A > B){
        C = A + 1;
         C = A- 1;
    } ELSE {
        C = A- 1;
         C = A- 1;
    }
 FOR (I = 0 : 1 : 10) {
    Q = Q + 1;
}
}
