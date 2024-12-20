VAR_GLOBAL {
    INTEGER A,B,C;
    INTEGER Q;
    INTEGER Q, Z, T;%%     affectations    
    INTEGER Q, Z, T;
    FLOAT X,L;
    CHAR Y[8];
    CHAR X[8];
    CONST INTEGER Z = 5;
    
}

DECLARATION { %%affectations
    FLOAT X,L;
    CHAR X[8];
    CONST INTEGER Z = 5;
}

INSTRUCTION {
     C = A- 1;
    IF ((A > B) && (A > B)){
        C = A + 1;
         C = A- 1;
    } ELSE {
        C = A- 1;
         C = A- 1;
    }
 FOR (INTEGER I = 0 : 1 : 10) {
    X = X + 1;
    READ(A);
    WRITE("hi");
    WRITE("hii",A,"hi");
    WRITE("hii",A,"hi,");

}
}
