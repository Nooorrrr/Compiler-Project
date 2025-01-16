%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h" 
%}

%option noyywrap
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

"%%"[^\n]*           {  }

[A-Z][a-z0-9]{0,7}   { yylval.chaine = strdup(yytext);return IDENTIFIER; }
\'[a-zA-Z]\' {
    yylval.car = yytext[1]; // Le caractère encapsulé (sans les guillemets simples)
    return CARACTERE;
}
\"[a-zA-Z]\" {
    yylval.car = yytext[1]; // Le caractère encapsulé (sans les guillemets simples)
    return CARACTERE;
}
[+]?[0-9]+\.[0-9]+      { yylval.flottant = strtod(yytext, NULL); return NUMBERFLOATPOS; }
"-"[0-9]+\.[0-9]+      { yylval.flottant = strtod(yytext, NULL); return NUMBERFLOATNEG; }
[+]?[0-9]+              { yylval.entier = atoi(yytext); return NUMBERINTPOS; }
"-"[0-9]+              { yylval.entier = atoi(yytext); return NUMBERINTNEG; }


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
":"                   { return BOUCLESEPARATOR; } 

"{"                  { return LBRACE; }
"}"                  { return RBRACE; }
"("                  { return LPAREN; }
")"                  { return RPAREN; }
"["                  { return LBRACKET; }
"]"                  { return RBRACKET; }
";"                  { return SEMICOLON; }

","                  { return COMMA; }
"="                  { return ASSIGN; }
\"[^\n\t\"]*\"  { return TEXT; }

[ \t]                { /* Ignorer les espaces et les tabulations */ }
[\n]                 { yylineno++; }
.                    { printf("Erreur lexical à la ligne %d: entite inconnu: %s\n", yylineno, yytext); exit(1); }

%%