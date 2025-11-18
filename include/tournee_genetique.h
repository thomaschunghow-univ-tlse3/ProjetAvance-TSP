/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */

#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "tournee_2_optimisation.h"
#include "traitement_tournee.h"
#include "structure_permutation.h"

typedef struct population *Population;

Population population_creer(MatriceDistance matrice, size_t N, double pMutation);

void supprimer_population(Population population);

Resultat repeter_croisement(Population population, size_t nbGeneration, bool dpx);

Resultat tournee_genetique(MatriceDistance matrice, size_t nbIndividus, size_t nb_generation, double proba);

Resultat tournee_genetique_dpx(MatriceDistance matrice, size_t nbIndividus, size_t nb_generation, double proba);

#endif


