/*
 * calcul_distance.c
 */

#include "calcul_distance.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>

#define DIFFERENCE_MINIMALE 1e-5

size_t calculer_factorielle(size_t n)
{
	size_t resultat = 1;
	for (size_t i = 1; i <= n; i++)
	{
		resultat *= i;
	}
	return resultat;
}

distance calculer_distance_euclidienne(Point A, Point B)
{
	return hypot(B.x - A.x, B.y - A.y);
}

void calculer_distance_euclidienne_generique(void *point_A, void *point_B, void *longueur_AB)
{
	Point *A = (Point *)point_A;
	Point *B = (Point *)point_B;
	distance *longueur = (distance *)longueur_AB;

	*longueur = calculer_distance_euclidienne(*A, *B);
}

distance calculer_conversion_degres_en_radians(coordonnee coordonnee)
{
	/* On a une coordonnée où la partie entière est les degrés, et la partie décimale les minutes. */

	distance degres = trunc(coordonnee);
	distance minutes = coordonnee - degres;

	distance radians = degres * PI / 180;
	radians += minutes * PI * 100 / (180 * 60);

	return radians;
}

distance calculer_distance_geographique(Point A, Point B)
{
	coordonnee latitude_A = calculer_conversion_degres_en_radians(A.x);
	coordonnee longitude_A = calculer_conversion_degres_en_radians(A.y);

	coordonnee latitude_B = calculer_conversion_degres_en_radians(B.x);
	coordonnee longitude_B = calculer_conversion_degres_en_radians(B.y);

	distance q1 = cos(longitude_A - longitude_B);
	distance q2 = cos(latitude_A - latitude_B);
	distance q3 = cos(latitude_A + latitude_B);

	return ceil(RAYON_TERRE * acos(.5 * (q2 * (1 + q1) - q3 * (1 - q1))));
}

void calculer_distance_geographique_generique(void *point_A, void *point_B, void *longueur_AB)
{
	Point *A = (Point *)point_A;
	Point *B = (Point *)point_B;
	distance *longueur = (distance *)longueur_AB;

	*longueur = calculer_distance_geographique(*A, *B);
}

distance calculer_distance_euclidienne_modifiee(Point A, Point B)
{
	distance difference_x = A.x - B.x;
	distance difference_y = A.y - B.y;
	distance distance_approchee = hypot(difference_x, difference_y) / RACINE_10;

	distance distance_arrondie = ceil(distance_approchee);

	return distance_arrondie;
}

void calculer_distance_euclidienne_modifiee_generique(void *point_A, void *point_B, void *longueur_AB)
{
	Point *A = (Point *)point_A;
	Point *B = (Point *)point_B;
	distance *longueur = (distance *)longueur_AB;

	*longueur = calculer_distance_euclidienne_modifiee(*A, *B);
}

void distance_additionner(void *distance_A, void *distance_B, void *somme)
{
	distance *A = (distance *)distance_A;
	distance *B = (distance *)distance_B;
	distance *somme_AB = (distance *)somme;

	*somme_AB = *A + *B;
}

void distance_soustraire(void *distance_A, void *distance_B, void *difference)
{
	distance *A = (distance *)distance_A;
	distance *B = (distance *)distance_B;
	distance *difference_AB = (distance *)difference;

	*difference_AB = *A - *B;
}

int distance_comparer(void *distance_A, void *distance_B)
{
	distance difference;

	distance_soustraire(distance_A, distance_B, &difference);

	if (difference < DIFFERENCE_MINIMALE)
	{
		if (difference > -DIFFERENCE_MINIMALE)
		{
			return 0; /* A == B */
		}

		return -1; /* A < B */
	}

	return 1; /* A > B */
}
