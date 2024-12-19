%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "ts.h"      // Inclure le fichier d'en-tête de la table de symboles

extern int scope;  // Déclaration de la variable scope
extern TableEntry Tab[1000];  // Table des identifiants et constantes
int scope = 0;  // Initialisation de scope
void yyerror(const char *s);  // Déclaration de la fonction d'erreur

%}
%union {
    int entier;        // Pour les entiers
    float flottant;    // Pour les nombres flottants
    char* chaine;      // Pour les chaînes de caractères
}
 

%token <entier> NUMBERINTPOS NUMBERINTNEG
%token <flottant> NUMBERFLOATPOS NUMBERFLOATNEG
%token <chaine> IDENTIFIER caractere
%type <chaine> type

%token VAR_GLOBAL DECLARATION INSTRUCTION INTEGER FLOAT CHAR CONST IF ELSE FOR READ WRITE
%token AND OR NOT EQUAL NEQ GTE LTE GT LT
%token LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMICOLON COMMA ASSIGN COLON
%token PLUS MINUS MULT DIV
%token TEXT

%left PLUS MINUS    // Définir les priorités des opérateurs
%left MULT DIV
%left AND OR
%left EQUAL NEQ GT LT GTE LTE
%nonassoc NOT

%%

/* Règles de la grammaire */
program:
    VAR_GLOBAL LBRACE varGloballist RBRACE DECLARATION LBRACE varGloballist RBRACE INSTRUCTION LBRACE statements RBRACE
    ;

varGloballist:
    varGloballist declaration
    | /* Vide */
    ;

declaration:
    type listevariable SEMICOLON 
    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON {
           if (rechercher($2) != NULL) {
            yyerror("Variable déjà déclarée.");
        } else {
          inserer($2, $1, 0, scope, 0, $4, 1);
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERINTPOS SEMICOLON {
         if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
        } else {
           inserer($3, $2, $5, scope, 1, 0, 0);
        }
    } 
    | CONST type IDENTIFIER ASSIGN NUMBERINTNEG SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
        } else {
           inserer($3, $2, $5, scope, 1, 0, 0);
        }
    } 
    | CONST type IDENTIFIER ASSIGN NUMBERFLOATPOS SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
        } else {
           inserer($3, $2, $5, scope, 1, 0, 0);
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERFLOATNEG SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
        } else {
           inserer($3, $2, $5, scope, 1, 0, 0);
        }
    }
    ;

listevariable:
    listevariable COMMA IDENTIFIER
    | IDENTIFIER
    ;

type:
    INTEGER { $$ = "INTEGER"; }
    | FLOAT { $$ = "FLOAT"; }
    | CHAR { $$ = "CHAR"; }
    ;

affectation:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON
;

expressionarithmetic:
    IDENTIFIER
    | LPAREN expressionarithmetic RPAREN
    | NUMBER
    | expressionarithmetic PLUS expressionarithmetic
    | expressionarithmetic MINUS expressionarithmetic
    | expressionarithmetic MULT expressionarithmetic
    | expressionarithmetic DIV expressionarithmetic
    ;

expressionlogic:
    | LPAREN expressionlogic RPAREN
    | NOT expressionlogic
    | expressionlogic AND expressionlogic
    | expressionlogic OR expressionlogic
    | expressionlogic EQUAL expressionlogic
    | expressionlogic NEQ expressionlogic
    | expressionarithmetic LT expressionarithmetic
    | expressionarithmetic LTE expressionarithmetic
    | expressionarithmetic GT expressionarithmetic
    | expressionarithmetic GTE expressionarithmetic
    ;

statements:
    statement
    | statements statement
    ;

statement:
    affectation
    | IF LPAREN expressionlogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE
    | FOR LPAREN initialisation COLON fortext RPAREN LBRACE statements RBRACE
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON
    ;

fortext:
    NUMBERINT COLON NUMBERINT
    | NUMBERINT COLON IDENTIFIER
    | IDENTIFIER COLON IDENTIFIER
    | IDENTIFIER COLON NUMBERINT
;

initialisation:
    IDENTIFIER ASSIGN expressionarithmetic
;

NUMBERINT:
    NUMBERINTPOS
    | NUMBERINTNEG;

NUMBER:
    NUMBERINT
    | NUMBERFLOATPOS
    | NUMBERFLOATNEG;

expressionwrite:
    IDENTIFIER
    | TEXT
    | TEXT COMMA expressionwrite
    | IDENTIFIER COMMA expressionwrite
    ;

%%

void yyerror(const char *s) {
    extern int yylineno;
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

    initialisation();
    yyin = f;
    yyparse();
    afficherTable(Tab, 1000);
    fclose(f);
    return 0;
}
