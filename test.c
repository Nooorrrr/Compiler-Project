

VAR_GLOBAL {
    INTEGER Q;
    INTEGER Q, Z, T;
    INTEGER Q, Z, T;
    FLOAT X,L;
    CHAR X[8];
    CONST INTEGER Z = 5;
}

DECLARATION {
    A= (X + 2) * Y;
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
    FOR (i = 0 : 1 : 10) {
        X= X + 1;
    }
}
