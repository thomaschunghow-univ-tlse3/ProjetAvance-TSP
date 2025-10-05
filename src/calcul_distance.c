/*
 *
 */

#include "calcul_distance.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

distance calculer_distance_euclidienne(Point A, Point B)
{
	int retour;
	if((retour = hypot(B.x - A.x, B.y - A.y)) == -1){
		perror("hypothénuse");
		exit(0);
	}
    return retour;
}

double calcul_longitude_latitude(double point){
	double deg = rint(point);
	double minCoor = point - deg;
	return 3.141592 * (deg + 5.0*(minCoor/30)) / 180.0;
}

distance calculer_distance_geographique(Point A, Point B)
{
	Point coordA, coordB;
	
	coordA.x = calcul_longitude_latitude(A.x);//longitude
	coordB.x = calcul_longitude_latitude(B.x);
	
	coordA.y = calcul_longitude_latitude(A.y);//latitude
	coordB.y = calcul_longitude_latitude(B.y);

	double q1 = cos(coordA.x - coordB.x);
	double q2 = cos(coordA.y - coordB.y);
	double q3 = cos(coordA.y + coordB.y);
	
	return (6378.388 * acos( 0.5*((1.0+q1) * q2 - (1.0-q1)*q3) ) + 1.0);
}

distance calculer_distance_euclidienne_modifiee(Point A, Point B){
	double xd = A.x - B.x;
	double yd = A.y - B.y;
	double rij = sqrt( (xd*xd + yd*yd) / 10.0);
	double tij = rint(rij);
	if(tij < rij)
		return tij +1;
	else
		return tij;
}