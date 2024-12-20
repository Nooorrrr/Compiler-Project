#include "quadruplet.h"

// Liste pour stocker les quadruplets
Quadruplet *quadruplets[1000];  // Tableau pour stocker jusqu'à 1000 quadruplets
int quadruplet_count = 0;        // Compteur pour le nombre de quadruplets

// Fonction pour créer un quadruplet
Quadruplet* create_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result) {
    Quadruplet *quad = (Quadruplet*)malloc(sizeof(Quadruplet));
    quad->op = strdup(op);
    quad->arg1 = strdup(arg1);
    quad->arg2 = strdup(arg2);
    quad->result = strdup(result);
    return quad;
}

// Fonction pour afficher un quadruplet
void print_quadruplet(Quadruplet *quad) {
    printf("(%s, %s, %s, %s)\n", quad->op, quad->arg1, quad->arg2, quad->result);
}

// Fonction pour afficher tous les quadruplets
void print_all_quadruplets() {
    for (int i = 0; i < quadruplet_count; i++) {
        print_quadruplet(quadruplets[i]);
    }
}

// Fonction pour libérer la mémoire d'un quadruplet
void free_quadruplet(Quadruplet *quad) {
    free(quad->op);
    free(quad->arg1);
    free(quad->arg2);
    free(quad->result);
    free(quad);
}

// Fonction pour ajouter un quadruplet à la liste
void add_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result) {
    if (quadruplet_count < 1000) {
        quadruplets[quadruplet_count++] = create_quadruplet(op, arg1, arg2, result);
    } else {
        printf("Erreur: Nombre maximum de quadruplets atteint.\n");
    }
}
