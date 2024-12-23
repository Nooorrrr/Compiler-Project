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
        char** variables; 
        int count; 
        int value;
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
        printf("var1 :\n%f\n",$1.value.ival);
           printf("var2 :\n%f\n",$3.value.ival);
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

statement:
    affectation
    | IF LPAREN expressionslogic RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
        // Vérifier que la condition dans IF est de type booléen

        if (strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("La condition de l'instruction IF doit être de type BOOLEAN.");
            return 0;
        }
    // Generate unique labels for jumps
    char* else_label = malloc(20);
    char* end_label = malloc(20);
    sprintf(else_label, "L%d", tempCount++);
    sprintf(end_label, "L%d", tempCount++);
    
    // If expression is false (0), jump to else
    generer("BZ", $3.name, "", else_label);
    
    // If-block code was already generated in statements
    
    // Jump to end after if block
    generer("BR", end_label, "", "");
    
    // Place else label
    generer("LABEL", else_label, "", "");
    
    // Else-block code was already generated in statements
    
    // Place end label
    generer("LABEL", end_label, "", "");
    
    free(else_label);
    free(end_label);

    }
    | FOR LPAREN init_for BOUCLESEPARATOR expression BOUCLESEPARATOR expression RPAREN LBRACE statements RBRACE {
      if (strcmp($5.type, "INTEGER") != 0||strcmp($7.type, "INTEGER") != 0) {
        yyerror("Le pas de la boucle doit être un entier.");
        return 0;
    }

    // Generate unique labels
    char* start_label = malloc(20);
    char* end_label = malloc(20);
    sprintf(start_label, "L%d", tempCount++);
    sprintf(end_label, "L%d", tempCount++);
    
    // Place start label
    generer("LABEL", start_label, "", "");
    
    // Generate comparison result
    char* temp = malloc(20);
    sprintf(temp, "t%d", tempCount++);
    generer("-", $3.name, $5.name, temp);  // temp = counter - limit
    
    // If temp >= 0 (counter >= limit), exit loop
    generer("BGE", temp, "", end_label);
    
    // Loop body code was already generated in statements
    
    // Increment counter
    generer("+", $3.name, $7.name, $3.name);
    
    // Jump back to start
    generer("BR", start_label, "", "");
    
    // Place end label
    generer("LABEL", end_label, "", "");
    
    free(start_label);
    free(end_label);
    free(temp);
    }
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON {
        if (rechercher($3.name) == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
    }
    | WRITE LPAREN expressionwrite RPAREN SEMICOLON {
        // Vérification que l'expression à écrire est valide
    }
;

expressionlogic:

expression EQUAL expression{
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // Compare values
        generer("-", $1.name, $3.name, temp);
        
        // If difference is 0, values are equal
        generer("BZ", temp, "", true_label);
        generer("=", "0", "", temp);  // Set result to false
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);  // Set result to true
        generer("LABEL", end_label, "", "");
        
        $$.name = temp;
        free(true_label);
        free(end_label);

        if(strcmp($1.type,"INTEGER")==0){
             if($1.value.ival==$3.value.ival){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"FLOAT")==0){
             if($1.value.fval==$3.value.fval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"CHAR")==0){
             if($1.value.cval==$3.value.cval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
    
    }
    |
    LPAREN expressionlogic RPAREN {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.variables = $2.variables;
        $$.count = $2.count;
        $$.value=$2.value;
    }
    | expression LT expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp($1.type,"INTEGER")==0){
             if($1.value.ival<$3.value.ival){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"FLOAT")==0){
             if($1.value.fval<$3.value.fval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"CHAR")==0){
             if($1.value.cval<$3.value.cval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }}
    
    | expression LTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // Compare values
        generer("-", $1.name, $3.name, temp);
        
        // If difference is negative, first value is less
        generer("BL", temp, "", true_label);
        generer("=", "0", "", temp);  // Set result to false
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);  // Set result to true
        generer("LABEL", end_label, "", "");
        
        $$.name = temp;
        free(true_label);
        free(end_label);

        if(strcmp($1.type,"INTEGER")==0){
             if($1.value.ival<=$3.value.ival){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"FLOAT")==0){
             if($1.value.fval<=$3.value.fval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"CHAR")==0){
             if($1.value.cval<=$3.value.cval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
    }
    
    | expression GT expression
    {  if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp($1.type,"INTEGER")==0){
             if($1.value.ival>$3.value.ival){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"FLOAT")==0){
             if($1.value.fval>$3.value.fval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"CHAR")==0){
             if($1.value.cval>$3.value.cval){
              $$.value=1;
        }else{
            $$.value=0;
        }
          }
    }
    | expression GTE expression {
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
        if(strcmp($1.type,"INTEGER")==0){
             if($1.value.ival>=$3.value.ival){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"FLOAT")==0){
             if($1.value.fval>=$3.value.fval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
          if(strcmp($1.type,"CHAR")==0){
             if($1.value.cval>=$3.value.cval){
              $$.value=1;
        }else{
            $$.value=0;
        }
        }
    }
    
    |expressionlogic AND expressionlogic {
        // Vérification que les deux opérandes sont booléens
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique AND.");
            return 0;
        }
        $$.type = "BOOLEAN";
        char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* false_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(false_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If first expression is false, result is false
        generer("BZ", $1.name, "", false_label);
        // If second expression is false, result is false
        generer("BZ", $3.name, "", false_label);
        // Both true, set result to true
        generer("=", "1", "", temp);
        generer("BR", end_label, "", "");
        // False case
        generer("LABEL", false_label, "", "");
        generer("=", "0", "", temp);
        generer("LABEL", end_label, "", "");
        
        $$.name = temp;
        free(false_label);
        free(end_label);

            if($1.value&&$3.value){
              $$.value=1;
        }else{
            $$.value=0;
        }
    }
    | expressionlogic OR expressionlogic {
        if (strcmp($1.type, "BOOLEAN") != 0 || strcmp($3.type, "BOOLEAN") != 0) {
            yyerror("Opérandes incompatibles pour l'opérateur logique OR.");
            return 0;
        }
        $$.type = "BOOLEAN";

         char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If first expression is true, result is true
        generer("BNZ", $1.name, "", true_label);
        // If second expression is true, result is true
        generer("BNZ", $3.name, "", true_label);
        // Both false, set result to false
        generer("=", "0", "", temp);
        generer("BR", end_label, "", "");
        // True case
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);
        generer("LABEL", end_label, "", "");
        
        $$.name = temp;
        free(true_label);
        free(end_label);

          if($1.value||$3.value){
              $$.value=1;
        }else{
            $$.value=0;
        }
    }
    | NOT expressionlogic {
        if (strcmp($2.type, "BOOLEAN") != 0) {
            yyerror("L'opérande de NOT doit être de type BOOLEAN.");
            return 0;
        }
        $$.type = "BOOLEAN";
        char* temp = malloc(20);
        sprintf(temp, "t%d", tempCount++);
        char* true_label = malloc(20);
        char* end_label = malloc(20);
        sprintf(true_label, "L%d", tempCount++);
        sprintf(end_label, "L%d", tempCount++);
        
        // If expression is false, result is true
        generer("BZ", $2.name, "", true_label);
        generer("=", "0", "", temp);
        generer("BR", end_label, "", "");
        generer("LABEL", true_label, "", "");
        generer("=", "1", "", temp);
        generer("LABEL", end_label, "", "");
        
        $$.name = temp;
        free(true_label);
        free(end_label);
          if(!$2.value){
              $$.value=1;
        }else{
            $$.value=0;
        }
    }
;

init_for:
    IDENTIFIER ASSIGN expression {
        TableEntry *varEntry = rechercher($1.name);
        if (varEntry == NULL) {
            yyerror("Variable non déclarée.");
            return 0;
        }
        $$ = $3;  // Pass the expression value up
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
}/*
expressionlogic:

expression EQUAL expression{
        if (strcmp($1.type, $3.type) != 0) {
            yyerror("Opérandes de types incompatibles pour l'opération de comparaison.");
            return 0;
        }
        $$.type = "BOOLEAN";  // Le résultat de la comparaison est de type booléen
    }
    |
    LPAREN expressionlogic RPAREN {
        // Copier le contenu de la sous-expression dans l'expression actuelle
        $$.type = $2.type;
        $$.variables = $2.variables;
        $$.count = $2.count;
    }
    | expression LT expression {
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
    | expressionlogic OPERA expressionlogic {
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
;*/