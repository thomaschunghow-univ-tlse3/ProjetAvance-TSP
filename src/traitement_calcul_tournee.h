/*
 */

#ifndef TRAITEMENT_CALCUL_TOURNEE_H
#define TRAITEMENT_CALCUL_TOURNEE_H

#include "structures_permutations.h"
#include "traitement_options.h"

#include <stdio.h>

typedef struct
{
    Permutation permutation;
    distance distance;
} Resultat;

typedef Resultat (*FonctionTraitement)(MatriceDistances);

extern FonctionTraitement liste_fonctions_traitement[];

void traitement(FILE *sortie, char *nom_fichier, MethodeCalcul methode, MatriceDistances matrice);

#endif // TRAITEMENT_CALCUL_TOURNEE_H