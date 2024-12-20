%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "ts.h"      // Inclure le fichier d'en-tête de la table de symboles
#include "quadruplet.h"  // Le fichier où tu définis ta structure Quadruplet

extern int scope;  // Déclaration de la variable scope
extern TableEntry Tab[1000];  // Table des identifiants et constantes
int scope = 0;  // Initialisation de scope
void yyerror(const char *s);  // Déclaration de la fonction d'erreur

%}
%union {
    int entier;        // Pour les entiers
    float flottant;    // Pour les nombres flottants
    char* chaine;      // Pour les chaînes de caractères
    struct
     { char** variables;
       int count; 
    } varList;  // Pour gérer une liste de variables
     struct { 
        char* type;    // Le type de l'expression (par exemple: "int", "float")
        char** variables; 
        int count; 
    } expr;     
}
 

%token <entier> NUMBERINTPOS NUMBERINTNEG
%token <flottant> NUMBERFLOATPOS NUMBERFLOATNEG
%token <chaine> IDENTIFIER caractere
%type <chaine> type
%type <varList>  listevariable
%type <expr> expressionarithmetic expressionlogic

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
        type listevariable SEMICOLON {
        // Boucle sur chaque variable dans listevariable
        for (int i = 0; i < $2.count; i++) {
            if (rechercher($2.variables[i]) != NULL) {
                yyerror("Variable déjà déclarée.");
                return 0;
            } else {
               inserer($2.variables[i], $1, 0, scope, 0, 0, 0);  // Insérer la variable (pas un tableau, pas une constante)

            }
        }
    }

    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON {
           if (rechercher($2) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($2, $1, 0, scope, 0, $4, 1);
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERINTPOS SEMICOLON {
         if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
          inserer($3, $2, $5, scope, 1, 0, 0);
        }
    } 
    | CONST type IDENTIFIER ASSIGN NUMBERINTNEG SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
         inserer($3, $2, $5, scope, 1, 0, 0);
        }
    } 
    | CONST type IDENTIFIER ASSIGN NUMBERFLOATPOS SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3, $2, $5, scope, 1, 0, 0);
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERFLOATNEG SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
          inserer($3, $2, $5, scope, 1, 0, 0);
        }
    }
    ;
listevariable:
    listevariable COMMA IDENTIFIER {
        $$ = $1;  // Copier la liste précédente
        $$ .count++;  // Incrémenter le nombre d'éléments
        $$ .variables = realloc($$.variables, sizeof(char*) * $$ .count);
        $$ .variables[$$.count - 1] = $3;  // Ajouter la nouvelle variable
    }
    | IDENTIFIER {
        $$ .count = 1;  // Une seule variable
        $$ .variables = malloc(sizeof(char*));
        $$ .variables[0] = $1;
    }
    ;

/*listevariable:
    listevariable COMMA IDENTIFIER
    | IDENTIFIER 
    ;*/
type:
    INTEGER { $$ = "INTEGER"; }
    | FLOAT { $$ = "FLOAT"; }
    | CHAR { $$ = "CHAR"; }
    ;

/*affectation:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON
    
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
expressionwrite:
    IDENTIFIER
    | TEXT
    | TEXT COMMA expressionwrite
    | IDENTIFIER COMMA expressionwrite
    ;

*/
affectation:
    IDENTIFIER ASSIGN expressionarithmetic SEMICOLON {
        // Vérification si la variable est déclarée
        if (rechercher($1) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        } else {
            // Vérification des types (assumer qu'on a un champ type dans la table des symboles)
            char *varType = rechercher($1)->type;
            char *exprType = $3.type; // Ici, tu devras récupérer le type de l'expression
            if (strcmp(varType, exprType) != 0) {
                yyerror("Type incompatible dans l'affectation.");
                return 0;
            }
        }
    }
;
expressionarithmetic:
    IDENTIFIER {
        // Vérifier que la variable est déclarée et obtenir son type
        if (rechercher($1) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        } else {
            $$.type = rechercher($1)->type;
        }
    }
    | LPAREN expressionarithmetic RPAREN {
        $$ = $2;  // Propagation du type
    }
    | NUMBER {
        $$.type = "INTEGER";  // Ou FLOAT selon le type de NUMBER
    }
    | expressionarithmetic PLUS expressionarithmetic {
        // Vérification des types pour l'opération arithmétique
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles.");
            return 0;
        }
        $$.type = $1.type;  // Le résultat a le même type que les opérandes
    }
    | expressionarithmetic MINUS expressionarithmetic {
        // Logique similaire pour l'opération de soustraction
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles.");
            return 0;
        }
        $$.type = $1.type;
    }
    | expressionarithmetic MULT expressionarithmetic {
        // Vérification pour multiplication
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles.");
            return 0;
        }
        $$.type = $1.type;
    }
    | expressionarithmetic DIV expressionarithmetic {
        // Vérification pour division
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles.");
            return 0;
        }
        $$.type = $1.type;
    }
;
expressionlogic:
    expressionarithmetic LT expressionarithmetic {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
    }
    | expressionarithmetic LTE expressionarithmetic {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expressionarithmetic GT expressionarithmetic {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expressionarithmetic GTE expressionarithmetic {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expressionlogic AND expressionlogic {
        // Vérification que les deux opérandes sont booléens
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique AND.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expressionlogic OR expressionlogic {
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique OR.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | NOT expressionlogic {
        if (strcmp($2.type, "BOOLEAN") != 0) {
            yyerror("L'opérande de NOT doit être de type BOOLEAN.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
;

statements:
    statement
    | statements statement
    ;

statement:
    affectation
    |IF LPAREN expressionlogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
        // Vérifier que la condition dans IF est de type booléen
        if (strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("La condition de l'instruction IF doit être de type BOOLEAN.");
            return 0;
        }
    }
    | FOR LPAREN initialisation COLON fortext RPAREN LBRACE statements RBRACE {
        // Vérifier la validité des types dans la boucle
        // Par exemple, vérifier que le type de la variable utilisée dans la boucle est compatible avec la condition
    }
    |READ LPAREN IDENTIFIER RPAREN SEMICOLON {
        if (rechercher($3) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON {
        // Vérification que l'expression à écrire est valide
    }
;

expressionwrite:
    IDENTIFIER
    | TEXT
    | TEXT COMMA expressionwrite
    | IDENTIFIER COMMA expressionwrite
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

fortext:
    NUMBERINT COLON NUMBERINT
    | NUMBERINT COLON IDENTIFIER
    | IDENTIFIER COLON IDENTIFIER
    | IDENTIFIER COLON NUMBERINT
;
%%

;

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