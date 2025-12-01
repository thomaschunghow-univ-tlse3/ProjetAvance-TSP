/*
 * affichage.h
 *
 * Affichage des données.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "lecture_tsp.h"
#include "traitement_tournee.h"
#include "calcul_distance.h"

#define RESET "\033[0m"
#define ROUGE "\033[31m"

void afficher_noms_champs(FILE *sortie);

void afficher_points(FILE *sortie, MatriceDistance);

void afficher_permutation(FILE *sortie, Permutation, size_t nombre_max_points);

void afficher_longueur(FILE *sortie, Permutation);

void afficher_tournee(FILE *sortie, char *nom_fichier, Methode, double temps, Permutation);

#endif // AFFICHAGE_H