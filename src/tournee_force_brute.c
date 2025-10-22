/*
 */

 #include "traitement_interruption.h"
#include "tournee_force_brute.h"
#include "structures_permutations.h"
#include "tournee_canonique.h"
#include "affichage.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include <stddef.h>
#include <signal.h> 


// fonction auxiliere qui copie un tab d'indices dans un TAD Permutation
void copier_tableau(Permutation permutation, size_t *tabIndices)
{
	for (size_t i = 0; i < nombre_indices(permutation); i++)
	{
		permutation->indices[i] = tabIndices[i];
	}
}



Resultat brute_force(MatriceDistances matrice)
{
    signal(SIGINT, changement_etat); 

    size_t nombre_points = nombre_points_matrice(matrice);
    Permutation permutation_courante = creer_permutation(nombre_points);
    Permutation meilleure_permutation = creer_permutation(nombre_points);

    distance d_courante;
    distance d_minimale;
    distance d_maximal = 0.0; // Initialisation

    bool stop = false;
    bool premiere_permutation = true;

    while (permutation_suivante(permutation_courante) && !stop){      
        
        d_courante = distance_totale_permutation(permutation_courante, matrice);

        if (premiere_permutation) {
            d_minimale = d_courante;
            d_maximal = d_courante;
            copier_tableau(meilleure_permutation, tableau_indices(permutation_courante)); 
            premiere_permutation = false;
        }

        if(flag){
            gerer_interruption_bf(d_courante,d_minimale,meilleure_permutation,permutation_courante,&stop);
        }


        if (d_courante < d_minimale) {
            d_minimale = d_courante;
            copier_tableau(meilleure_permutation, tableau_indices(permutation_courante));
        }

        if (d_courante > d_maximal) {
            d_maximal = d_courante;
        }

    }

    supprimer_permutation(&permutation_courante);
    signal(SIGINT, SIG_DFL);  

    Resultat resultat_final;
    resultat_final.permutation = meilleure_permutation;
    resultat_final.distance = d_minimale;

    return resultat_final;
}

Resultat calcul_tournee_force_brute(MatriceDistances matrice)
{
	return brute_force(matrice);
}
