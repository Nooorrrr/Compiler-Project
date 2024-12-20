#include "ts.h"

// Déclaration de la table des symboles
TableEntry Tab[1000];  // Table des IDF et CONST

// Initialisation de la table des symboles
void initialiserTable(TableEntry *table, int taille) {
    for (int i = 0; i < taille; i++) {
        table[i].state = 0;      // Libre
        strcpy(table[i].name, "");
        strcpy(table[i].type, "");
        table[i].val.ival = 0;   // Initialiser à zéro
        table[i].scope = 0;
        table[i].offset = -1;
        table[i].isArray = 0;
        table[i].arraySize = 0;
        table[i].isConst = 0;
        table[i].next = NULL;
    }
}

// Initialisation générale de la table
void initialisation() {
    initialiserTable(Tab, 1000);
}

// Recherche dans la table des symboles
TableEntry* rechercher(const char entite[]) {
    for (int i = 0; i < 1000; i++) {
        if (Tab[i].state == 1 && strcmp(Tab[i].name, entite) == 0) {
            return &Tab[i];
        }
    }
    return NULL;
}
// Insertion d'une nouvelle entrée dans la table
void inserer(const char entite[], const char type[], float val, int scope, int isArray, int arraySize, int isConst) {
    for (int i = 0; i < 1000; i++) {
        if (Tab[i].state == 0) { 
            Tab[i].state = 1; 
            strcpy(Tab[i].name, entite);
            strcpy(Tab[i].type, type);
            
            // Modifiez cette ligne pour affecter un float à la valeur
            if (strcmp(type, "INTEGER") == 0) {
                Tab[i].val.ival = (int)val;  // Assurez-vous de convertir float en int si nécessaire
            } else if (strcmp(type, "FLOAT") == 0) {
                Tab[i].val.fval = (float)val;  // Affectation directe si c'est un float
            } else if (strcmp(type, "CHAR") == 0) {
                Tab[i].val.cval = (char)val;  // Conversion si c'est un char
            }
            
            Tab[i].scope = scope;
            Tab[i].isArray = isArray;
            Tab[i].arraySize = arraySize;
            Tab[i].isConst = isConst;
            Tab[i].offset = -1;
            Tab[i].next = NULL;
            return;
        }
    }
    fprintf(stderr, "Erreur : table pleine, impossible d'insérer %s\n", entite);
}


// Affichage de l'en-tête de la table
void afficherEnTete() {
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
    printf("| Nom             | Type       | Valeur   | Portée| Tableau| Taille| Const |\n");
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
}
// Affichage d'une entrée de la table
void afficherEntree(TableEntry *entry) {
    if (strcmp(entry->type, "INTEGER") == 0) {
        printf("| %-15s | %-10s | %-8d | %-5d | %-5d | %-5d | %-5d |\n", 
               entry->name, entry->type, entry->val.ival, entry->scope,
               entry->isArray, entry->arraySize, entry->isConst);
    } else if (strcmp(entry->type, "FLOAT") == 0) {
        printf("| %-15s | %-10s | %-8.2f | %-5d | %-5d | %-5d | %-5d |\n", 
               entry->name, entry->type, entry->val.fval, entry->scope,
               entry->isArray, entry->arraySize, entry->isConst);
    } else if (strcmp(entry->type, "CHAR") == 0) {
        printf("| %-15s | %-10s | %-8c | %-5d | %-5d | %-5d | %-5d |\n", 
               entry->name, entry->type, entry->val.cval, entry->scope,
               entry->isArray, entry->arraySize, entry->isConst);
    } else {
        // Ajoutez un message de debug si le type est inconnu
        printf("Type inconnu: %s\n", entry->type);
    }
}

// Affichage de la table des symboles
void afficherTable(TableEntry *table, int taille) {
    afficherEnTete();
    for (int i = 0; i < taille; i++) {
        if (table[i].state == 1) {  // Vérifie si l'entrée est valide
            afficherEntree(&table[i]);
        }
    }
    printf("+-----------------+------------+----------+-------+-------+-------+-------+\n");
}

// Modification de la valeur d'une entrée dans la table des symboles
void modifierValeur(const char idf[], void *newValue, const char *type) {
    TableEntry *entry = rechercher(idf);  // Search for the identifier in the symbol table

    if (entry != NULL) {
        if (entry->isConst) {
            fprintf(stderr, "Erreur : impossible de modifier la valeur de %s car il s'agit d'une constante.\n", idf);
            return;  // Do not modify if the variable is constant
        }

        // Modify the value based on the type
        if (strcmp(type, "INTEGER") == 0) {
            entry->val.ival = *(int *)newValue;
            printf("La valeur de %s a été modifiée avec succès. Nouvelle valeur : %d\n", idf, entry->val.ival);
        } 
        else if (strcmp(type, "FLOAT") == 0) {
            entry->val.fval = *(float *)newValue;
            printf("La valeur de %s a été modifiée avec succès. Nouvelle valeur : %.2f\n", idf, entry->val.fval);
        }
        else if (strcmp(type, "CHAR") == 0) {
            entry->val.cval = *(char *)newValue;
            printf("La valeur de %s a été modifiée avec succès. Nouvelle valeur : %c\n", idf, entry->val.cval);
        }
        else {
            fprintf(stderr, "Erreur : type de donnée inconnu %s pour %s.\n", type, idf);
        }
    } else {
        fprintf(stderr, "Erreur : l'identifiant %s n'existe pas dans la table des symboles.\n", idf);
    }
}
