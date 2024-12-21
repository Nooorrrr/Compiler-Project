#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUADRUPLETS 1000  // Limite de quadruplets
int tempCount = 0;

typedef struct {
    char* op;
    char* arg1;
    char* arg2;
    char* result;
} Quadruplet;

Quadruplet* quadruplets[MAX_QUADRUPLETS];  // Tableau pour stocker jusqu'à 1000 quadruplets
int quadruplet_count = 0;

// Fonction pour créer un quadruplet
Quadruplet* create_quadruplet(const char* op, const char* arg1, const char* arg2, const char* result) {
    Quadruplet* quad = (Quadruplet*)malloc(sizeof(Quadruplet));
    if (!quad) {
        fprintf(stderr, "Memory allocation failed for Quadruplet\n");
        exit(EXIT_FAILURE);
    }

    quad->op = op ? strdup(op) : NULL;
    quad->arg1 = arg1 ? strdup(arg1) : NULL;
    quad->arg2 = arg2 ? strdup(arg2) : NULL;
    quad->result = result ? strdup(result) : NULL;

    if (!quad->op || !quad->arg1 || !quad->arg2 || !quad->result) {
        fprintf(stderr, "Memory allocation failed for strings in Quadruplet\n");
        exit(EXIT_FAILURE);
    }

    return quad;
}


// Fonction pour convertir un entier en chaîne de caractères
char* convert(int i) {
    char* s = (char*)malloc(15 * sizeof(char));  // Allocation de mémoire pour la chaîne
    if (!s) {
        fprintf(stderr, "Memory allocation failed for string conversion\n");
        exit(EXIT_FAILURE);
    }
    sprintf(s, "%d", i);
    return s;
}

// Fonction pour afficher un quadruplet
void print_quadruplet(const Quadruplet* quad) {
    if (quad) {
        printf("(%s, %s, %s, %s)\n", quad->op, quad->arg1, quad->arg2, quad->result);
    }
}

// Fonction pour générer un quadruplet
void generer(char* a, char* b, char* c, char* d) {
printf("%s     %s      %s     %s",a,b,c,d);
    if (!a ) {
        fprintf(stderr, "Invalid argument(s) passed to generer: NULL\n");
        exit(EXIT_FAILURE);
    }
    if (!b) {
        fprintf(stderr, "Invalid argument(s) passed to generer: NULL 2\n");
        exit(EXIT_FAILURE);
    }
    if (!c ) {
        fprintf(stderr, "Invalid argument(s) passed to generer: NULL 3\n");
        exit(EXIT_FAILURE);
    }if (!d) {
        fprintf(stderr, "Invalid argument(s) passed to generer: NULL 4\n");
        exit(EXIT_FAILURE);
    }

    printf("Generating quadruplet: (%s, %s, %s, %s)\n", a, b, c, d);

    if (quadruplet_count >= MAX_QUADRUPLETS) {
        fprintf(stderr, "Quadruplet limit exceeded\n");
        exit(EXIT_FAILURE);
    }

    quadruplets[quadruplet_count] = create_quadruplet(a, b, c, d);
    quadruplet_count++;
}


// Fonction pour afficher tous les quadruplets générés
void afficher_quadruplets() {
    printf("*********************Quadruplets***********************\n");
    for (int i = 0; i < quadruplet_count; i++) {
        print_quadruplet(quadruplets[i]);
        printf("---------------------------------------------------\n");
    }
}

// Fonction pour libérer la mémoire d'un quadruplet
void free_quadruplet(Quadruplet *quad) {
    if (quad) {
        if (quad->op) {
            free(quad->op);
            quad->op = NULL;
        }
        if (quad->arg1) {
            free(quad->arg1);
            quad->arg1 = NULL;
        }
        if (quad->arg2) {
            free(quad->arg2);
            quad->arg2 = NULL;
        }
        if (quad->result) {
            free(quad->result);
            quad->result = NULL;
        }
        free(quad);
    }
}

// Fonction pour libérer la mémoire de tous les quadruplets
void free_all_quadruplets() {
    for (int i = 0; i < quadruplet_count; i++) {
        if (quadruplets[i]) {
            free_quadruplet(quadruplets[i]);
            quadruplets[i] = NULL;
        }
    }
    quadruplet_count = 0; // Réinitialiser le compteur après la libération
}


// Fonction pour gérer les expressions logiques et générer les quadruplets associés
void quadL(int i, char* b, char* c, char* d) {
    switch(i) {
        case 1 :
            generer("BNZ", convert(quadruplet_count + 3), b, "");
            generer("=", "", "1", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "0", d);
            break;
        case 2 :
            generer("BNZ", convert(quadruplet_count + 4), b, "");
            generer("BNZ", convert(quadruplet_count + 3), c, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 3 :
            generer("BZ", convert(quadruplet_count + 4), b, "");
            generer("BZ", convert(quadruplet_count + 3), c, "");
            generer("=", "", "1", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "0", d);
            break;
    }
}

// Fonction pour gérer les expressions de comparaison et générer les quadruplets associés
void quadC(int i, char* b, char* c, char* d) {
    switch(i) {
        case 1 :
            generer("-", b, c, d);
            generer("BG", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 2 :
            generer("-", b, c, d);
            generer("BGE", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 3 :
            generer("-", b, c, d);
            generer("BL", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 4 :
            generer("-", b, c, d);
            generer("BLE", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 5 :
            generer("-", b, c, d);
            generer("BZ", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
        case 6 :
            generer("-", b, c, d);
            generer("BNZ", convert(quadruplet_count + 3), d, "");
            generer("=", "", "0", d);
            generer("BR", convert(quadruplet_count + 2), "", "");
            generer("=", "", "1", d);
            break;
    }
}

void delete_quad(Quadruplet* quad) {
    if (quad) {
        free(quad->op);
        free(quad->arg1);
        free(quad->arg2);
        free(quad->result);
        free(quad);
    }
}
