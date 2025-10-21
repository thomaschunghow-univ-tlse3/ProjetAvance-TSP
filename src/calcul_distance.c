/*
 * calcul_distance.c
 */

#include "calcul_distance.h"

#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define RACINE_10 3.16227766016837952279
#define RAYON_TERRE 6378.388

distance calculer_distance_euclidienne(Point A, Point B)
{
	return hypot(B.x - A.x, B.y - A.y);
}

distance conversion_degres_en_radians(coordonnee coordonnee)
{
	/* On a une coordonnée où la partie entière est les degrés, et la partie décimale les minutes. */

	distance degres = floor(coordonnee);
	distance minutes = coordonnee - degres;

	distance radians = degres * PI / 180;
	radians += minutes * PI * 100 / (180 * 60);

	return radians;
}

distance calculer_distance_geographique(Point A, Point B)
{
	coordonnee latitude_A, longitude_A, latitude_B, longitude_B;

	latitude_A = conversion_degres_en_radians(A.x);
	longitude_A = conversion_degres_en_radians(A.y);

	latitude_B = conversion_degres_en_radians(B.x);
	longitude_B = conversion_degres_en_radians(B.y);

	distance q1 = cos(longitude_A - longitude_B);
	distance q2 = cos(latitude_A - latitude_B);
	distance q3 = cos(latitude_A + latitude_B);

	return ceil(RAYON_TERRE * acos(.5 * ((q2 * (1 + q1) - q3 * (1 - q1)))));
}

distance calculer_distance_euclidienne_modifiee(Point A, Point B)
{
	distance difference_x = A.x - B.x;
	distance difference_y = A.y - B.y;
	distance distance_approchée = hypot(difference_x, difference_y) / RACINE_10;

	distance distance_arrondie = ceil(distance_approchée);

	return distance_arrondie;
}
