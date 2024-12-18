#include "TS.h"



// Definition of the Value type
typedef union {
    int intValue;
    float floatValue;
    char charValue;
} Value;

// Definition of the TableEntry type
typedef struct {
    char name[9];
    char type[10];
    int isConst;
    int arraySize;
    Value value;
    Value *arrayValues;
} TableEntry;

// Declaration of the symbol table
TableEntry Tab[TABLE_SIZE];  // Table of identifiers and constants

void initialiserTable(TableEntry table[], int taille) {
    for (int i = 0; i < taille; i++) {
        table[i].name[0] = '\0';
        table[i].type[0] = '\0';
        table[i].isConst = 0;
        table[i].value.intValue = 0;  // Initialize value with 0
        table[i].arraySize = 0;
        table[i].arrayValues = NULL;
    }
}

// Function to search in the symbol table
TableEntry* rechercher(TableEntry table[], const char entite[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(table[i].name, entite) == 0) {
            return &table[i];  // Return pointer to the found entry
        }
    }
    return NULL;  // Return NULL if the entity was not found
}

// Function to insert into the symbol table
void inserer(TableEntry table[], const char entite[], const char type[], Value val, int arraySize, int isConst) {
    if (estPleine(table)) {
        printf("Erreur : Table des symboles pleine.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].name[0] == '\0') {  // Find an empty slot
            strncpy(table[i].name, entite, sizeof(table[i].name) - 1);
            strncpy(table[i].type, type, sizeof(table[i].type) - 1);
            table[i].isConst = isConst;
            table[i].arraySize = arraySize;
            table[i].value = val;
            if (arraySize > 0) {
                table[i].arrayValues = (Value *)malloc(arraySize * sizeof(Value));
            }
            return;
        }
    }
}

// Function to check if the table is full
int estPleine(TableEntry table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].name[0] == '\0') {
            return 0;  // Table is not full
        }
    }
    return 1;  // Table is full
}

// Function to insert a value into an array in the symbol table
void insererValeurTableau(TableEntry *entry, int index, Value value) {
    if (index >= 0 && index < entry->arraySize) {
        entry->arrayValues[index] = value;
    } else {
        printf("Erreur : Index hors limites.\n");
    }
}

// Function to modify a variable in the symbol table
void modifierVariable(char *nomVariable, Value nouvelleValeur) {
    TableEntry *entry = rechercher(Tab, nomVariable);
    if (entry != NULL) {
        entry->value = nouvelleValeur;
    } else {
        printf("Erreur : Variable non trouvée.\n");
    }
}

// Function to modify a value in an array in the symbol table
void modifierValeurTableau(char *nomTableau, int index, Value nouvelleValeur) {
    TableEntry *entry = rechercher(Tab, nomTableau);
    if (entry != NULL) {
        insererValeurTableau(entry, index, nouvelleValeur);
    } else {
        printf("Erreur : Tableau non trouvé.\n");
    }
}