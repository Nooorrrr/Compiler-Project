VAR_GLOBAL {
    INTEGER A;
    CONST CHAR B="M";
    CHAR C;
    INTEGER Q;  
    FLOAT X;
    CONST INTEGER Z = 5;
    CONST INTEGER L = 1;
    
}

DECLARATION { %%affectations
   CONST INTEGER N= 4;
   CHAR D;

}

INSTRUCTION {
    A=N+N;
  
   D="h";

 
     
    IF ((A > Q) && (A > Q)){
        Q = A + 1;
         Q = A- 1;
    } ELSE {
        Q = A- 1;
         Q = A- 1;
    }
 FOR (I = 0 : 1 : 10) {
    X = X + 1;
}
}
