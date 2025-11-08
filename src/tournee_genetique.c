/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"
#include "traitement_tournee.h"
#include "traitement_interruption.h"

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#define NB_INDIVIDUS_MAX 100
#define PROBA_MUTATION 0.4

struct population{
	
	MatriceDistance mat;
	size_t nb_individus;
	size_t indice_meilleur_distance;
	size_t indice_pire_distance;
	double pMutation;
	Resultat individus[NB_INDIVIDUS_MAX];//utilisation d'un tableau pour stocker les résultats //TODO trouver un moyen d'utiliser un pointeur
};

void population_initialiser(Population population){
	for(size_t i = 0; i< population ->nb_individus;i++){
		population->individus[i] = tournee_marche_aleatoire(population -> mat);
	}
}

void extremum_distance(Population population){
	distance distanceMinimale = population -> individus[0].longueur;
	distance distanceMaximale = distanceMinimale;
	
	for(size_t i=1; i<population -> nb_individus ;i++){
		if(population -> individus[i].longueur>distanceMaximale)
			population -> indice_pire_distance = i;
		if(population -> individus[i].longueur<distanceMinimale)
			population -> indice_meilleur_distance = i;
	}
}

Population population_creer(MatriceDistance matrice, size_t N, double pMutation ){  /*size_t nombre_croisement, size_t nombre_generation*/
	size_t nombre_sommets = matrice_obtenir_nombre_points(matrice);
	Population population = malloc(sizeof(struct population) + (sizeof(Permutation)+nombre_sommets*sizeof(size_t)+sizeof(distance))*N );//+ sizeof(matrice) + sizeof(size_t)*3 + sizeof(pMutation)  + 
	if(population == NULL){
		fprintf(stderr,
			"Erreur population creer :\n"
			"Echec de l'allocation mémoire de la population \n"
		);
	}
	
	population -> mat = matrice;
	population -> pMutation = pMutation;
	population -> nb_individus = N;
	population_initialiser(population);
	extremum_distance(population);
	
	return population;
}



void supprimer_population(Population population){
	for(size_t i = 0; i< population -> nb_individus;i++){
		if(i==population->indice_meilleur_distance)
			printf("tournées de retour : %ld\n",i);
		if(i!=population->indice_meilleur_distance){
			printf("%ld\n",i);
			supprimer_tournee(&population->individus[i]);
		}
		
	}
	
	free(population);
	population = NULL;
	
}

void assert_tournee_meme_longueur(Resultat tournee1, Resultat tournee2){
	assert(tournee1 -> permutation -> nombre_sommets == tournee2 -> permutation -> nombre_sommets);
	(void) tournee1;
	(void) tournee2;
}

Resultat croisement(Resultat tournee1, Resultat tournee2, size_t indice){
	assert_tournee_meme_longueur(tournee1, tournee2);
	Resultat tournee_resultat;
	
	if(indice%2 == 0)
		tournee_resultat = tournee2;
	else
		tournee_resultat = tournee1;
	size_t nbSommet = tournee_nb_sommet(&tournee_resultat);
	for(size_t i=0; i <  nbSommet; i++){
		size_t sommet1 = tournee_sommet_numero(&tournee1,i);
		size_t sommet2 = tournee_sommet_numero(&tournee2,i);
		permutation_echanger_sommets(tournee_resultat.permutation,sommet1,sommet2);/*tournee_resultat->permutation->sommets[i] = sommet1;*/
	}
	
	return tournee_resultat;
	
}



bool determiner_mutation(double proba){ //TODO modifier cette fonction pour qu'elle renvoie une probabilité avec une complexité acceptable et des probabilités équilibrés
	srand(getpid()%NB_INDIVIDUS_MAX);
	double valeur = rand()%NB_INDIVIDUS_MAX;
	if(valeur < 0.0)
		valeur = -valeur;
	while(valeur >= 10.0)
		valeur -= 10.0;
	while(valeur >= 1.0)
		valeur -= 1.0;
	return valeur<proba;
}


Population generation(Population population, size_t indice){
	size_t premier = donner_nombre_aleatoire(0, population -> nb_individus);
	size_t deuxieme = donner_nombre_aleatoire(0, population -> nb_individus);
	while(premier == deuxieme){
		deuxieme = donner_nombre_aleatoire(0, population -> nb_individus);
	}
	Resultat tournee_fille = croisement(population -> individus[premier], population -> individus[deuxieme],indice);
	if(determiner_mutation(population -> pMutation)){
		printf("mutation\n");
		premier = donner_nombre_aleatoire(0, population -> nb_individus);
		deuxieme = donner_nombre_aleatoire(0, population -> nb_individus);
		permutation_echanger_sommets(tournee_fille.permutation,premier,deuxieme);
	}else
		printf("pas de mutation\n");
	tournee_fille.longueur = permutation_calculer_distance_totale(tournee_permutation(&tournee_fille),population -> mat);
	extremum_distance(population);
	population -> individus[population -> indice_pire_distance] = tournee_fille;
	return population;
}

Resultat repeter_croisement(Population population, size_t nbGeneration){
	size_t indiceM = population -> indice_meilleur_distance;
	size_t indiceP = population -> indice_meilleur_distance;
	int stabilite = 0;
	bool demande_stop = false;
	for(size_t i = 0;!demande_stop && i<nbGeneration && stabilite <= 10; i++){
		population = generation(population,i);
		if (interruption)
		{
			double longueur = tournee_longueur(&population -> individus[population -> indice_meilleur_distance]);
			
			Permutation pirePermutation = tournee_permutation(&population -> individus[population -> indice_pire_distance]);
			Permutation meilleurPermutation = tournee_permutation(&population -> individus[population -> indice_meilleur_distance]);
			
            demande_stop = interruption_traitement(pirePermutation, meilleurPermutation, longueur);
        }
		if(indiceM != population -> indice_meilleur_distance || indiceP != population -> indice_meilleur_distance)
			stabilite = 0;
		else
			stabilite++;
		indiceM = population -> indice_meilleur_distance;
		indiceP = population -> indice_meilleur_distance;
		printf("indice %ld stabilite : %d \n",i,stabilite);
		
	}
	return population -> individus[population -> indice_meilleur_distance];
}

Resultat tournee_genetique(MatriceDistance matrice){
	Population population = population_creer(matrice,NB_INDIVIDUS_MAX,PROBA_MUTATION);
	size_t nb_generation=50;
	
	Resultat resultat = repeter_croisement(population,nb_generation);
	//supprimer_population(population); //fonction commentée car elle fait parfois des doubles free TODO régler ce probléme
	return resultat;
}