%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
void yyerror(const char *s);  // Déclaration de la fonction d'erreur
%}

%token VAR_GLOBAL DECLARATION INSTRUCTION INTEGER FLOAT CHAR CONST IF ELSE FOR READ WRITE
%token IDENTIFIER NUMBER
%token AND OR NOT EQUAL NEQ GTE LTE GT LT
%token LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMICOLON COMMA ASSIGN
%token PLUS MINUS MULT DIV

%left PLUS MINUS    // Définir les priorités des opérateurs
%left MULT DIV
%left AND OR
%left EQUAL NEQ GT LT GTE LTE
%nonassoc NOT

%%

/* Règles de la grammaire */
program:
    VAR_GLOBAL LBRACE varGloballist RBRACE DECLARATION LBRACE declarationlist RBRACE INSTRUCTION LBRACE statements RBRACE
    ;

varGloballist:
    varGloballist declaration
    | /* Vide */
    ;

declaration:
    type listevariable SEMICOLON               // Déclaration d'une variable simple
    | CONST type IDENTIFIER ASSIGN expressionarithmetic  SEMICOLON // Déclaration de constante
    | type IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON;
    ;

listevariable:
    listevariable COMMA IDENTIFIER 
    | IDENTIFIER;


type:
    INTEGER
    | FLOAT
    | CHAR
    ;


declarationlist:
    declaration declarationlist
    | /* Vide */
    ;

declaration:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON
;
expressionarithmetic:
    IDENTIFIER
    |LPAREN expressionarithmetic RPAREN
    | NUMBER                            // Nombre
    | expressionarithmetic PLUS expressionarithmetic        // Addition
    | expressionarithmetic MINUS expressionarithmetic       // Soustraction
    | expressionarithmetic MULT expressionarithmetic        // Multiplication
    | expressionarithmetic DIV expressionarithmetic         // Division
    ;

expressionlogic:                  
    | LPAREN expressionlogic RPAREN          // Parenthèses
    | NOT expressionlogic                     // Négation logique
    | expressionlogic AND expressionlogic         // Et logique
    | expressionlogic OR expressionlogic          // Ou logique
    | expressionlogic EQUAL expressionlogic       // Égalité
    | expressionlogic NEQ expressionlogic         // Différence
    | expressionarithmetic LT expressionarithmetic          // Inférieur
    | expressionarithmetic LTE expressionarithmetic         // Inférieur ou égal
    | expressionarithmetic GT expressionarithmetic          // Supérieur
    | expressionarithmetic GTE expressionarithmetic         // Supérieur ou égal
    ;

statements:
    statement
    | statements statement
    ;

// a revoir keml kima rahoum
statement:
    declaration
    | IF LPAREN expressionlogic RPAREN LBRACE statements RBRACE  ELSE LBRACE statements RBRACE  // Condition IF
    | FOR LPAREN statement expressionlogic SEMICOLON statement RPAREN statement  // Boucle FOR
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON  // Instruction READ
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON  // Instruction WRITE
    ;

expressionwrite:
    //mezel mdrtha
    ;

%%

void yyerror(const char *s) {
    extern int yylineno;  // Déclarer yylineno qui est utilisé par flex pour suivre les numéros de ligne
    fprintf(stderr, "Erreur à la ligne %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Erreur : aucun fichier spécifié.\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    yyin = f;
    yyparse();  // Appeler le parseur
    fclose(f);
    return 0;
}
