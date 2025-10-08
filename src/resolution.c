/*
 * Résolution du problème du voyageur de commerce.
 */

#include "structures_de_donnees.h"
#include "calcul_distance.h"
#include "lecture_donnees.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char **argv)
{
	char *nom_fichier ;//argv[1];
	if(argc == 2){
		char data[30] = "data/"; 
		
		nom_fichier = strcat(data,argv[1]);//strcat(char *dest,char *src) pour concaténer 2 chaines
		//printf("pensez à placer data/ avant le nom de fichier.\n");
	}
	else if(argc>2){
		perror("choisissez un seul fichier");
		exit(1);
	}else
		nom_fichier = "data/rat783.tsp";
		
    /*(void)argc;
    (void)argv;*/

    // EXEMPLE
    Specification specification = lire_specification_tsp(nom_fichier);
    TableauPoints tableau_points = creer_tableau_points(specification.nombre_points);
    lire_points_tsp(nom_fichier, tableau_points);
	MatriceDistances matrice; //déterminisme du calcul
	if(strcmp(specification.type_distance,"GEO"))//distance géographique
		matrice = creer_matrice(tableau_points, calculer_distance_geographique);
	else if(strcmp(specification.type_distance,"EUC_2D"))//distance euclidienne
		matrice = creer_matrice(tableau_points, calculer_distance_euclidienne);
	else if(strcmp(specification.type_distance,"ATT"))//distance euclidienne modifiee
		matrice = creer_matrice(tableau_points, calculer_distance_euclidienne_modifiee);
	else//distance euclidienne par défaut dans les autres cas
		matrice = creer_matrice(tableau_points, calculer_distance_euclidienne);
    
    remplir_matrice(matrice);
    afficher_specification(specification);
    afficher_liste_points(tableau_points);
	
	Point point;
	point.x = 191.0; point.y = 200.0; 
	changerPoint(matrice, point, 279);
	
    afficher_matrice(matrice);
    supprimer_matrice(&matrice);
	
    return EXIT_SUCCESS;
}
