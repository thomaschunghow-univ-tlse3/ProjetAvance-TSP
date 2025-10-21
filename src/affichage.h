/*
 *
 * Ce module fournit les différentes fonctions d'affichage.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structure_permutation.h"
#include "lecture_donnees.h"
#include "options.h"
#include "traitement_tournee.h"

#include <stdio.h>

void afficher_noms_champs(FILE *sortie);

void afficher_permutation(FILE *sortie, Permutation);

void afficher_tournee(FILE *, char *nom_fichier, MethodeCalcul methode, double temps, distance, Permutation);

#endif // AFFICHAGE_H