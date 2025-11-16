/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */

#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "traitement_tournee.h"

Resultat tournee_genetique_generique(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation, size_t taille_tournoi);

Resultat tournee_genetique_dpx(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation);

#endif // TOURNEE_GENETIQUE_H
