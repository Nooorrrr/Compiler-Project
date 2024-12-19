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
    VAR_GLOBAL = 258,              /* VAR_GLOBAL  */
    LBRACE = 259,                  /* LBRACE  */
    RBRACE = 260,                  /* RBRACE  */
    DECLARATION = 261,             /* DECLARATION  */
    INSTRUCTION = 262,             /* INSTRUCTION  */
    SEMICOLON = 263,               /* SEMICOLON  */
    CONST = 264,                   /* CONST  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    FOR = 267,                     /* FOR  */
    READ = 268,                    /* READ  */
    WRITE = 269,                   /* WRITE  */
    IDENTIFIER = 270,              /* IDENTIFIER  */
    NUMBERINTPOS = 271,            /* NUMBERINTPOS  */
    NUMBERINTNEG = 272,            /* NUMBERINTNEG  */
    NUMBERFLOATPOS = 273,          /* NUMBERFLOATPOS  */
    NUMBERFLOATNEG = 274,          /* NUMBERFLOATNEG  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    NOT = 277,                     /* NOT  */
    EQUAL = 278,                   /* EQUAL  */
    NEQ = 279,                     /* NEQ  */
    GTE = 280,                     /* GTE  */
    LTE = 281,                     /* LTE  */
    GT = 282,                      /* GT  */
    LT = 283,                      /* LT  */
    LBRACE = 284,                  /* LBRACE  */
    RBRACE = 285,                  /* RBRACE  */
    LPAREN = 286,                  /* LPAREN  */
    RPAREN = 287,                  /* RPAREN  */
    LBRACKET = 288,                /* LBRACKET  */
    RBRACKET = 289,                /* RBRACKET  */
    SEMICOLON = 290,               /* SEMICOLON  */
    COMMA = 291,                   /* COMMA  */
    ASSIGN = 292,                  /* ASSIGN  */
    QUOTE = 293,                   /* QUOTE  */
    COLON = 294,                   /* COLON  */
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
#line 30 "parser.y"

    int intValue;
    float floatValue;
    char charValue;
    char* stringValue;
    struct {
        char* type;
        Value value;
    } expressionValue;
    IdentifierList identList;

#line 101 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
