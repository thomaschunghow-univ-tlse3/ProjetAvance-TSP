/*
 * traitement_tournee.h
 *
 * Outil de traitement de tous les algorithmes de tournée.
 */

#ifndef TRAITEMENT_TOURNEE_H
#define TRAITEMENT_TOURNEE_H

#include "structure_permutation.h"
#include "options.h"

typedef struct
{
    Permutation permutation;
    distance longueur;
} Resultat;

typedef Resultat (*AlgorithmeTournee)(MatriceDistance);


void tournee_traitement(FILE *sortie, Options, MatriceDistance);

size_t tournee_nb_sommet(Resultat *resultat);

Permutation tournee_permutation(Resultat *resultat);

distance tournee_longueur(Resultat *resultat);

size_t tournee_sommet_numero(Resultat *resultat, size_t indice);

void supprimer_tournee(Resultat *resultat);


#endif // TRAITEMENT_TOURNEE_H