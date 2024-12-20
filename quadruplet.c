#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quadruplet.h"
#include "ts.c"

// quadruplets pour stocker les quadruplets
Quadruplet *quadruplets[1000];  // Tableau pour stocker jusqu'à 1000 quadruplets
int quadruplet_count = 0;       // Compteur pour le nombre de quadruplets

// Fonction pour créer un quadruplet
Quadruplet* create_quadruplet(const char *op, const char *arg1, const char *arg2, const char *result) {
    
Quadruplet *quad = (Quadruplet*)malloc(sizeof(Quadruplet));
    if (!quad) {
        perror("Erreur d'allocation mémoire pour Quadruplet");
        exit(EXIT_FAILURE);
    }
    quad->op = strdup(op);
    quad->arg1 = strdup(arg1);
    quad->arg2 = strdup(arg2);
    quad->result = strdup(result);

    if (!quad->op || !quad->arg1 || !quad->arg2 || !quad->result) {
        perror("Erreur d'allocation mémoire pour les chaînes du Quadruplet");
        free_quadruplet(quad);
        exit(EXIT_FAILURE);
    }

    return quad;
}

// Fonction pour convertir un entier en chaîne de caractères
char* convert(int i) {
    char s[15];
    sprintf(s, "%d", i);
    return strdup(s);
}

// Fonction pour afficher un quadruplet
void print_quadruplet(const Quadruplet *quad) {
    if (quad) {
        printf("(%s, %s, %s, %s)\n", quad->op, quad->arg1, quad->arg2, quad->result);
    }
}

// Fonction pour générer un quadruplet
void generer(char* a, char* b, char* c, char* d) {
    quadruplets[quadruplet_count] = create_quadruplet(a, b, c, d);
    quadruplet_count++;
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

// Fonction pour afficher tous les quadruplets générés
void afficher_quadruplets() {
    printf("*********************Quadruplets***********************\n");
    for (int i = 0; i < quadruplet_count; i++) {
        print_quadruplet(quadruplets[i]);
        printf("---------------------------------------------------\n");
    }
}

void delete_quad() {
    int i,j,k,t,p;
	char *temp;
    for (int i = 0; i < quadruplet_count; i++) {
        if (strcmp(quadruplets[i]->op, "=") == 0) {  // Si l'opération est "="
            j = i + 1;
            temp = strdup(quadruplets[i]->result);
            k = 0;
            while (j < quadruplet_count && k == 0) {
                // Afficher des informations de débogage pour chaque quadruplet comparé
                printf("Comparing result: %s with arg1: %s and arg2: %s\n", 
                       quadruplets[i]->result, quadruplets[j]->arg1, quadruplets[j]->arg2);
                // Si la valeur 'result' du quadruplet "=" est utilisée ailleurs (dans 'arg1' ou 'arg2')
                if (strcmp(quadruplets[j]->arg1, temp) == 0 || strcmp(quadruplets[j]->arg2, temp) == 0||((strcmp(quadruplets[j]->op,"BR")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BZ")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BNZ")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BG")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BGE")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BL")==0)&&(atoi(quadruplets[j]->arg1)<i))||((strcmp(quadruplets[j]->op,"BLE")==0)&&(atoi(quadruplets[j]->arg1)<i))){
                    k = 1;  // Trouvé, ne supprime pas ce quadruplet
                }
                j++;
            }

            if (k == 0) {  // Si 'result' n'est pas utilisé ailleurs, on supprime le quadruplet
                t=0;
                p=i;
                while((p>0)&&(t==0)){
                if((strcmp(quadruplets[p-1]->op,"+")==0)||(strcmp(quadruplets[p-1]->op,"-")==0)||(strcmp(quadruplets[p-1]->op,"*")==0)||(strcmp(quadruplets[p-1]->op,"/")==0)){
                	p--;
				}
                	else{
					t=1;
					}
				}
           	    for(j=p;j<quadruplet_count-1;j++){
					quadruplets[j]=quadruplets[j+(i-p)+1];
				}
				quadruplet_count=quadruplet_count-(i-p)-1;
			}
		}
	}
}




// Fonction pour libérer la mémoire d'un quadruplet
void free_quadruplet(Quadruplet *quad) {
    if (quad) {
        free(quad->op);
        free(quad->arg1);
        free(quad->arg2);
        free(quad->result);
        free(quad);
    }
}

// Fonction pour libérer la mémoire de tous les quadruplets
void free_all_quadruplets() {
    for (int i = 0; i < quadruplet_count; i++) {
        free_quadruplet(quadruplets[i]);
    }
    quadruplet_count = 0; // Réinitialiser le compteur après la libération
}
