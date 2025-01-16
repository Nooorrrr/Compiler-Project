/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBERINTPOS = 258,            /* NUMBERINTPOS  */
    NUMBERINTNEG = 259,            /* NUMBERINTNEG  */
    NUMBERFLOATPOS = 260,          /* NUMBERFLOATPOS  */
    NUMBERFLOATNEG = 261,          /* NUMBERFLOATNEG  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    CARACTERE = 263,               /* CARACTERE  */
    VAR_GLOBAL = 264,              /* VAR_GLOBAL  */
    DECLARATION = 265,             /* DECLARATION  */
    INSTRUCTION = 266,             /* INSTRUCTION  */
    INTEGER = 267,                 /* INTEGER  */
    FLOAT = 268,                   /* FLOAT  */
    CHAR = 269,                    /* CHAR  */
    CONST = 270,                   /* CONST  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    FOR = 273,                     /* FOR  */
    READ = 274,                    /* READ  */
    WRITE = 275,                   /* WRITE  */
    AND = 276,                     /* AND  */
    OR = 277,                      /* OR  */
    NOT = 278,                     /* NOT  */
    EQUAL = 279,                   /* EQUAL  */
    NEQ = 280,                     /* NEQ  */
    GTE = 281,                     /* GTE  */
    LTE = 282,                     /* LTE  */
    GT = 283,                      /* GT  */
    LT = 284,                      /* LT  */
    LBRACE = 285,                  /* LBRACE  */
    RBRACE = 286,                  /* RBRACE  */
    LPAREN = 287,                  /* LPAREN  */
    RPAREN = 288,                  /* RPAREN  */
    LBRACKET = 289,                /* LBRACKET  */
    RBRACKET = 290,                /* RBRACKET  */
    SEMICOLON = 291,               /* SEMICOLON  */
    COMMA = 292,                   /* COMMA  */
    ASSIGN = 293,                  /* ASSIGN  */
    BOUCLESEPARATOR = 294,         /* BOUCLESEPARATOR  */
    PLUS = 295,                    /* PLUS  */
    MINUS = 296,                   /* MINUS  */
    MULT = 297,                    /* MULT  */
    DIV = 298,                     /* DIV  */
    TEXT = 299                     /* TEXT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 54 "parser.y"

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

#line 151 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
