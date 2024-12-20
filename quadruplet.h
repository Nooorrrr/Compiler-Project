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

// Déclaration des variables globales
extern Quadruplet *quadruplets[1000];  // Tableau pour stocker jusqu'à 1000 quadruplets
extern int quadruplet_count;    
extern Quadruplet liste[1500]; // Liste des quadruplets
extern int qc;                 // Compteur des quadruplets

// Fonctions pour gérer les quadruplets
void generer(char* a, char* b, char* c, char* d);  // Générer un quadruplet
void quadL(int i, char* b, char* c, char* d);       // Gérer les expressions logiques
void quadC(int i, char* b, char* c, char* d);       // Gérer les expressions de comparaison
char* convert(int i);                              // Convertir un entier en chaîne de caractères

// Fonctions pour afficher les quadruplets
void afficher_quadruplets();                       // Afficher tous les quadruplets

// Fonctions de gestion de la mémoire
void delete_quad();                                // Supprimer les quadruplets inutilisés
void free_quadruplet(Quadruplet *quad);            // Libérer la mémoire d'un quadruplet
void free_all_quadruplets();                       // Libérer la mémoire de tous les quadruplets

// Fonction pour ajouter un quadruplet à la liste globale
void add_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result);

// Fonctions pour les branchements (saute conditionnel ou inconditionnel)
void add_unconditional_jump(const char *label);     // Ajouter un saut inconditionnel
void add_conditional_jump(const char *condition, const char *label); // Ajouter un saut conditionnel

#endif