#include <stdio.h>
#include "ts.h"
#include "quadruplet.h"

extern int yyparse();
extern FILE *yyin;

int main(int argc, char **argv) {
    
    if (argc < 2) {
        fprintf(stderr, "Erreur : aucun fichier spécifié.\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    initialisation();
    yyin = f;
    yyparse();
    afficherTable(Tab, 1000);
    fclose(f);
    afficher_quadruplets();
    free_all_quadruplets();  // Free memory allocated for quadruplets
    return 0;
}