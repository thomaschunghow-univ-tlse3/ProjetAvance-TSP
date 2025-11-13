/*
 * tournee_genetique.h
 *
 * Algorithme génétique.
 */

#ifndef TOURNEE_GENETIQUE_H
#define TOURNEE_GENETIQUE_H

#include "traitement_tournee.h"

Resultat tournee_genetique_generique(MatriceDistance m , size_t nombre_individus, size_t nombre_generations, double taux_mutation);

Resultat tournee_genetique_dpx(MatriceDistance m , size_t nombre_individus, size_t nombre_generations, double taux_mutation);

#endif // TOURNEE_GENETIQUE_H
