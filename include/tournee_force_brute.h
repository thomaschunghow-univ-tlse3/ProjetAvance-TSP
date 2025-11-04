/*
 * tournee_force_brute.h
 *
 * Algorithme de force brute.
 */

#ifndef TOURNEE_FORCE_BRUTE_H
#define TOURNEE_FORCE_BRUTE_H

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f2faa0f (rebase)
#include "traitement_tournee.h"

/* Méthode classique. */
Resultat tournee_force_brute_naive(MatriceDistance matrice);
<<<<<<< HEAD
=======
#include "structure_permutation.h"
#include "traitement_tournee.h"

/* Méthode classique. */
Resultat calcul_tournee_force_brute_naive(MatriceDistance matrice);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
>>>>>>> f2faa0f (rebase)

/* Méthode avec élagage :
 * A chaque permutation, on calcule la longueur de la nouvelle tournée.
 * A l'ajout de chaque distance, si la valeur de la somme partielle
 * dépasse celle de la longueur de la meilleure tournée,
 * alors on abandonne et on passe à la prochaine permutation. */
<<<<<<< HEAD
<<<<<<< HEAD
Resultat tournee_force_brute_elagage(MatriceDistance matrice);
=======
Resultat calcul_tournee_force_brute_elagage(MatriceDistance matrice);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
Resultat tournee_force_brute_elagage(MatriceDistance matrice);
>>>>>>> f2faa0f (rebase)

/* Méthode incrémentale :
 * A chaque permutation, à la longueur de l'ancienne tournée,
 * on supprime puis on ajoute uniquement les distances entre les points qui ont été échangés par l'algorithme.
 * Ainsi, pour passer de la longueur de l'ancienne tournée à la longueur de la tournée courante,
 * on réalise au maximum cinq soustractions puis cinq additions,
 * donc au maximum dix opérations par permutation. */
<<<<<<< HEAD
<<<<<<< HEAD
Resultat tournee_force_brute_incrementale(MatriceDistance matrice);
=======
Resultat calcul_tournee_force_brute_incrementale(MatriceDistance matrice);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
Resultat tournee_force_brute_incrementale(MatriceDistance matrice);
>>>>>>> f2faa0f (rebase)

#endif // TOURNEE_FORCE_BRUTE_H