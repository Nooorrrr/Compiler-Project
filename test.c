VAR_GLOBAL {
    INTEGER A;
    CONST FLOAT Pi = 3; %%(=,3, ,pi)
    CHAR C;
    INTEGER Q;  
    FLOAT Y;
    CONST INTEGER Max= 100;
    CONST CHAR D = 'X';
}

DECLARATION { %% local variables
   INTEGER N,I;
   CONST INTEGER Min = 3;
   CHAR Z;
}

INSTRUCTION {
     
    A = Max - 1;
    
    N=20/3;
    Y=4*A;
    
    IF ((A > Min) ) {
        Q = A + Max;
        Y = Y / 2;
    } ELSE {
        Q = Min * 2;
        Y = Pi+ 5;
    }

    FOR (I = 0 : 2 : 20) {
        Y = Y + Y;
        IF (I + 2 == 0) {
            A = A + I;
        }
    }
    
    
}