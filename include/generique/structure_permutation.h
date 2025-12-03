/*
 * structure_permutation.h
 *
 * Permutation :
 * Définition et opérations du type abstrait de permutation.
 *
 * Remarque : les permutations sont initialisées dans l’ordre canonique,
 * puis parcourues dans l’ordre lexical, en fixant le premier indice.
 * C'est-à-dire, on calcule les (n-1)! permutations, et non pas les n! permutations,
 * car comparer toutes les tournées revient à comparer toutes les tournées qui partent du même point.
 *
 * La permutation est également associée à sa longueur.
 * Cependant, la longueur peut ne plus être valide après certaines opérations.
 * Il faut porter attention à initialiser correctement la longueur,
 * et à la mettre à jour après une opération qui modifie la permutation.
 */

#ifndef STRUCTURE_PERMUTATION_H
#define STRUCTURE_PERMUTATION_H

#include "structure_matrice.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct permutation *Permutation;

Permutation permutation_creer(size_t nombre_sommets, size_t taille_distance);
void permutation_supprimer(Permutation *);

void permutation_initialiser(Permutation);
void permutation_melanger(Permutation);

void permutation_inverser(Permutation, Permutation inverse);

void permutation_renverser_morceau(Permutation, size_t sommet_A, size_t sommet_B);

void permutation_decaler(Permutation, size_t nombre_decalage_gauche);
void permutation_decaler_morceau(Permutation, size_t nombre_decalage_gauche, size_t sommet_A, size_t sommet_B);

void permutation_copier(Permutation destination, Permutation source);

size_t permutation_obtenir_nombre_sommets(Permutation);

size_t permutation_obtenir_sommet(Permutation, size_t indice);
void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B);

size_t permutation_obtenir_taille_distance(Permutation);

void permutation_obtenir_longueur(Permutation, void *longueur_destination);
void permutation_modifier_longueur(Permutation, void *longueur_source);

int permutation_comparer_longueurs(Permutation permutation_A, Permutation permutation_B, DistanceComparer);

void permutation_calculer_longueur(Permutation permutation, MatriceDistance matrice);
void permutation_calculer_longueur_avec_elagage(Permutation permutation, MatriceDistance matrice, Permutation permutation_minimale);

bool permutation_avancer(Permutation);
bool permutation_avancer_et_incrementer_longueur(Permutation permutation, MatriceDistance matrice);

void permutation_echanger_aretes(Permutation, size_t sommet_A, size_t sommet_B);
bool permutation_decroiser(MatriceDistance matrice, Permutation permutation, size_t sommet_A, size_t sommet_B, Permutation permutation_decroisee);

#endif // STRUCTURE_PERMUTATION_H
