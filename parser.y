%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "TS.h"  // Inclure la table des symboles
void yyerror(const char *s);  // Déclaration de la fonction d'erreur
%}

%token VAR_GLOBAL DECLARATION INSTRUCTION INTEGER FLOAT CHAR CONST IF ELSE FOR READ WRITE
%token IDENTIFIER NUMBERINTPOS NUMBERINTNEG NUMBERFLOATPOS NUMBERFLOATNEG
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
    varGloballist declarat
    | /* Vide */
    ;

declarat:
    type listevariable SEMICOLON               // Déclaration d'une variable simple
        {
            // Ajouter à la table des symboles
            for (int i = 0; i < $2; i++) {
                if (rechercher(Tab, $2[i].name) == NULL) {
                    inserer(Tab, $2[i].name, $1, 0, 0.0f, 0, 0);
                } else {
                    yyerror("Variable déjà déclarée.");
                }
            }

        }
    | CONST type IDENTIFIER ASSIGN expressionarithmetic SEMICOLON // Déclaration de constante
        {
            if (rechercher(Tab, $3) == NULL) {
                inserer(Tab, $3, $2, 1, $5, 0, 0);
            } else {
                yyerror("Constante déjà déclarée.");
            }
        }
    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON; // Tableau ou chaîne
        {
            if (rechercher(Tab, $2) == NULL) {
                inserer(Tab, $2, $1, 0, 0.0f, 1, $4);
            } else {
                yyerror("Tableau déjà déclaré.");
            }
        }
    ;

listevariable:
    listevariable COMMA IDENTIFIER 
    | IDENTIFIER;


type:
    INTEGER
    | FLOAT
    | CHAR
    ;

affectation:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON
        {
            TableEntry *entry = rechercher(Tab, $1);
            if (entry == NULL) {
                yyerror("Variable non déclarée.");
            } else {
                // Mettre à jour la valeur de la variable
                entry->value = $3;
            }
        }
;

expressionarithmetic:
    IDENTIFIER
        {
            TableEntry *entry = rechercher(Tab, $1);
            if (entry == NULL) {
                yyerror("Variable non déclarée dans l'expression.");
                $$ = 0;  // Valeur par défaut en cas d'erreur
            } else {
                $$ = entry->value;  // Récupérer la valeur de la variable
            }
        }
    | LPAREN expressionarithmetic RPAREN
        { $$ = $2; }  // Parenthèses, la valeur est celle de l'expression à l'intérieur
    | NUMBERINTPOS
        { $$ = $1; }
    | NUMBERINTNEG
        { $$ = $1; }
    | NUMBERFLOATPOS
        { $$ = $1; }
    | NUMBERFLOATNEG
        { $$ = $1; }
    | expressionarithmetic PLUS expressionarithmetic
        { $$ = $1 + $3; }
    | expressionarithmetic MINUS expressionarithmetic
        { $$ = $1 - $3; }
    | expressionarithmetic MULT expressionarithmetic
        { $$ = $1 * $3; }
    | expressionarithmetic DIV expressionarithmetic
        {
            int droite=atoi($3);
            if (droite == 0) {
                yyerror("Division par zéro.");
                $$ = 0;  // Valeur par défaut en cas d'erreur
            } else {
                $$ = $1 / $3;
            }
        }
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

statement:
    affectation
    | IF LPAREN expressionlogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE  // Condition IF
        {
            // Logique pour IF
        }
    | FOR LPAREN initialisation COLON fortext RPAREN LBRACE statements RBRACE
        {
            // Logique pour FOR
        }
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON  // Instruction READ
        {
            // Logique pour READ
            TableEntry *entry = rechercher(Tab, $3);
            if (entry == NULL) {
                yyerror("Variable non déclarée.");
            } else {
                // Lire la valeur et la stocker dans la variable
            }
        }
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON  // Instruction WRITE
        {
            // Logique pour WRITE
            // Afficher la valeur de l'expression
        }
    ;

fortext:
      NUMBER COLON NUMBER     
    |  NUMBER COLON IDENTIFIER   
    |  IDENTIFIER COLON IDENTIFIER     
    | IDENTIFIER COLON NUMBER     
;

initialisation:
  IDENTIFIER ASSIGN expressionarithmetic
;

NUMBER:
    NUMBERINTPOS
    |NUMBERINTNEG;


expressionwrite:
    IDENTIFIER
    |TEXT 
    |TEXT COMMA expressionwrite
    |IDENTIFIER COMMA expressionwrite
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
