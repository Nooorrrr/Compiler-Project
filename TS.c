#include "TS.h"

// Définition du type Value (à adapter selon les types que tu souhaites gérer)
typedef union {
    int intValue;
    float floatValue;
    char charValue;
} Value;

// Déclaration des tables
TableEntry Tab[TABLE_SIZE];  // Table des IDF et CONST

void initialiserTable(TableEntry table[], int taille) {
    for (int i = 0; i < taille; i++) {
        table[i].name[0] = '\0';
        table[i].type[0] = '\0';
        table[i].isConst = 0;
        table[i].value.intValue = 0;  // Initialisation de la valeur avec 0
        table[i].arraySize = 0;
        table[i].arrayValues = NULL;
    }
}

// Fonction de recherche dans la table des symboles
TableEntry* rechercher(TableEntry table[], const char entite[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(table[i].name, entite) == 0) {
            return &table[i];  // Retourner le pointeur vers l'entrée trouvée
        }
    }
    return NULL;  // Retourner NULL si l'entité n'a pas été trouvée
}

// F
void inserer(TableEntry table[], const char entite[], const char type[], Value val, int arraySize, int isConst) {
    if (estPleine(table)) {
        printf("Erreur : Table des symboles pleine.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].name[0] == '\0') {  // Emplacement libre trouvé
            strncpy(table[i].name, entite, 8);
            strncpy(table[i].type, type, 9);
            table[i].isConst = isConst;
            table[i].arraySize = arraySize;

            if (arraySize > 0) {  // C'est un tableau
                table[i].arrayValues = (Value *)malloc(arraySize * sizeof(Value));
                if (table[i].arrayValues == NULL) {
                    printf("Erreur : Allocation mémoire échouée pour le tableau.\n");
                    return;
                }
                // Initialisation du tableau
                for (int j = 0; j < arraySize; j++) {
                    table[i].arrayValues[j].intValue = 0;  // Initialisation à une valeur par défaut (0 pour int)
                }
            } else {
                // Assigner la valeur en fonction du type
                if (strcmp(type, "INTEGER") == 0) {
                    table[i].value.intValue = val.intValue;
                } else if (strcmp(type, "FLOAT") == 0) {
                    table[i].value.floatValue = val.floatValue;
                } else if (strcmp(type, "CHAR") == 0) {
                    table[i].value.charValue = val.charValue;
                }
            }
            return;
        }
    }
}

// Fonction pour insérer une valeur dans un tableau à un index donné
// Fonction pour insérer une valeur dans un tableau à un index donné
void insererValeurTableau(TableEntry *entry, int index, Value value) {
    if (entry == NULL || entry->arrayValues == NULL) {
        printf("Erreur : Entrée invalide ou tableau non initialisé.\n");
        return;
    }
    if (index < 0 || index >= entry->arraySize) {
        printf("Erreur : Index hors limites pour le tableau '%s'.\n", entry->name);
        return;
    }

    // Assigner la valeur en fonction du type de donnée dans l'union
    if (strcmp(entry->type, "INTEGER") == 0) {
        entry->arrayValues[index].intValue = value.intValue;
    } else if (strcmp(entry->type, "FLOAT") == 0) {
        entry->arrayValues[index].floatValue = value.floatValue;
    } else if (strcmp(entry->type, "CHAR") == 0) {
        entry->arrayValues[index].charValue = value.charValue;
    } else {
        printf("Erreur : Type de donnée inconnu pour le tableau '%s'.\n", entry->name);
    }
}

// Fonction pour vérifier si la table est pleine (optionnelle, peut être utilisée dans l'insertion)
int estPleine(TableEntry table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].name[0] == '\0') {  // Si un emplacement vide est trouvé
            return 0;  // La table n'est pas pleine
        }
    }
    return 1;  // La table est pleine
}

// Fonction pour modifier une variable simple
// Fonction pour modifier une variable simple
void modifierVariable(char *nomVariable, Value nouvelleValeur) {
    // Recherche de l'entrée dans la table des symboles par son nom
    TableEntry *entry = rechercher(Tab, nomVariable);
    
    // Vérification si l'entrée existe
    if (entry == NULL) {
        printf("Erreur : La variable '%s' n'est pas déclarée.\n", nomVariable);
        return;
    }

    // Si c'est un tableau, on affiche un message d'erreur
    if (entry->arraySize > 0) {
        printf("Erreur : Impossible de modifier une valeur d'un tableau directement.\n");
        return;
    }

    // Modifier la valeur en fonction du type de la variable
    if (strcmp(entry->type, "INTEGER") == 0) {
        entry->value.intValue = nouvelleValeur.intValue;
    } else if (strcmp(entry->type, "FLOAT") == 0) {
        entry->value.floatValue = nouvelleValeur.floatValue;
    } else if (strcmp(entry->type, "CHAR") == 0) {
        entry->value.charValue = nouvelleValeur.charValue;
    } else {
        printf("Erreur : Type de donnée inconnu pour la variable '%s'.\n", nomVariable);
        return;
    }

    printf("La variable '%s' a été modifiée avec succès.\n", nomVariable);
}

// Fonction pour modifier une valeur dans un tableau à un indice donné
void modifierValeurTableau(char *nomTableau, int index, Value nouvelleValeur) {
    // Recherche de l'entrée dans la table des symboles par son nom
    TableEntry *entry = rechercher(Tab, nomTableau);
    
    // Vérification si l'entrée existe et si c'est bien un tableau
    if (entry == NULL) {
        printf("Erreur : Le tableau '%s' n'est pas déclaré.\n", nomTableau);
        return;
    }
    
    if (entry->arraySize == 0) {
        printf("Erreur : '%s' n'est pas un tableau.\n", nomTableau);
        return;
    }

    // Vérification si l'index est valide
    if (index < 0 || index >= entry->arraySize) {
        printf("Erreur : L'indice %d est hors des limites du tableau '%s'.\n", index, nomTableau);
        return;
    }

    // Modification de la valeur à l'indice donné dans le tableau, en fonction du type
    if (strcmp(entry->type, "INTEGER") == 0) {
        entry->arrayValues[index].intValue = nouvelleValeur.intValue;
    } else if (strcmp(entry->type, "FLOAT") == 0) {
        entry->arrayValues[index].floatValue = nouvelleValeur.floatValue;
    } else if (strcmp(entry->type, "CHAR") == 0) {
        entry->arrayValues[index].charValue = nouvelleValeur.charValue;
    } else {
        printf("Erreur : Type de donnée inconnu pour le tableau '%s'.\n", nomTableau);
        return;
    }

    printf("La valeur à l'indice %d du tableau '%s' a été modifiée avec succès.\n", index, nomTableau);
}











/// en gros 7a ykoun 3ndna pour les tableau un pointeur vers une table de valeur ( nss79ouha f la semantique)
// pour que si g une table j enregistre ses valeurs hneya
//srt f la semantique g besoin des valeurs actuelles des fct 