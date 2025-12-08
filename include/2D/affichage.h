/*
 * affichage.h
 *
 * Affichage des données.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "traitement_tournee.h"

#include <stddef.h>
#include <stdio.h>

#define ROUGE "\033[31m"
#define RESET "\033[0m"

void afficher_noms_champs(FILE *sortie);

void afficher_points(FILE *sortie, MatriceDistance);

void afficher_permutation(FILE *sortie, Permutation, size_t nombre_max_points);

void afficher_longueur(FILE *sortie, Permutation);

void afficher_tournee(FILE *sortie, char *nom_fichier, Methode, double temps, Permutation);

/* DEBUG */

#include "structure_morceau.h"

void afficher_morceaux(FILE *sortie, TableauMorceau);

#endif // AFFICHAGE_H
