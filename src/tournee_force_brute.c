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

// fonction auxiliere qui copie un tab d'indices dans un TAD Permutation
void copier_tableau(Permutation permutation, size_t *tabIndices)
{
	for (size_t i = 0; i < nombreIndices(permutation); i++)
	{
		permutation->indices[i] = tabIndices[i];
	}
}

Permutation brute_force(MatriceDistances matrice)
{
	size_t nombre_points = nombre_points_matrice(matrice);
	Permutation permutation_courante = creer_permutation(nombre_points);
	Permutation meilleure_permutation = creer_permutation(nombre_points);

	distance d_courante = distance_totale_permutation(permutation_courante, matrice);
	distance d_minimale = d_courante;

	while (permutation_suivante(permutation_courante))
	{
		distance d_courante = distance_totale_permutation(permutation_courante, matrice);
		if (d_courante < d_minimale)
		{
			d_minimale = d_courante;
			copier_tableau(meilleure_permutation, tabIndices(permutation_courante));
		}
	}

	supprimer_permutation(&permutation_courante);
	return meilleure_permutation;
}

Resultat calcul_tournee_force_brute(MatriceDistances matrice)
{
	Permutation meilleure_permutation = brute_force(matrice);
	distance meilleure_distance = distance_totale_permutation(meilleure_permutation, matrice);

	Resultat resultat;
	resultat.permutation = meilleure_permutation;
	resultat.distance = meilleure_distance;

	return resultat;
}
