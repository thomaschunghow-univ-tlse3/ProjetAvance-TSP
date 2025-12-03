/*
 * tournee_force_brute.h
 *
 * Algorithme de force brute.
 */

#ifndef TOURNEE_FORCE_BRUTE_H
#define TOURNEE_FORCE_BRUTE_H

#include "structure_matrice.h"
#include "structure_permutation.h"

/* Méthode classique. */
Permutation tournee_force_brute_naive(MatriceDistance matrice);

/* Méthode avec élagage :
 * A chaque permutation, on calcule la longueur de la nouvelle tournée.
 * A l'ajout de chaque distance, si la valeur de la somme partielle
 * dépasse celle de la longueur de la meilleure tournée,
 * alors on abandonne et on passe à la prochaine permutation. */
Permutation tournee_force_brute_avec_elagage(MatriceDistance matrice);

/* Méthode incrémentale :
 * A chaque permutation, à la longueur de l'ancienne tournée,
 * on supprime puis on ajoute uniquement les distances entre les points qui ont été échangés par l'algorithme.
 * Ainsi, pour passer de la longueur de l'ancienne tournée à la longueur de la tournée courante,
 * on réalise au maximum cinq soustractions puis cinq additions,
 * donc au maximum dix opérations par permutation. */
Permutation tournee_force_brute_incrementale(MatriceDistance matrice);

#endif // TOURNEE_FORCE_BRUTE_H
