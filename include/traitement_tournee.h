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
<<<<<<< HEAD
<<<<<<< HEAD
    distance longueur;
=======
    distance distance;
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
    distance longueur;
>>>>>>> f2faa0f (rebase)
} Resultat;

typedef Resultat (*AlgorithmeTournee)(MatriceDistance);

<<<<<<< HEAD
<<<<<<< HEAD
void tournee_traitement(FILE *sortie, Options, MatriceDistance);
void supprimer_tournee(Resultat *resultat);
=======
void traitement_tournee(FILE *sortie, Options, MatriceDistance);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
void tournee_traitement(FILE *sortie, Options, MatriceDistance);
void supprimer_tournee(Resultat *resultat);
>>>>>>> f2faa0f (rebase)

#endif // TRAITEMENT_TOURNEE_H