/*
 * calcul_distance.c
 */

#include "calcul_distance.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INVERSE_RACINE_10 0.31622776601683794117

calculer_distance liste_fonctions_calcul[] = {
	calculer_distance_euclidienne,
	calculer_distance_geographique,
	calculer_distance_euclidienne_modifiee};

distance calculer_distance_euclidienne(Point A, Point B)
{
	return hypot(B.x - A.x, B.y - A.y);
}

distance calcul_longitude_latitude(coordonnee point)
{
	double deg = rint(point);
	double minCoor = point - deg;
	return 3.141592 * (deg + 5.0 * (minCoor / 30)) / 180.0;
}

distance calculer_distance_geographique(Point A, Point B)
{
	Point coordA, coordB;

	coordA.x = calcul_longitude_latitude(A.x); // longitude
	coordB.x = calcul_longitude_latitude(B.x);

	coordA.y = calcul_longitude_latitude(A.y); // latitude
	coordB.y = calcul_longitude_latitude(B.y);

	double q1 = cos(coordA.x - coordB.x);
	double q2 = cos(coordA.y - coordB.y);
	double q3 = cos(coordA.y + coordB.y);

	return (6378.388 * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
}

distance calculer_distance_euclidienne_modifiee(Point A, Point B)
{
	distance difference_x = A.x - B.x;
	distance difference_y = A.y - B.y;
	distance distance_approchée = hypot(difference_x, difference_y) * INVERSE_RACINE_10;

	/* Si on change la précision de distance, il faut changer accordément la fonction d'arrondissement supérieur. */
	distance distance_arrondie = ceil(distance_approchée);

	return distance_arrondie;
}
