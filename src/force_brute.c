/*
 *force_brute.c
 */
#include "force_brute.h"
#include "structures_de_donnees.h"
#include "canonique.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h>

/*
 * calcule la permutation suivante de l'ordre lexicographique
 * et renvoie un boolean qui montre si la permutation suivante existe
 */
bool permutation_suivante(TableauIndices *tableau_indices)
{
	// trouver le suffix non croissant
	if (tableau_indices->taille == 0)
		return false;
	size_t i = tableau_indices->taille - 1;
	while (i > 0 && (tableau_indices->indices)[i - 1] >= (tableau_indices->indices)[i])
		i--;
	if (i == 0)
		return false;

	// trouver le successeur du pivot
	size_t j = tableau_indices->taille - 1;
	while ((tableau_indices->indices)[j] <= (tableau_indices->indices)[i - 1])
		j--;

	echanger_indices(tableau_indices, i - 1, j);

	// inverser le suffix
	j = tableau_indices->taille - 1;
	while (i < j)
	{
		echanger_indices(tableau_indices, i, j);
		i++;
		j--;
	}
	return true;
}

// TODO : brute force renvoie la permutation
distance brute_force(MatriceDistances matrice)
{
	size_t nombre_points = nombre_points_matrice(matrice);
	TableauIndices *permutation_courante = creer_tableau_indices(nombre_points);

	distance d_courante = distance_totale_sequence(permutation_courante, matrice);
	distance d_minimale = d_courante;
	printf("%lf\n", d_courante);

	printf("%lf\n", d_minimale);

	while (permutation_suivante(permutation_courante))
	{
		distance d_courante = distance_totale_sequence(permutation_courante, matrice);
		if (d_courante < d_minimale)
		{
			d_minimale = d_courante;
		}
	}
	supprimer_tableau_indices(permutation_courante);
	return d_minimale;
}

void traitement_bf(FILE *sortie, MatriceDistances matrice)
{
	distance meilleure_distance = brute_force(matrice);
	fprintf(sortie, "Distance minimale : %lf\n", meilleure_distance);
}
