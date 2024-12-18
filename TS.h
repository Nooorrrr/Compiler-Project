#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

// Ensure only one declaration of Value
typedef union {
    float floatValue;
    int intValue;
    char charValue;
} Value;

// Ensure TableEntry is declared before use
typedef struct {
    char name[9];
    char type[10];
    int isConst;
    int arraySize;
    Value value;
    Value *arrayValues;
} TableEntry;

void inserer(TableEntry table[], const char entite[], const char type[], Value val, int arraySize, int isConst);
void insererValeurTableau(TableEntry *entry, int index, Value value);
void modifierVariable(char *nomVariable, Value nouvelleValeur);
void modifierValeurTableau(char *nomTableau, int index, Value nouvelleValeur);

#endif // TS_H