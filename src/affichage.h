/*
 *
 * Ce module fournit les différentes fonctions d'affichage.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures_permutations.h"
#include "traitement_lecture_donnees.h"
#include "traitement_options.h"
#include "traitement_calcul_tournee.h"

#include <stdio.h>

void afficher_noms_champs(FILE *sortie);

void afficher_specification(FILE *, Specification);
void afficher_tableau_points(FILE *, TableauPoints);
void afficher_matrice(FILE *, MatriceDistances);

void afficher_tournee(FILE *, char *nom_fichier, MethodeCalcul methode, double temps, distance, Resultat);

#endif // AFFICHAGE_H