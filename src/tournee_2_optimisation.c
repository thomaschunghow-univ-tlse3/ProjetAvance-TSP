/*
 * tournee_2_optimisation.c
 */
#include "structure_point.h"
#include "structure_distance.h"
#include "structure_matrice.h"
#include <math.h>
#include <stdlib.h>

int normalisation(const void *P1, const void *P2){
	const Point *D = malloc(sizeof(Point));
	D = P1;
	const Point *T = malloc(sizeof(Point));
	T = P2;
	return (int) ceil((D->x)*(T->y) - (D->y)*(T->x));
}

/*bool Croisement(Point A, Point B, Point C, Point D){
  Point v1,v2; //utilisation de la structure point pour créer un vecteur
  v1.x = B.x-A.x; //premier vecteur 
  v1.y = B.y-A.y;
  v2.x = C.x - D.x; //deuxiême vecteur
  v2.y = C.y - D.y;
  
  return v1.x*v2.y - v1.y*v2.x==0;
}*/

void recherche_croisement(MatriceDistance matrice){
	
	Point *tableau = matrice_obtenir_adresse_point(matrice);
	qsort(tableau,matrice_obtenir_nombre_points(matrice),sizeof(Point),normalisation);
}