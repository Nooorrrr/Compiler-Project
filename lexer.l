%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h" 
%}

%option noyywrap

%%

"VAR_GLOBAL"         { return VAR_GLOBAL; }
"DECLARATION"        { return DECLARATION; }
"INSTRUCTION"        { return INSTRUCTION; }
"INTEGER"            { return INTEGER; }
"FLOAT"              { return FLOAT; }
"CHAR"               { return CHAR; }
"CONST"              { return CONST; }
"IF"                 { return IF; }
"ELSE"               { return ELSE; }
"FOR"                { return FOR; }
"READ"               { return READ; }
"WRITE"              { return WRITE; }

"%%"[^\n]*           { /* Commentaire, on ignore */ }

[A-Z][a-z0-9]{0,7}   { return IDENTIFIER; }

[+-]?[0-9]+              { return NUMBER; }
[+-]?[0-9]+\.[0-9]+      { return NUMBER; }
"&&"                 { return AND; }
"\|\|"               { return OR; }
"!"                  { return NOT; }
"=="                 { return EQUAL; }
"!="                 { return NEQ; }
">="                 { return GTE; }
"<="                 { return LTE; }
">"                  { return GT; }
"<"                  { return LT; }

"+"                   { return PLUS; }   
"-"                   { return MINUS; } 
"*"                   { return MULT; }   
"/"                   { return DIV; }    

"{"                  { return LBRACE; }
"}"                  { return RBRACE; }
"("                  { return LPAREN; }
")"                  { return RPAREN; }
"["                  { return LBRACKET; }
"]"                  { return RBRACKET; }
";"                  { return SEMICOLON; }
","                  { return COMMA; }
"="                  { return ASSIGN; }

[ \t]                { /* Ignorer les espaces et les tabulations */ }
[\n]                 { yylineno++; }
.                    { printf("Erreur lexical à la ligne %d: Caractère inattendu: %s\n", yylineno, yytext); exit(1); }

%%

