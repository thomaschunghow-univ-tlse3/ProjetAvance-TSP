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

<<<<<<< HEAD
<<<<<<< HEAD
Permutation permutation_creer(size_t nombre_sommets);
=======
Permutation permutation_creer(size_t nombre_indices);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
Permutation permutation_creer(size_t nombre_sommets);
>>>>>>> f2faa0f (rebase)
void permutation_supprimer(Permutation *);

bool permutation_avancer(Permutation);
bool permutation_avancer_et_incrementer_longueur(Permutation, MatriceDistance, distance *longueur);

size_t permutation_obtenir_taille(Permutation);

<<<<<<< HEAD
<<<<<<< HEAD
size_t permutation_obtenir_sommet(Permutation, size_t indice);

void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B);
=======
size_t permutation_obtenir_indice(Permutation, size_t indice);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
size_t permutation_obtenir_sommet(Permutation, size_t indice);

void permutation_echanger_sommets(Permutation permutation, size_t sommet_A, size_t sommet_B);
>>>>>>> f2faa0f (rebase)

distance permutation_calculer_distance_totale(Permutation, MatriceDistance);
distance permutation_calculer_distance_totale_avec_elagage(Permutation, MatriceDistance, distance longueur_minimale);

void permutation_copier(Permutation destination, Permutation source);

<<<<<<< HEAD
<<<<<<< HEAD
void permutation_echanger_aretes(Permutation, size_t sommet_A, size_t sommet_B);
distance permutation_difference_apres_decroisement(MatriceDistance, Permutation, size_t sommet_A, size_t sommet_B);

=======
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
void permutation_echanger_aretes(Permutation, size_t sommet_A, size_t sommet_B);
distance permutation_difference_apres_decroisement(MatriceDistance, Permutation, size_t sommet_A, size_t sommet_B);

>>>>>>> f2faa0f (rebase)
#endif // STRUCTURE_PERMUTATION_H
