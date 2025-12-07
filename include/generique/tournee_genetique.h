/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */

#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "structure_matrice.h"
#include "structure_morceau.h"
#include "structure_permutation.h"
#include "structure_tableau_permutation.h"

typedef enum
{
    LIGHT,
    DPX,
} GenetiqueVariante;

void tournee_genetique_light(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations,
                             double taux_mutation, size_t taille_tournoi, Permutation permutation_resultat,
                             TableauPermutation population, TableauPermutation enfants, TableauPermutation parents,
                             Permutation inverse);

void tournee_genetique_dpx(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations,
                           double taux_mutation, size_t taille_tournoi, Permutation permutation_resultat,
                           TableauPermutation population, TableauPermutation enfants, TableauPermutation parents,
                           Permutation inverse, TableauMorceau morceaux);

#endif // TOURNEE_GENETIQUE_H
