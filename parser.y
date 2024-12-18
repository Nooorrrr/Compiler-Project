%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h"

void yyerror(const char *s);
int yylex(void);

typedef union {
    int intValue;
    float floatValue;
    char charValue;
    char* stringValue;
    struct {
        char* type;
        Value value;
    } expressionValue;
    IdentifierList identList;
} YYSTYPE;

#define YYSTYPE YYSTYPE

void insertSymbol(const char* name, const char* type, Value value, int is_constant, int array_size);
SymbolTableEntry* findSymbol(const char* name);
int typesCompatible(const char* type1, const char* type2);

%}

%union {
    int intValue;
    float floatValue;
    char charValue;
    char* stringValue;
    struct {
        char* type;
        Value value;
    } expressionValue;
    IdentifierList identList;
}

%token VAR_GLOBAL LBRACE RBRACE DECLARATION INSTRUCTION SEMICOLON
%token CONST ASSIGN LBRACKET RBRACKET COMMA INTEGER FLOAT CHAR LPAREN RPAREN
%token <intValue> NUMBERINTPOS NUMBERINTNEG
%token <floatValue> NUMBERFLOATPOS NUMBERFLOATNEG
%token <stringValue> TEXT IDENTIFIER
%token COLON

%type <stringValue> type
%type <expressionValue> expressionarithmetic

%%

program:
    declarations instructions
    ;

declarations:
    /* empty */
    | declarations declaration
    ;

declaration:
    VAR_GLOBAL IDENTIFIER COLON type SEMICOLON
    {
        Value defaultValue;
        if (strcmp($4, "INTEGER") == 0)
            defaultValue.intValue = 0;
        else if (strcmp($4, "FLOAT") == 0)
            defaultValue.floatValue = 0.0;
        else if (strcmp($4, "CHAR") == 0)
            defaultValue.charValue = '\0';

        insertSymbol($2, $4, defaultValue, 0, 0);
        free($2);
        free($4);
    }
    ;

type:
    INTEGER { $$ = strdup("INTEGER"); }
    | FLOAT { $$ = strdup("FLOAT"); }
    | CHAR { $$ = strdup("CHAR"); }
    ;

instructions:
    /* empty */
    | instructions instruction
    ;

instruction:
    affectation
    ;

affectation:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON
    {
        SymbolTableEntry* symbol = findSymbol($1);
        if (symbol == NULL) {
            char errorMsg[100];
            sprintf(errorMsg, "Variable '%s' not declared", $1);
            yyerror(errorMsg);
        } else if (symbol->is_constant) {
            char errorMsg[100];
            sprintf(errorMsg, "Cannot modify constant '%s'", $1);
            yyerror(errorMsg);
        } else if (!typesCompatible(symbol->type, $3.type)) {
            char errorMsg[100];
            sprintf(errorMsg, "Type mismatch for variable '%s'", $1);
            yyerror(errorMsg);
        } else {
            // Update symbol value
            if (strcmp(symbol->type, "INTEGER") == 0)
                symbol->value.intValue = $3.value.intValue;
            else if (strcmp(symbol->type, "FLOAT") == 0)
                symbol->value.floatValue = $3.value.floatValue;
            else if (strcmp(symbol->type, "CHAR") == 0)
                symbol->value.charValue = $3.value.charValue;
        }
        free($1);
        free($3.type);
    }
    ;

expressionarithmetic:
    NUMBERINTPOS { $$ = $1; }
    | NUMBERINTNEG { $$ = $1; }
    | NUMBERFLOATPOS { $$ = $1; }
    | NUMBERFLOATNEG { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Error: no file specified.\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Error: could not open file %s\n", argv[1]);
        return 1;
    }

    yyin = f;
    yyparse();
    fclose(f);

    return 0;
}