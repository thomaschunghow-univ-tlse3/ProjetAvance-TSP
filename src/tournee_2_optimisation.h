/*
 * tournee_2_optimisation.h
 *
 * Algorithme de 2-optimisation.
 */
 
int parcours_tableau(const void *P1, const void *P2);

int normalisation(const void *P1, const void *P2);

typedef int (*Compar)(const void *,const void *);

void recherche_croisement(MatriceDistance matrice, Compar comparateur);