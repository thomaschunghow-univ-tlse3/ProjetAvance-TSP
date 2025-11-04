/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f2faa0f (rebase)

#ifndef TOURNEE_2_OPTIMISATION_H
#define TOURNEE_2_OPTIMISATION_H

#include "tournee_canonique.h"
#include "affichage.h"

Resultat tournee_plus_proche_voisin(MatriceDistance);

size_t donner_nombre_aleatoire(size_t borne_inf, size_t borne_sup);

Resultat tournee_marche_aleatoire(MatriceDistance);

Resultat tournee_2_optimisation_plus_proche_voisin(MatriceDistance);

Resultat tournee_2_optimisation_marche_aleatoire(MatriceDistance);

<<<<<<< HEAD
=======
 
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
>>>>>>> f2faa0f (rebase)
int parcours_tableau(const void *P1, const void *P2);

int normalisation(const void *P1, const void *P2);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> f2faa0f (rebase)
typedef int (*compar)(const void *, const void *);

void recherche_croisement(MatriceDistance matrice, compar comparateur);

<<<<<<< HEAD
#endif // TOURNEE_2_OPTIMISATION_H
=======
typedef int (*compar)(const void *,const void *);

void recherche_croisement(MatriceDistance matrice, compar comparateur);
>>>>>>> 20e72f5 (modification de l'arborescence)
=======
#endif // TOURNEE_2_OPTIMISATION_H
>>>>>>> f2faa0f (rebase)
