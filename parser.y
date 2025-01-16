%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"  // Inclure le fichier généré par Flex
#include "ts.h"      // Inclure le fichier d'en-tête de la table de symboles
#include "quadruplet.h"  // Le fichier où tu définis ta structure Quadruplet
extern int tempCount;
extern int scope;  // Déclaration de la variable scope
extern TableEntry Tab[1000];  // Table des identifiants et constantes
int scope = 0;  // Initialisation de scope
// Structure pour un nœud de pile
typedef struct StackNode {
    char* data;
    struct StackNode* next;
} StackNode;

// Pointeur vers le sommet de la pile
StackNode* else_label_stack = NULL;
StackNode* end_label_stack = NULL;
StackNode* start_label_stack = NULL;


// Fonction pour empiler
void push(StackNode** stack, const char* value) {
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->data = strdup(value); // Copier la chaîne
    new_node->next = *stack;
    *stack = new_node;
}

// Fonction pour dépiler
char* pop(StackNode** stack) {
    if (*stack == NULL) {
        fprintf(stderr, "Erreur : pile vide\n");
        return NULL;
    }
    StackNode* temp = *stack;
    char* value = temp->data;
    *stack = (*stack)->next;
    free(temp);
    return value;
}

// Fonction pour obtenir le sommet sans dépiler
char* top(StackNode* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Erreur : pile vide\n");
        return NULL;
    }
    return stack->data;
}
void yyerror(const char *s);  // Déclaration de la fonction d'erreur
%}
%union {
    int entier;        // Pour les entiers
    float flottant;    // Pour les namebres flottants
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
        char* name;       
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
        char* name;  // Add this line to define the name field
        char* type;    // Le type de l'expression (par exemple: "int", "float")
        int count; 
        char* value;
    } exprlog;    

    struct {
        char* name;        // name d'une entité (chaîne de caractères)
        char** variables; // Tableau de chaînes de caractères
        int count;        // namebre d'éléments dans le tableau
    } id;
}

%token <entier> NUMBERINTPOS NUMBERINTNEG 
%token <flottant> NUMBERFLOATPOS NUMBERFLOATNEG
%token <id> IDENTIFIER 
%type <chaine> type
%type <varList>  listevariable
%type <exprari> expression 
%type <exprlog> expressionlogic expressionslogic
%token<car> CARACTERE
%type <entier> NUMBERINT 
%type <flottant> NUMBERFLOAT
%type <exprari> init_for

%token VAR_GLOBAL DECLARATION INSTRUCTION INTEGER FLOAT CHAR CONST IF ELSE FOR READ WRITE
%token AND OR NOT EQUAL NEQ GTE LTE GT LT
%token LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET SEMICOLON COMMA ASSIGN BOUCLESEPARATOR
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
        if (rechercher($3.name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3.name, $2, $5, scope, 0, 0, 1);  // Insérer la constante entière
        }
         char var2[20];
        sprintf(var2,"%d",  $5);
        generer("=",var2, "", $3.name);
    }
    | CONST type IDENTIFIER ASSIGN NUMBERFLOAT SEMICOLON {
        if (rechercher($3.name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3.name, $2, $5, scope, 0, 0, 1);  // Insérer la constante flottante
        }
         char var2[20];
        sprintf(var2,"%f",  $5);
        generer("=",var2, "", $3.name);
        
    }
    | CONST type IDENTIFIER ASSIGN CARACTERE SEMICOLON {
        if (rechercher($3.name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($3.name, $2, $5, scope, 0, 0, 1);  // Insérer la constante flottante
        }
             char var2[20];
        sprintf(var2,"%c",  $5);
        generer("=",var2, "", $3.name);
    }
    | type IDENTIFIER LBRACKET NUMBERINTPOS RBRACKET SEMICOLON {
        if (rechercher($2.name) != NULL) {
            yyerror("Variable déjà déclarée.");
            return 0;
        } else {
            inserer($2.name, $1, 0, scope, 0, $4, 1);
        }
    }
    ;

listevariable:
    listevariable COMMA IDENTIFIER {
        $$ = $1;  // Copier la liste précédente
        $$.count++;  // Incrémenter le namebre d'éléments
        $$.variables = realloc($$.variables, sizeof(char*) * $$.count);
        $$.variables[$$.count - 1] = $3.name;  // Ajouter la nouvelle variable
    }
    | IDENTIFIER {
        $$.count = 1;  // Une seule variable
        $$.variables = malloc(sizeof(char*));
        $$.variables[0] = $1.name;
    }
    ;
affectation:
    IDENTIFIER ASSIGN expression SEMICOLON {
        // Vérification si la variable est déclarée
        TableEntry *varEntry = rechercher($1.name);
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
            generer("=",$3.name, "", varEntry->name);
        } else if (strcmp(varEntry->type, "FLOAT") == 0) {
            varEntry->val.fval = $3.value.fval;  // Affecter un flottant
            if(strcmp($3.type,"INTEGER") == 0){
                generer("=",$3.name, "", varEntry->name);
                varEntry->val.fval = (float) $3.value.ival;
            }
        } else if (strcmp(varEntry->type, "CHAR") == 0) {
       
            generer("=",$3.name, "", varEntry->name);
            varEntry->val.cval = $3.value.cval;  // Affecter un caractère
        } else {
            yyerror("Type inconnu pour l'affectation.4");
            return 0;
        } 
    
    }
;

expression:
    IDENTIFIER {  // Cas où l'expression est une variable
        TableEntry *entry = rechercher($1.name);
        if (entry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }

        $$.type = entry->type;

        // Affectation de la valeur en fonction du type de la variable
        if (strcmp(entry->type, "INTEGER") == 0) {
            $$.value.ival = entry->val.ival;
        } else if (strcmp(entry->type, "FLOAT") == 0) {
            $$.value.fval = entry->val.fval;
        } else if (strcmp(entry->type, "CHAR") == 0) {
            $$.value.cval = entry->val.cval;
        } else {
            yyerror("Type inconnu pour l'expression.");
            return 0;
        }
        $$.name=$1.name;
      
    }
    | NUMBERINT {  // Cas où l'expression est un entier
        $$.type = "INTEGER";
        $$.value.ival = $1;  // La valeur entière
        // Générer un quadruplet pour l'entier
        char val[20];
        sprintf(val, "%d", $1);
         $$.name=val;
          
      
         
    }
    | NUMBERFLOAT {  // Cas où l'expression est un flottant
        $$.type = "FLOAT";
        $$.value.fval = $1;  // La valeur flottante


        // Générer un quadruplet pour le flottant
       char val[20];
        sprintf(val, "%f", $1);  // Corrected format specifier
         $$.name=val;
        
    }
    | CARACTERE {  // Cas où l'expression est un caractère
        $$.type = "CHAR";
        $$.value.cval = $1;  // La valeur caractère
        // Générer un quadruplet pour le caractère
       char val[20];
        sprintf(val, "%c", $1);
         $$.name=val;

    }
    | expression PLUS expression {  // Addition
     if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
       $$.type = "INTEGER";
            $$.value.ival = $1.value.ival + $3.value.ival;

            // Générer un quadruplet pour l'addition
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("+", $1.name,$3.name, tempVar);
                $$.name=tempVar;
    } else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
          
        }
        if (strcmp($3.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
      
        }
        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval + $3.value.fval;
           // Générer un quadruplet pour l'addition flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("+",$1.name,$3.name, tempVar);
            $$.name=tempVar;
    } else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour l'addition.");
        return 0;
    }


    }
    | expression MINUS expression {  // Soustraction
        if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
       $$.type = "INTEGER";
            $$.value.ival = $1.value.ival - $3.value.ival;

            // Générer un quadruplet pour l'addition
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("-", $1.name,$3.name, tempVar);
                $$.name=tempVar;
    } else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($3.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
     //   printf("var1 :\n%f\n",$1.value.ival);
       // printf("var2 :\n%f\n",$3.value.ival);
        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval - $3.value.fval;
           // Générer un quadruplet pour l'addition flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("-",$1.name,$3.name, tempVar);
            $$.name=tempVar;
    } else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la soustraction.");
        return 0;
    }

    }
    | expression MULT expression {  // Multiplication
  
      
         if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
       $$.type = "INTEGER";
            $$.value.ival = $1.value.ival * $3.value.ival;

            // Générer un quadruplet pour l'addition
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("*", $1.name,$3.name, tempVar);
                $$.name=tempVar;
    } else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($3.type,"INTEGER")==0) {
            $3.type = "FLOAT";
          
            $3.value.fval = (float) $3.value.ival;
          
        }
           

        $$.type = "FLOAT";
        $$.value.fval = $1.value.fval * $3.value.fval;
           // Générer un quadruplet pour l'addition flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("*",$1.name,$3.name, tempVar);
            $$.name=tempVar;
    } else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la multiplication.");
        return 0;
    }

    }
    | expression DIV expression {  // Division

        if (strcmp($1.type,"INTEGER")==0 && strcmp($3.type,"INTEGER")==0) {
             $$.type = "INTEGER";
               if($3.value.fval==0){
              yyerror("division sur 0 impossible.");
                }else{  
             $$.value.ival = $1.value.ival/ $3.value.ival;

            // Générer un quadruplet pour l'addition
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("/", $1.name,$3.name, tempVar);
                $$.name=tempVar;
             }
           
    } else if (strcmp($1.type,"FLOAT")==0|| strcmp($3.type,"FLOAT")==0) {
        // Si l'un des opérandes est un FLOAT
        if (strcmp($1.type,"INTEGER")==0) {
            $1.type = "FLOAT";
            $1.value.fval = (float) $1.value.ival;
        }
        if (strcmp($3.type,"INTEGER")==0) {
            $3.type = "FLOAT";
            $3.value.fval = (float) $3.value.ival;
        }
        $$.type = "FLOAT";
          if($3.value.fval==0){
              yyerror("division sur 0 impossible.");
                }else{ 
        $$.value.fval = $1.value.fval / $3.value.fval;
           // Générer un quadruplet pour l'addition flottante
            char tempVar[20];
            sprintf(tempVar, "t%d", tempCount++);
            generer("/",$1.name,$3.name, tempVar);
            $$.name=tempVar;
                }
    } else {
        // Si les types sont incompatibles
        yyerror("Opérandes de types incompatibles pour la division.");
        return 0;
    }

    }
    | LPAREN expression RPAREN {  // Parenthèses pour prioriser les opérations
        $$.type = $2.type;
        $$.value = $2.value;
        $$.name=$2.name;
    }
    ;
type:
    INTEGER { $$ = "INTEGER"; }
    | FLOAT { $$ = "FLOAT"; }
    | CHAR { $$ = "CHAR"; }
    ;



statements:
    statement
    | statements statement
    ;

expressionslogic:
    expressionlogic
    | expressionslogic expressionlogic
;

ifstart:
     {
       

        char else_label[20], end_label[20];
        sprintf(else_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        push(&else_label_stack, else_label);
        push(&end_label_stack, end_label);


    }
;
ifcond:
    ifstart IF LPAREN expressionslogic RPAREN {
         if (strcmp($4.type, "BOOLEAN") != 0) {
            yyerror("La condition de l'instruction IF doit être de type BOOLEAN.");
            return 0;
        }
    };
;
ifstate:
    LBRACE statements RBRACE {
        char* current_else_label = top(else_label_stack);
        char* current_end_label = top(end_label_stack);

        generer("BR", current_end_label, "", "");
        generer("LABEL", current_else_label, "", "");
    }
;

forcond:
    FOR LPAREN init_for BOUCLESEPARATOR expression BOUCLESEPARATOR expression RPAREN {
        if (strcmp($5.type, "INTEGER") != 0 || strcmp($7.type, "INTEGER") != 0) {
            yyerror("Le pas de la boucle doit être un entier.");
            return 0;
        }

        // Générer des labels uniques
        char start_label[20],end_label[20];
        sprintf(start_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);

        // Empiler les labels
        push(&start_label_stack, start_label);
        push(&end_label_stack, end_label);

        generer("LABEL", start_label, "", "");
        char temp[20];
        sprintf(temp, "t%d", tempCount++);
        generer("-", $7.name, $3.name, temp); 
        generer("BPE", temp, "", end_label);
        generer("+", $3.name, $7.name, $3.name);
    }
;

statement:
    affectation
    | ifcond ifstate ELSE LBRACE statements RBRACE {
        char* current_end_label = pop(&end_label_stack);
        char* current_else_label = pop(&else_label_stack);

        generer("LABEL", current_end_label, "", "");

        // Libérer la mémoire
        free(current_else_label);
        free(current_end_label);
    }

    |forcond LBRACE statements RBRACE {
        char* current_start_label = pop(&start_label_stack);
        char* current_end_label = pop(&end_label_stack);
        generer("BR", current_start_label, "", "");
        generer("LABEL", current_end_label, "", "");
        free(current_start_label);
        free(current_end_label);
    }
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON {
        if (rechercher($3.name) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON
;

expressionlogic:
expression EQUAL expression{
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        char* current_else_label = top(else_label_stack);
        generer("BNE",current_else_label,$1.name,$3.name);


    }
    |
    LPAREN expressionlogic RPAREN {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.count = $2.count;
        $$.value=$2.value;
    }
    | expression LT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        char* current_else_label = top(else_label_stack);
        generer("BGE",current_else_label,$1.name,$3.name);
        }
    
    
    | expression LTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        char* current_else_label = top(else_label_stack);
        generer("BG",current_else_label,$1.name,$3.name);

    }
    
    | expression GT expression
    {  if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        char* current_else_label = top(else_label_stack);
        generer("BLE",current_else_label,$1.name,$3.name);
    
    }
    | expression GTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        char* current_else_label = top(else_label_stack);
        generer("BL",current_else_label,$1.name,$3.name);


    }
    
    | expressionlogic AND expressionlogic {
        // Vérification que les opérandes sont du type booléen
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique AND.");
            return 0;
        }

        // Résultat de l'opération logique AND est de type booléen
        $$.type = "BOOLEAN";

        // Création des labels pour gérer les sauts conditionnels
        char* current_else_label = malloc(20);
        char* current_end_label = malloc(20);
        sprintf(current_else_label, "L%d", tempCount++);
        sprintf(current_end_label, "L%d", tempCount++);

        // Génération des instructions pour le test logique
        generer("JZ", $1.name, "", current_else_label);  // Si $1 est false, sauter à current_else_label
        generer("JZ", $3.name, "", current_else_label);  // Si $3 est false, sauter à current_else_label

        // Si les deux opérandes sont vrais, on continue l'exécution normale
        generer("BR", current_end_label, "", "");  // Sauter à current_end_label à la fin

        // Générer le label pour l'instruction ELSE
        generer("LABEL", current_else_label, "", "");
        generer("FALSE", "", "", "");  // Pour indiquer que l'opération a échoué

        // Générer le label de fin
        generer("LABEL", current_end_label, "", "");

        // Libérer la mémoire des labels
        free(current_else_label);
        free(current_end_label);
    }
;
    |   expressionlogic  OR  expressionlogic {
        // Vérifier que les deux opérandes sont du type booléen
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique OR.");
            return 0;
        }
        $$.type = "BOOLEAN"; // Le résultat est de type booléen

        // Créer des labels pour gérer le flux d'exécution
        char* current_end_label = malloc(20);
        sprintf(current_end_label, "L%d", tempCount++);

        // Si l'un des opérandes est vrai, sauter au label de fin
        generer("JNZ", $1.name, "", current_end_label);  // Si $1 est vrai, sauter
        generer("JNZ", $3.name, "", current_end_label);  // Si $3 est vrai, sauter

        // Si aucune des expressions n'est vraie, on considère que l'OR est faux
        generer("FALSE", "", "", "");  // Sinon, FALSE

        // Générer le label de fin
        generer("LABEL", current_end_label, "", "");

        // Libérer la mémoire allouée pour le label de fin
        free(current_end_label);
    }
;expressionlogic:
    NOT expressionlogic {
        // Vérifier que l'opérande est de type booléen
        if (strcmp($2.type, "BOOLEAN") != 0) {
            yyerror("L'opérande de NOT doit être de type BOOLEAN.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat est de type booléen

        // Créer un label pour gérer le flux d'exécution
        char* current_end_label = malloc(20);
        sprintf(current_end_label, "L%d", tempCount++);

        // Si l'opérande est faux, le résultat sera vrai
        generer("JZ", $2.name, "", current_end_label);  // Si $2 est faux, sauter

        // Sinon, le résultat sera faux
        generer("TRUE", "", "", "");

        // Générer le label de fin
        generer("LABEL", current_end_label, "", "");

        // Libérer la mémoire allouée pour le label de fin
        free(current_end_label);
    }
;

;

init_for:
    IDENTIFIER ASSIGN expression {
        TableEntry *varEntry = rechercher($1.name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        $$ = $3;  // Pass the expression value up
        $$.name=$1.name;
    }
    ;


expressionwrite:
    IDENTIFIER {
        TableEntry *varEntry = rechercher($1.name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
    | TEXT
    | TEXT COMMA expressionwrite
    | IDENTIFIER COMMA expressionwrite {
        TableEntry *varEntry = rechercher($1.name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
;

NUMBERINT:
    NUMBERINTPOS
    | NUMBERINTNEG
;

NUMBERFLOAT:
    NUMBERFLOATNEG
    | NUMBERFLOATPOS
;

%%

void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Erreur à la ligne %d: %s\n", yylineno, s);
}