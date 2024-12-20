#ifndef ts_H
#define ts_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef union {
    char cval;
    int ival;
    float fval;
} Value;



typedef union {
    int *iArray;    // Tableau d'entiers
    float *fArray;  // Tableau de flottants
    char *cArray;   // Tableau de caractères
} ArrayValue;

// Structure représentant une entrée dans la table des symboles
// Dans ts.h
typedef struct {
    int state;
    char name[50];
    char type[50];  // Utilisez un tableau de caractères au lieu d'un enum
    int scope;
    int isArray;
    ArrayValue val;     // Pointeur vers les valeurs du tableau
    int arraySize;
    int isConst;
    struct TableEntry *next;
    int offset;
} TableEntry;

// Déclarations des tables
extern TableEntry Tab[1000];  // Table des identifiants et constantes


void initialisation();
TableEntry* rechercher(const char entite[]);
void inserer(const char entite[], const char type[], float val, int scope, int isArray, int arraySize, int isConst);
void modifierValeur(const char idf[], void *newValue, const char *type);
void modifierValeurTableau(const char idf[], int index, void *newValue, const char *type);
void afficherEnTete();
void afficherEntree(TableEntry *entry);
void afficherTable(TableEntry *table, int taille);
#endif