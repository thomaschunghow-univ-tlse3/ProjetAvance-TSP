/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */
<<<<<<< HEAD
#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "tournee_2_optimisation.h"
#include "traitement_tournee.h"

typedef struct population *Population;

Population population_creer(MatriceDistance matrice, size_t N, double pMutation );

void supprimer_population(Population population);

Resultat repeter_croisement(Population population, size_t nbGeneration);

#endif
=======
>>>>>>> 20e72f5 (modification de l'arborescence)
