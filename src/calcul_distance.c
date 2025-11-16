/*
 * calcul_distance.c
 */

#include "calcul_distance.h"

#include <stdlib.h>
#include <math.h>

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

distance calculer_distance_euclidienne_modifiee(Point A, Point B)
{
	distance difference_x = A.x - B.x;
	distance difference_y = A.y - B.y;
	distance distance_approchee = hypot(difference_x, difference_y) / RACINE_10;

	distance distance_arrondie = ceil(distance_approchee);

	return distance_arrondie;
}
