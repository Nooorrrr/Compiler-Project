#include "ts.h"

// Déclaration des tables
TableEntry Tab[1000];    // Table des IDF et CONST

void initialiserTable(TableEntry *table, int taille) {
    for (int i = 0; i < taille; i++) {
        table[i].state = 0;        // Libre
        strcpy(table[i].name, "");
        strcpy(table[i].type, "");
        table[i].val = 0.0;
        table[i].scope = 0;
        table[i].offset = -1;
        table[i].isArray = 0;      
        table[i].arraySize = 0;    
        table[i].isConst = 0;      
        table[i].next = NULL;
    }
}

void initialisation() {
    initialiserTable(Tab, 1000);  
}


// Fonction de recherche dans les tables
TableEntry* rechercher(const char entite[]) {
    TableEntry *table = NULL;
    int taille;
    table = Tab;
    taille = 1000;
  
    for (int i = 0; i < taille; i++) {
        if (table[i].state == 1 && strcmp(table[i].name, entite) == 0) {
            return &table[i];  // Retourner le pointeur vers l'entrée trouvée
        }
    }
    return NULL; 
}

// Fonction d'insertion dans les tables
void inserer(const char entite[], const char type[], float val, int scope, int isArray, int arraySize, int isConst) {
    TableEntry *table = NULL;
    int taille;
    table = Tab;
    taille = 1000;
 

    for (int i = 0; i < taille; i++) {
        if (table[i].state == 0) { 
            table[i].state = 1; 
            strcpy(table[i].name, entite);
            strcpy(table[i].type, type);
            table[i].val = val;
            table[i].scope = scope;   
            table[i].isArray = isArray;
            table[i].arraySize = arraySize;
            table[i].isConst = isConst;
            table[i].offset = -1; 
            table[i].next = NULL; 
            return; 
        }
    }
   fprintf(stderr, "Erreur : table pleine, impossible d'insérer %s\n", entite);
}


void afficherEntree(TableEntry *entry) {
    printf("| %-15s | %-10s | %-8.2f | %-5d | %-5d | %-5d | %-5d |\n",
           entry->name, entry->type, entry->val, entry->scope,
           entry->isArray, entry->arraySize, entry->isConst);
}

// Fonction pour afficher l'en-tête de la table
void afficherEnTete() {
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
    printf("| Nom             | Type       | Valeur   | Portée| Tableau| Taille| Const |\n");
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
}

// Fonction pour afficher toute la table des symboles
void afficherTable(TableEntry *table, int taille) {
    afficherEnTete();
    for (int i = 0; i < taille; i++) {
        if (table[i].state == 1) { // Si l'entrée est occupée
            afficherEntree(&table[i]);
        }
    }
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
}

/* Fonction main pour tester
int main() {
    // Initialisation de la table des symboles
    initialisation();

    // Insérer des entités de test dans la table des symboles
    inserer("x", "int", 10.0, 0, 0, 0, 0);
    inserer("y", "float", 20.5, 1, 0, 0, 0);
    inserer("arr", "int", 0.0, 2, 1, 10, 0); // Tableau de taille 10

    // Afficher la table des symboles
    afficherTable(Tab, 1000);

    return 0;
}*/