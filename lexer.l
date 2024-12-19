%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"  
%}

%option header-file="lex.yy.h"

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

"%%"[^\n]*           { /* Ignore comments */ }

[A-Z][a-z0-9]{0,7}   { return IDENTIFIER; } 

[+]?[0-9]+           { return NUMBERINTPOS; }  
[+]?[0-9]+\.[0-9]+   { return NUMBERFLOATPOS; }  
"-"[0-9]+            { return NUMBERINTNEG; }  
"-"[0-9]+\.[0-9]+    { return NUMBERFLOATNEG; }

"&&"                 { return AND; }
"\|\|"               { return OR; }
"!"                  { return NOT; }
"=="                 { return EQUAL; }
"!="                 { return NEQ; }
">="                 { return GTE; }
"<="                 { return LTE; }
">"                  { return GT; }
"<"                  { return LT; }
"\""                   { return QUOTE; }   // Règle pour le guillemet

"+"                  { return PLUS; }
"-"                  { return MINUS; }
"*"                  { return MULT; }
"/"                  { return DIV; }

"{"                  { return LBRACE; }
"}"                  { return RBRACE; }
"("                  { return LPAREN; }
")"                  { return RPAREN; }
"["                  { return LBRACKET; }
"]"                  { return RBRACKET; }
";"                  { return SEMICOLON; }
"\:"                 { return COLON; }
","                  { return COMMA; }
"="                  { return ASSIGN; }
\"[^\n\t]*\"  { return TEXT; }

[ \t]                { /* Ignore spaces and tabs */ }
[\n]                 { yylineno++; } 
.                    { printf("Erreur lexical à la ligne %d: entité inconnue: %s\n", yylineno, yytext); exit(1); }  // Handle unknown characters

%%


