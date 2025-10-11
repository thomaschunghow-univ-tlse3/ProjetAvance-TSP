/*
 *
 */
#include <stdio.h>
#include "structures_de_donnees.h"
#include "force_brute.h"
#include "canonique.h"

TableauDistances force_brute(TableauPoints tableauPoint, calculer_distance calcul_distance){
	MatriceDistances matrice = creer_matrice(tableauPoint,calcul_distance);
	TableauDistances tournee = tournee_canonique(matrice);
	TableauDistances current = tournee;
	size_t nbPoint = taille_tableau_points(tableauPoint);
	distance dist = somme_tableau_distances(tournee);
	for(size_t ligne = 0 ; ligne < nbPoint; ligne++){
		size_t distanceActuelle;
		for(size_t colonne = 0 ; colonne < ligne; colonne++){
			echangerPoint(matrice,ligne,colonne);
			if(ligne != colonne){
				current = tournee_canonique(matrice);
				distanceActuelle=somme_tableau_distances(current);
				if(distanceActuelle<dist){
					dist = distanceActuelle;
					tournee = current;
				}
			}
			
		}
	}
	return tournee;
}