/*
 * affichage.h
 *
 * Ce module fournit les différentes fonctions d'affichage.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures_de_donnees.h"
#include "lecture_donnees.h"

#include <stdio.h>

void afficher_specification(FILE *, Specification);

void afficher_tableau_points(FILE *, TableauPoints);

void afficher_matrice(FILE *, MatriceDistances);

void afficher_tournee(FILE *, TableauDistances);



#endif // AFFICHAGE_H