/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"

Resultat tournee_genetique_generique(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    Resultat resultat;
    resultat.longueur = 0;
    resultat.permutation = permutation_creer(5);
    (void)nombre_individus;
    (void)nombre_generations;
    (void)taux_mutation;
    return resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance, size_t nombre_individus, size_t nombre_generations, double taux_mutation)
{
    Resultat resultat;
    resultat.longueur = 0;
    resultat.permutation = permutation_creer(5);
    (void)nombre_individus;
    (void)nombre_generations;
    (void)taux_mutation;
    return resultat;
}
