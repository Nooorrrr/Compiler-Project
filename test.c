VAR_GLOBAL {
    INTEGER A;
    CONST FLOAT Pi = 3.14;
    CHAR C;
    INTEGER Q;  
    FLOAT Y;
    CONST INTEGER Max= 100;
    CONST CHAR D = 'X';
}

DECLARATION { %% local variables
   INTEGER N;
   CONST INTEGER Min = 1;
   CHAR Z;
}

INSTRUCTION {
    A = Max - Min;
    C = 'G';
    N=20/3;
    Y=4*A;
    
    IF ((A > Min) || (C == 'G')) {
        Q = A + Max;
        Y = Y / 2;
    } ELSE {
        Q = Min * 2;
        Y = Pi+ 5;
    }

    FOR (I = 0 : 2 : 20) {
        Y = Y + I;
        IF (I % 2 == 0) {
            A = A + I;
        }
    }
    
    WHILE (Y < MAX) {
        Y = Y + 1;
    }
    
    SWITCH (A) {
        CASE 10:
            Q = A + 1;
            BREAK;
        CASE 20:
            Q = A + 2;
            BREAK;
        DEFAULT:
            Q = A;
    }
}