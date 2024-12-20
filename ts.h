#ifndef ts_H
#define ts_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Structure représentant une entrée dans la table des symboles
typedef struct {
    int state;          
    char name[50];      
    char type[50];      
    float val;          
    int scope;   
    int isArray;           
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
void modifierValeur(const char idf[], float newValue) ;
void afficherEnTete();
void afficherEntree(TableEntry *entry);
void afficherTable(TableEntry *table, int taille);
#endif