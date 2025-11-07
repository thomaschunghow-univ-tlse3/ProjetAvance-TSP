/*
 * affichage.h
 *
 * Affichage des données.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H


#include "structure_permutation.h"
#include "lecture_donnees.h"
#include "options.h"
#include "traitement_tournee.h"

#include <stdio.h>


#define RESET "\033[0m"
#define ROUGE "\033[31m"

void afficher_noms_champs(FILE *sortie);


void afficher_permutation(FILE *sortie, Permutation, size_t nombre_max_points);


void afficher_longueur(FILE *sortie, distance);

void afficher_tournee(FILE *sortie, char *nom_fichier, MethodeCalcul, double temps, distance, Permutation);

#endif // AFFICHAGE_H