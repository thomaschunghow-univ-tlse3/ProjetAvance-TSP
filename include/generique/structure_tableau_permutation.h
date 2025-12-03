/*
 * structure_tableau_permutation.h
 *
 * Tableau de permutation :
 * Définition et opérations du type abstrait de tableau de permutation.
 */

#ifndef STRUCTURE_TABLEAU_PERMUTATION_H
#define STRUCTURE_TABLEAU_PERMUTATION_H

#include "structure_matrice.h"
#include "structure_permutation.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct tableau_permutation *TableauPermutation;

TableauPermutation tableau_permutation_creer(size_t nombre_permutations, size_t nombre_sommets, size_t taille_distance);
void tableau_permutation_supprimer(TableauPermutation *);

size_t tableau_permutation_obtenir_nombre_permutations(TableauPermutation);

Permutation tableau_permutation_obtenir_permutation(TableauPermutation, size_t indice);
void tableau_permutation_obtenir_longueur(TableauPermutation, size_t indice, void *longueur_destination);
void tableau_permutation_modifier_longueur(TableauPermutation, size_t indice, void *longueur_source);

size_t tableau_permutation_trouver_pire_individu(TableauPermutation, DistanceComparer);
size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation, DistanceComparer);

void tableau_permutation_echanger_tableaux(TableauPermutation *tableau_A, TableauPermutation *tableau_B);

void tableau_permutation_trier(TableauPermutation, DistanceComparer);

#endif // STRUCTURE_TABLEAU_PERMUTATION_H
