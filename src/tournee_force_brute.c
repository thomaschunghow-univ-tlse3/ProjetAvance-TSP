/*
 */

#include "tournee_force_brute.h"
#include "structures_permutations.h"
#include "tournee_canonique.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h>

// TODO : brute force renvoie la permutation
distance brute_force(MatriceDistances matrice)
{
	size_t nombre_points = nombre_points_matrice(matrice);
	Permutation permutation_courante = creer_permutation(nombre_points);

	distance d_courante = distance_totale_permutation(permutation_courante, matrice);
	distance d_minimale = d_courante;
	printf("%lf\n", d_courante);

	printf("%lf\n", d_minimale);

	while (permutation_suivante(permutation_courante))
	{
		distance d_courante = distance_totale_permutation(permutation_courante, matrice);
		if (d_courante < d_minimale)
		{
			d_minimale = d_courante;
		}
	}
	supprimer_permutation(&permutation_courante);
	return d_minimale;
}

void traitement_bf(FILE *sortie, MatriceDistances matrice)
{
	distance meilleure_distance = brute_force(matrice);
	fprintf(sortie, "Distance minimale : %lf\n", meilleure_distance);
}
