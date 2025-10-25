/*
 * tournee_2_optimisation.c
 */
#include "structure_point.h"
#include "structure_distance.h"
#include "structure_matrice.h"
#include "tournee_2_optimisation.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

Point *tableau;
size_t nbPoint;

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

bool equals(Point P1,Point P2){
	return P1.x == P2.x && P1.y == P2.y;
}

int parcours_tableau(const void *P1, const void *P2){
	const Point *D = malloc(sizeof(Point));
	D = P1;
	const Point *T = malloc(sizeof(Point));
	T = P2;
	size_t indice = 1;
	Point v1,v2;
	v1.x = D->x-T->x; //premier vecteur 
	v1.y = D->y-T->y;
	Point current;
	int comparaison = 0;int comparaisonMax = 0;
	Point next = tableau[0];
	while(indice < nbPoint){
		current = next;
		next = tableau[indice];
		if(!equals(current,*D) && !equals(next,*T) && !equals(current,*T) && !equals(next,*D)){
			v2.x = current.x - next.x; //deuxiême vecteur
			v2.y = current.y - next.y;
			comparaison = ceil(v1.x*v2.y - v1.y*v2.x);
			if(comparaisonMax < abs(comparaison))
				comparaisonMax = comparaison;
		}
		indice++;
	} 

	return (int) comparaisonMax;
}

void recherche_croisement(MatriceDistance matrice, compar comparateur){
	tableau = matrice_obtenir_adresse_point(matrice);
	nbPoint = matrice_obtenir_nombre_points(matrice);//void qsort(void *base, size_t nmemb, size_t size,int (*compar)(const void *, const void *));
	qsort(tableau,matrice_obtenir_nombre_points(matrice),sizeof(Point),comparateur);
}