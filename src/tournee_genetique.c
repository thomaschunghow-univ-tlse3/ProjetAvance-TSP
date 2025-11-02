/*
 * tournee_genetique.c
 */

#include <stdlib.h>
#include <unistd.h>

#include "tournee_genetique.h"

//#define NB_INDIVIDUS 100

struct population{
	MatriceDistance mat;
	Resultat* individus;
	size_t nb_individus;
	size_t indice_meilleur_distance;
	double pMutation;
};

void population_initialiser(Population population){
	for(size_t i = 0; i< population -> nb_individus;i++){
		population -> individus[i] = tournee_marche_aleatoire(population -> mat);
	}
}

size_t pire_distance(Population population){
	distance distanceMaximale = population -> individus[0].longueur;
	distance distanceMinimale = distanceMaximale;
	size_t indice = 0;
	for(size_t i=1; i<population -> nb_individus ;i++){
		if(population -> individus[i].longueur > distanceMaximale){
			distanceMaximale = population -> individus[i].longueur;
			indice = i;
		}
		if(population -> individus[i].longueur<distanceMinimale)
			population -> indice_meilleur_distance = i;
	}
	return indice;
}

Population population_creer(MatriceDistance matrice, size_t N, double pMutation ){  /*size_t nombre_croisement, size_t nombre_generation*/
	Population population = malloc(sizeof(matrice) + N*sizeof(Resultat) + 2*sizeof(size_t) + sizeof(double));
	
	population -> mat = matrice;
	population -> pMutation = pMutation;
	population -> nb_individus = N;
	population_initialiser(population);
	pire_distance(population);
	return population;
}



void supprimer_population(Population population){
	
	for(size_t i = 0; i< population -> nb_individus;i++){
		supprimer_tournee(&population->individus[i]);
	}
	free(population);
	population = NULL;
}

Resultat croisement(Resultat tournee1, Resultat tournee2){
	//TODO
	(void) tournee1;
	return tournee2;
	//(void) tournee2;
	
}



bool determiner_mutation(double proba){
	srand(getpid());
	double valeur = rand()/proba;
	while(valeur>1.0)
		valeur -=1.0;
	return valeur>=proba;
}

Population generation(Population population){
	size_t premier = donner_nombre_aleatoire(0, population -> nb_individus);
	size_t deuxieme = donner_nombre_aleatoire(0, population -> nb_individus);
	while(premier == deuxieme){
		deuxieme = donner_nombre_aleatoire(0, population -> nb_individus);
	}
	Resultat tournee_fille = croisement(population -> individus[premier], population -> individus[deuxieme]);
	if(determiner_mutation(population -> pMutation))
		tournee_fille = tournee_marche_aleatoire(population -> mat);
	size_t indice_pire_distance = pire_distance(population);
	population -> individus[indice_pire_distance] = tournee_fille;
	return population;
}

Resultat repeter_croisement(Population population, size_t nbGeneration){
	size_t indice = pire_distance(population);
	int stabilite = 0;
	for(size_t i = 0; i<nbGeneration && stabilite <= 10; i++){
		population = generation(population);
		if(indice != population -> indice_meilleur_distance)
			stabilite = 0;
		else
			stabilite++;
	}
	return population -> individus[population -> indice_meilleur_distance];
}