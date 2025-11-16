/*
 * structure_permutation.h
 *
 * Définitions et opérations sur les permutations.
 *
 * Remarque : les permutations sont initialisées dans l’ordre canonique,
 * puis parcourues dans l’ordre lexical, en fixant le premier indice.
 * C'est-à-dire, on calcule les (n-1)! permutations, et non pas les n! permutations,
 * car comparer toutes les tournées revient à comparer toutes les tournées qui partent du même point.
 */

#ifndef STRUCTURE_PERMUTATION_H
#define STRUCTURE_PERMUTATION_H

#include "structure_matrice.h"

#include <stdbool.h>

typedef struct permutation *Permutation;

Permutation permutation_creer(size_t nombre_sommets);
void permutation_supprimer(Permutation *);

void permutation_initialiser(Permutation);
void permutation_initialiser_aleatoirement(Permutation);

bool permutation_avancer(Permutation);
bool permutation_avancer_et_incrementer_longueur(Permutation, MatriceDistance, distance *longueur);

size_t permutation_obtenir_taille(Permutation);

size_t permutation_obtenir_sommet(Permutation, size_t indice);

void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B);

distance permutation_calculer_distance_totale(Permutation, MatriceDistance);
distance permutation_calculer_distance_totale_avec_elagage(Permutation, MatriceDistance, distance longueur_minimale);

void permutation_copier(Permutation destination, Permutation source);

void permutation_echanger_aretes(Permutation, size_t sommet_A, size_t sommet_B);
distance permutation_difference_apres_decroisement(MatriceDistance, Permutation, size_t sommet_A, size_t sommet_B);

void permutation_inverser(Permutation, Permutation inverse);

void permutation_decaler(Permutation, size_t nombre_decalage_gauche);

/* Tableaux de permutation. */

typedef struct tableau_permutation *TableauPermutation;

TableauPermutation tableau_permutation_creer(size_t nombre_permutations);
void tableau_permutation_allouer(TableauPermutation, size_t nombre_sommets);

void tableau_permutation_vider(TableauPermutation);
void tableau_permutation_supprimer(TableauPermutation *);

size_t tableau_permutation_obtenir_nombre_permutation(TableauPermutation);

Permutation tableau_permutation_obtenir_permutation(TableauPermutation, size_t indice);
void tableau_permutation_modifier_permutation(TableauPermutation, size_t indice, Permutation);
distance tableau_permutation_obtenir_longueur(TableauPermutation, size_t indice);
void tableau_permutation_modifier_longueur(TableauPermutation, size_t indice, distance longueur);

size_t tableau_permutation_trouver_pire_individu(TableauPermutation);
size_t tableau_permutation_trouver_meilleur_individu(TableauPermutation);

void tableau_permutation_echanger_tableaux(TableauPermutation *tableau_A, TableauPermutation *tableau_B);

void tableau_permutation_trier(TableauPermutation);

#endif // STRUCTURE_PERMUTATION_H
