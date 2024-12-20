#ifndef QUADRUPLET_H
#define QUADRUPLET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour un quadruplet
typedef struct {
    char *op;         // L'opérateur (+, -, *, /, etc.)
    char *arg1;       // Premier opérande
    char *arg2;       // Deuxième opérande
    char *result;     // Résultat
} Quadruplet;

// Fonction pour créer un quadruplet
Quadruplet* create_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result);

// Fonction pour afficher un quadruplet
void print_quadruplet(Quadruplet *quad);

// Fonction pour afficher tous les quadruplets
void print_all_quadruplets();

// Fonction pour libérer la mémoire d'un quadruplet
void free_quadruplet(Quadruplet *quad);

// Fonction pour ajouter un quadruplet à une liste
void add_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result);

#endif
