/*
 * affichage.h
 *
 * Affichage des données.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

<<<<<<< HEAD
<<<<<<< HEAD
#include "lecture_donnees.h"
#include "traitement_tournee.h"

=======
#include "structure_permutation.h"
#include "lecture_donnees.h"
#include "options.h"
#include "traitement_tournee.h"

#include <stdio.h>

>>>>>>> 20e72f5 (modification de l'arborescence)
=======
#include "lecture_donnees.h"
#include "traitement_tournee.h"

>>>>>>> f2faa0f (rebase)
#define RESET "\033[0m"
#define ROUGE "\033[31m"

void afficher_noms_champs(FILE *sortie);

<<<<<<< HEAD
<<<<<<< HEAD
void afficher_permutation(FILE *sortie, Permutation, size_t nombre_max_points);
=======
void afficher_permutation(FILE *sortie, Permutation);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
void afficher_permutation(FILE *sortie, Permutation, size_t nombre_max_points);
>>>>>>> f2faa0f (rebase)

void afficher_longueur(FILE *sortie, distance);

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul, double temps, distance, Permutation);

#endif // AFFICHAGE_H