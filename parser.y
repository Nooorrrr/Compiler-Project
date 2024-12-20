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
    char car;
    struct { 
        char** variables;
        int count; 
    } varList;  // Pour gérer une liste de variables

    // Déclaration de l'union Value
    union {
        char cval;     // Caractère
        int ival;      // Entier
        float fval;    // Flottant
    } Value;  // Union pour stocker la valeur

    struct { 
        char* type;    // Le type de l'expression (par exemple: "int", "float")
        char** variables; 
        int count; 
        union {         // Utilisation de l'union pour la valeur
            char cval;
            int ival;
            float fval;
        } value;
    } exprari;

    struct { 
        char* type;    // Le type de l'expression (par exemple: "int", "float")
        char** variables; 
        int count; 
    } exprlog;    
}

%token <entier> NUMBERINTPOS NUMBERINTNEG 
%token <flottant> NUMBERFLOATPOS NUMBERFLOATNEG
%token <chaine> IDENTIFIER 
%type <chaine> type
%type <varList>  listevariable
%type <exprari> expression 
%type <exprlog> expressionlogic expressionslogic
%token<car> CARACTERE
%type <entier> NUMBERINT 
%type <flottant> NUMBERFLOAT




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
    ;declaration:
    type listevariable SEMICOLON {
        for (int i = 0; i < $2.count; i++) {
            if (rechercher($2.variables[i]) != NULL) {
                yyerror("Variable déjà déclarée.");
                return 0;
            } else {
                if (strcmp($1, "INTEGER") == 0) {
                    inserer($2.variables[i], $1, 0, scope, 0, 0, 0);  // Insérer sans valeur initiale pour une variable
                } else if (strcmp($1, "FLOAT") == 0) {
                    inserer($2.variables[i], $1, 0.0f, scope, 0, 0, 0);  // Insérer un flottant
                } else if (strcmp($1, "CHAR") == 0) {
                    inserer($2.variables[i], $1, '\0', scope, 0, 0, 0);  // Insérer un caractère (valeur nulle par défaut)
                }
            }
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERINT SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
           
            inserer($3, $2,$5, scope, 0, 0, 1);  // Insérer la constante entière
  
        }
    }
    | CONST type IDENTIFIER ASSIGN NUMBERFLOAT SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3, $2, $5, scope, 0, 0, 1);  // Insérer la constante flottante
        }
    }
     | CONST type IDENTIFIER ASSIGN CARACTERE SEMICOLON {
        if (rechercher($3) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3, $2, $5, scope, 0, 0, 1);  // Insérer la constante flottante
        }
    }
    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON {
           if (rechercher($2) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($2, $1, 0, scope, 0, $4, 1);
        }
    };

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
    /*
*/// Affectation
// Affectation et expression dans un même bloc
affectation:
    IDENTIFIER ASSIGN expression SEMICOLON {
        // Vérification si la variable est déclarée
        TableEntry *varEntry = rechercher($1);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }

        // Vérification si la variable est une constante et ne peut pas être modifiée
        if (varEntry->isConst == 1) {
            yyerror("Vous essayez de modifier une constante.");
            return 0;
        }

        // Vérification de la compatibilité des types entre la variable et l'expression
        if(strcmp(varEntry->type,"INTEGER")== 0||strcmp(varEntry->type,"CHAR")== 0){
        if (strcmp(varEntry->type, $3.type) != 0) {
            yyerror("Type incompatible dans l'affectation.test1");
            return 0;
        }
        }
        if(strcmp(varEntry->type,"FLOAT")== 0){
            if (strcmp($3.type, "CHAR") == 0) {
            yyerror("Type incompatible dans l'affectation.2");
            return 0;
        }
        }
         if(strcmp(varEntry->type,"CHAR")== 0){
            if (strcmp($3.type, "CHAR") != 0) {
            yyerror("Type incompatible dans l'affectation.3");
            return 0;
        }
        }
        

        // Modification de la valeur en fonction du type
        if (strcmp(varEntry->type, "INTEGER") == 0) {
            varEntry->val.ival = $3.value.ival;  // Affecter un entier
        } else if (strcmp(varEntry->type, "FLOAT") == 0) {
            varEntry->val.fval = $3.value.fval;  // Affecter un flottant
            if(strcmp($3.type,"INTEGER") == 0){
                varEntry->val.fval = (float) $3.value.ival;
            }
        } else if (strcmp(varEntry->type, "CHAR") == 0) {
            varEntry->val.cval = $3.value.cval;  // Affecter un caractère
        } else {
            yyerror("Type inconnu pour l'affectation.4");
            return 0;
        }
    }
;


// Expression générale (affectation ou arithmétique)
expression:
    IDENTIFIER {
        TableEntry *entry = rechercher($1);
        if (entry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        
        $$.type = entry->type;

        // Affectation de valeur selon le type de la variable
        if (strcmp($$.type, "INTEGER") == 0) {
            $$.value.ival = entry->val.ival;
        } else if (strcmp($$.type, "FLOAT") == 0) {
            $$.value.fval = entry->val.fval;
        } else if (strcmp($$.type, "CHAR") == 0) {
            $$.value.cval = entry->val.cval;
        }
    }
    | NUMBERINT {
        $$.type = "INTEGER";
        $$.value.ival = $1;

    }
    | NUMBERFLOAT {
        $$.type = "FLOAT";
        $$.value.fval = $1;
       
    }
    | CARACTERE {
        $$.type = "CHAR";
        $$.value.cval = $1;  // Valeur du caractère
    }
    | expression PLUS expression{
    // Vérifier la compatibilité des types avant de faire l'opération
    if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
        // Si les deux sont des entiers
        $$.type = "INTEGER";
        $$.value.ival = $1.value.ival + $3.value.ival;
        printf("%d",$$.value.ival);
    }
    else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($1.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval + $3.value.fval;
    } 
    else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour l'addition.");
        return 0;
    }
    }
    | expression MINUS expression{
    // Vérifier la compatibilité des types avant de faire l'opération
    if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
        // Si les deux sont des entiers
        $$.type = "INTEGER";
        $$.value.ival = $1.value.ival - $3.value.ival;
     
    }
    else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($1.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval - $3.value.fval;
    } 
    else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la soustraction.");
        return 0;
    }
    }
    | expression MULT expression {
    // Vérifier la compatibilité des types avant de faire l'opération
    if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
        // Si les deux sont des entiers
        $$.type = "INTEGER";
        $$.value.ival = $1.value.ival * $3.value.ival;
       
    }
    else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($1.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval * $3.value.fval;
    } 
    else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la multiplication.");
        return 0;
    }
    }

    | expression DIV expression{
    // Vérifier la compatibilité des types avant de faire l'opération
    if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
        // Si les deux sont des entiers
        $$.type = "INTEGER";
         if($3.value.fval==0){
              yyerror("division sur 0 impossible.");
        }else{  
            $$.value.ival = $1.value.ival / $3.value.ival;
        }
      
    }
    else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($1.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
        $$.type = "FLOAT";
      if($3.value.fval==0){
              yyerror("division sur 0 impossible.");
       }else{
         $$.value.ival = $1.value.ival / $3.value.ival;
       }
    } 
    else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la multiplication.");
        return 0;
    }
    }
       
    
    |LPAREN expression RPAREN
    {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.variables = $2.variables;
        $$.count = $2.count;
        $$.value = $2.value;
        
    }
   
;



type:
    INTEGER { $$ = "INTEGER"; }
    | FLOAT { $$ = "FLOAT"; }
    | CHAR { $$ = "CHAR"; }
    ;



expressionlogic:
    LPAREN expressionlogic RPAREN
    {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.variables = $2.variables;
        $$.count = $2.count;
    }
    |expression LT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
    }
    | expression LTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expression GT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";
    }
    | expression GTE expression {
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

expressionslogic:
expressionlogic
|expressionslogic expressionlogic
;
statement:
    affectation
    |IF LPAREN expressionslogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
        // Vérifier que la condition dans IF est de type booléen
        if (strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("La condition de l'instruction IF doit être de type BOOLEAN.");
            return 0;
        }
    }
    | FOR LPAREN affectation COLON fortext RPAREN LBRACE statements RBRACE {
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
    IDENTIFIER {    TableEntry *varEntry = rechercher($1);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        }
    | TEXT
    | TEXT COMMA expressionwrite
    | IDENTIFIER COMMA expressionwrite{
            TableEntry *varEntry = rechercher($1);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
    ;




NUMBERINT:
    NUMBERINTPOS
    | NUMBERINTNEG;
NUMBERFLOAT:
    NUMBERFLOATNEG
    | NUMBERFLOATPOS;



fortext:
    NUMBERINT COLON NUMBERINT
    | NUMBERINT COLON IDENTIFIER 
       { TableEntry *varEntry = rechercher($3);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }}
    | IDENTIFIER COLON IDENTIFIER
        { TableEntry *varEntry = rechercher($1);
           TableEntry *varEntry2 = rechercher($3);
        if (varEntry == NULL || varEntry2==NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        }
    | IDENTIFIER COLON NUMBERINT
       { TableEntry *varEntry = rechercher($1);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }}
;
%%

;

void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Erreur à la ligne %d: %s\n", yylineno, s);
}

// int main(int argc, char **argv) {
//     if (argc < 2) {
//         fprintf(stderr, "Erreur : aucun fichier spécifié.\n");
//         return 1;
//     }

//     FILE *f = fopen(argv[1], "r");
//     if (!f) {
//         perror("Erreur d'ouverture du fichier");
//         return 1;
//     }

//     initialisation();
//     yyin = f;
//     yyparse();
//     afficherTable(Tab, 1000);
//     fclose(f);
//     return 0;
// }

/*listevariable:
    listevariable COMMA IDENTIFIER
    | IDENTIFIER 
    ;*/

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