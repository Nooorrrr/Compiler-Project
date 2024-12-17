#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Union pour gérer différents types de valeurs
typedef union {
    float floatValue;   // Valeur flottante
    int intValue;       // Valeur entière
    char charValue;     // Valeur caractère
} Value;

// Structure représentant une entrée dans la table des symboles
typedef struct {
    char name[9];        // Nom de la variable (8 caractères max + '\0')
    char type[10];       // Type : INTEGER, FLOAT, CHAR
    int isConst;         // 1 si c'est une constante, 0 sinon
    int arraySize;       // Taille si c'est un tableau (0 si ce n'est pas un tableau)
    Value value;         // Valeur si ce n'est pas un tableau
    Value *arrayValues;  // Tableau de valeurs pour les tableaux
} TableEntry;

// Déclaration de la taille de la table des symboles
#define TABLE_SIZE 1000

// Déclaration de la table des symboles
extern TableEntry Tab[TABLE_SIZE];

// Fonction d'initialisation de la table des symboles
void initialiserTable(TableEntry table[], int taille);

// Fonction d'insertion dans la table des symboles
void inserer(TableEntry table[], const char entite[], const char type[], Value val, int arraySize, int isConst);

// Fonction pour insérer une valeur dans un tableau déjà existant
void insererValeurTableau(TableEntry *entry, int index, Value val);

// Fonction de recherche dans la table des symboles
TableEntry* rechercher(TableEntry table[], const char entite[]);
void modifierVariable(char *nomVariable, Value nouvelleValeur);
void modifierValeurTableau(char *nomTableau, int index, Value nouvelleValeur);

// Fonction pour vérifier si la table est pleine
int estPleine(TableEntry table[]);

#endif // TS_H
