#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "TS.h"      // Inclure la table des symboles

void yyerror(const char *s);  // Déclaration de la fonction d'erreur

// Fonction pour vérifier la compatibilité des types lors d'une affectation
int typesCompatibles(const char *typeVar, Value val) {
    if (strcmp(typeVar, "INTEGER") == 0 && (val.floatValue == 0)) {
        return 1;  // INTEGER peut accepter un int ou un float
    } else if (strcmp(typeVar, "FLOAT") == 0 && (val.intValue == 0)) {
        return 1;  // FLOAT peut accepter un float
    } else if (strcmp(typeVar, "CHAR") == 0 && (val.intValue >= 0 && val.intValue <= 255)) {
        return 1;  // CHAR peut accepter un char
    }
    return 0;
}

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
    type listevariable SEMICOLON  // Déclaration d'une variable simple
        {
            for (int i = 0; i < $2; i++) {
                if (rechercher(Tab, $2[i].name) == NULL) {
                    inserer(Tab, $2[i].name, $1, 0, 0.0f, 0, 0);
                } else {
                    yyerror("Variable déjà déclarée.");
                }
            }
        }
    | CONST type IDENTIFIER ASSIGN expressionarithmetic SEMICOLON  // Déclaration de constante
        {
            if (rechercher(Tab, $3) == NULL) {
                inserer(Tab, $3, $2, 1, $5, 0, 0);
            } else {
                yyerror("Constante déjà déclarée.");
            }
        }
    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON;  // Déclaration de tableau
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
                if (!typesCompatibles(entry->type, $3)) {
                    yyerror("Type de l'expression incompatible avec la variable.");
                } else {
                    entry->value = $3;
                }
            }
        }
;

expressionarithmetic:
    IDENTIFIER
        {
            TableEntry *entry = rechercher(Tab, $1);
            if (entry == NULL) {
                yyerror("Variable non déclarée dans l'expression.");
                $$ = (Value){.intValue = 0};  // Valeur par défaut en cas d'erreur
            } else {
                $$ = entry->value;  // Récupérer la valeur de la variable
            }
        }
    | LPAREN expressionarithmetic RPAREN
        { $$ = $2; }
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
            if ($3.intValue == 0 || $3.floatValue == 0) {
                yyerror("Division par zéro.");
                $$ = (Value){.intValue = 0};  // Valeur par défaut en cas d'erreur
            } else {
                $$ = $1 / $3;
            }
        }
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
        { /* Logique pour IF */ }
    | FOR LPAREN initialisation COLON fortext RPAREN LBRACE statements RBRACE
        { /* Logique pour FOR */ }
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON
        {
            TableEntry *entry = rechercher(Tab, $3);
            if (entry == NULL) {
                yyerror("Variable non déclarée.");
            } else {
                // Lire la valeur et la stocker dans la variable
            }
        }
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON
        { /* Logique pour WRITE */ }
;

fortext:
    NUMBER COLON NUMBER
    | NUMBER COLON IDENTIFIER
    | IDENTIFIER COLON IDENTIFIER
    | IDENTIFIER COLON NUMBER
;

initialisation:
    IDENTIFIER ASSIGN expressionarithmetic
;

NUMBER:
    NUMBERINTPOS
    | NUMBERINTNEG;

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

    yyin = f;
    yyparse();  // Appeler le parseur
    fclose(f);
    return 0;
}
