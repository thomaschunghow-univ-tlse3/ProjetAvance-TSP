/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"
#include "traitement_tournee.h"
#include "nombre_aleatoire.h"
#include "traitement_interruption.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>

#define NB_INDIVIDUS_MAX 500

struct population{
	
	MatriceDistance mat;
	size_t nb_individus;
	size_t indice_meilleur_distance;
	size_t indice_pire_distance;
	double pMutation;
	Resultat individus[NB_INDIVIDUS_MAX];//utilisation d'un tableau pour stocker les résultats //TODO trouver un moyen d'utiliser un pointeur
};

void population_initialiser(Population population){// initialisation des tournées par marche aléatoire
	for(size_t i = 0; i< population ->nb_individus;i++){
		population->individus[i] = tournee_marche_aleatoire(population -> mat);
	}
}

void extremum_distance(Population population){
	distance distanceMinimale = population -> individus[0].longueur;
	distance distanceMaximale = distanceMinimale;
	
	for(size_t i=1; i<population -> nb_individus ;i++){
		if(population -> individus[i].longueur>distanceMaximale){//calcul de l'indice de la pire distance
			population -> indice_pire_distance = i;
			distanceMaximale = population -> individus[i].longueur;
		}
		if(population -> individus[i].longueur<distanceMinimale){//calcul de l'indice de la meilleure distance
			population -> indice_meilleur_distance = i;
			distanceMinimale = population -> individus[i].longueur;
		}
	}
}

Population population_creer(MatriceDistance matrice, size_t N, double pMutation )
{   
	if(N>NB_INDIVIDUS_MAX){
		perror("Trop d'individus pour cette tournée");
		exit(0);
	}
	Population population = malloc(sizeof(struct population) /*+ (sizeof(Permutation) + matrice_obtenir_nombre_points(matrice)*sizeof(size_t))*N*/);
	if(population == NULL)
	{
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

void supprimer_population(Population population)
{
	/*for(size_t i=0; i<population -> nb_individus; i++){
		if(i!=population->indice_meilleur_distance)
			supprimer_tournee(&population -> individus[i]);
	}*/

	free(population);
	population = NULL;
	
}

void assert_tournee_meme_longueur(Resultat tournee1, Resultat tournee2)
{
	assert(tournee1 -> permutation -> nombre_sommets == tournee2 -> permutation -> nombre_sommets);
	(void) tournee1;
	(void) tournee2;
}

Resultat croisement(Resultat tournee1, Resultat tournee2, size_t indice)
{
	assert_tournee_meme_longueur(tournee1, tournee2);
	Resultat tournee_resultat;
	
	if(indice%2 == 0)
		tournee_resultat = tournee2;
	else
		tournee_resultat = tournee1;
	size_t nbSommet = tournee_nb_sommet(&tournee_resultat);
	for(size_t i=0; i <  nbSommet; i++)
	{
		size_t sommet1 = tournee_sommet_numero(&tournee1,i);
		size_t sommet2 = tournee_sommet_numero(&tournee2,i);
		if(sommet1 != sommet2)
			permutation_echanger_sommets(tournee_resultat.permutation,sommet1,sommet2);//échange des sommets de la tournée résultat
	}
	return tournee_resultat;
}

bool determiner_mutation(double proba){
	
	size_t valeur = rand()%100;
	
	return valeur>proba*100;
}

bool sommet_partage(Permutation permutation, size_t sommet1, size_t sommet2)
{
	size_t nbSommet = permutation_obtenir_taille(permutation);
	for(size_t i=0; i<nbSommet;i++)
	{
		if( permutation_obtenir_sommet(permutation,i-1) == sommet1 && permutation_obtenir_sommet(permutation,i) == sommet2)
			return true;//on regarde dans la 2eme permutation si les 2 sommets sont ceux recherchés.
	}
	return false;
}

Permutation calculer_plus_proche_voisin(Permutation permutation, MatriceDistance matrice, size_t indice)
{
	distance longueur;
	distance longueurMinimale = matrice_obtenir_distance(matrice,indice,indice+1);
	size_t indiceMinimum=indice;
	size_t nbSommet = permutation_obtenir_taille(permutation);
	for(size_t i = 0; i<nbSommet;i++)
	{
		if(i!=indice)
		{
			if(i<indice)//calcul des longueurs de l'indice actuel
				longueur = matrice_obtenir_distance(matrice,indice,i);
			else
				longueur = matrice_obtenir_distance(matrice,i,indice);
			if( longueur < longueurMinimale)
			{
				longueurMinimale = longueur;
				indiceMinimum=i;
			}
		}
	}
	permutation_echanger_aretes(permutation,indice,indiceMinimum);
	return permutation;
}

Resultat croisement_DPX(Resultat tournee1, Resultat tournee2, MatriceDistance matrice)
{
	Resultat tournee_resultat = tournee1;
	size_t nbSommet = tournee_nb_sommet(&tournee1);
	Permutation permutation1 = tournee_permutation(&tournee1);
	Permutation permutation2 = tournee_permutation(&tournee2);
	Permutation resultat_permutation = tournee_permutation(&tournee_resultat);
	for(size_t i = 1; i<nbSommet; i++)
	{
		if(!sommet_partage(permutation2,permutation_obtenir_sommet(permutation1,i-1),permutation_obtenir_sommet(permutation1,i)))//si les 2 arêtes ne sont pas présentes dans la tournée 2 alors on remplace par le plus proche voisin
			resultat_permutation = calculer_plus_proche_voisin(resultat_permutation,matrice,i);
	}
	tournee_resultat.permutation=resultat_permutation;
	return tournee_resultat;
}

Population generation(Population population, size_t indice,bool dpx)
{
	size_t premier = donner_entier_aleatoire(0, population -> nb_individus);//choix des tournées parentes
	size_t deuxieme = donner_entier_aleatoire(0, population -> nb_individus);
	while(premier == deuxieme)
	{
		deuxieme = donner_entier_aleatoire(0, population -> nb_individus);
	}
	Resultat tournee_fille;
	if(dpx )//tournée DPX
		tournee_fille = croisement_DPX(population -> individus[premier], population -> individus[deuxieme],population -> mat);
	else//tournée génétique normale
		tournee_fille = croisement(population -> individus[premier], population -> individus[deuxieme],indice);
	if(determiner_mutation(population -> pMutation))
	{// décider s'il y a une mutation ou pas
		printf("mutation\n");
		premier = donner_entier_aleatoire(0, population -> nb_individus);
		deuxieme = donner_entier_aleatoire(0, population -> nb_individus);
		while(premier == deuxieme)
		{
			deuxieme = donner_entier_aleatoire(0, population -> nb_individus);
		}
		permutation_echanger_sommets(tournee_fille.permutation,premier,deuxieme);//echanger 2 sommets aléatoire en cas de mutation
	}
	else
		printf("pas de mutation\n");
	tournee_fille.longueur = permutation_calculer_distance_totale(tournee_permutation(&tournee_fille),population -> mat);//calculer la distance de la nouvelle tournées
	if(tournee_longueur(&tournee_fille) < tournee_longueur(&population -> individus[population -> indice_pire_distance]))
	{
		population -> individus[population -> indice_pire_distance] = tournee_fille;
		extremum_distance(population);
	}
	return population;
}

Resultat repeter_croisement(Population population, size_t nbGeneration,bool dpx){
	size_t indiceM = population -> indice_meilleur_distance;
	size_t indiceP = population -> indice_meilleur_distance;
	int stabilite = 0;
	bool demande_stop = false;
	srand(time(NULL));//initialisation du rand()
	for(size_t i = 0;!demande_stop && stabilite <= 10 && i<nbGeneration; i++){
		population = generation(population,i,dpx);// nouvelle génération
		if (interruption)//interruption par ^C
		{
			double longueur = tournee_longueur(&population -> individus[population -> indice_meilleur_distance]);
			
			Permutation pirePermutation = tournee_permutation(&population -> individus[population -> indice_pire_distance]);
			Permutation meilleurPermutation = tournee_permutation(&population -> individus[population -> indice_meilleur_distance]);
			
            demande_stop = interruption_traitement(pirePermutation, meilleurPermutation, longueur);
        }
		if(indiceM != population -> indice_meilleur_distance || indiceP != population -> indice_meilleur_distance)// verification de la 
			stabilite = 0;//si changement des extrémités réinitialisation de la stabilité
		else
			stabilite++;// sinon incrémentation de la variable stabilité
		indiceM = population -> indice_meilleur_distance;
		indiceP = population -> indice_meilleur_distance;
		printf("indice %ld stabilite : %d \n",i,stabilite);
		
	}
	return population -> individus[population -> indice_pire_distance];
}

Resultat tournee_genetique(MatriceDistance matrice, size_t nbIndividus, size_t nb_generation, double proba){
	Population population = population_creer(matrice,nbIndividus,proba);
	
	Resultat resultat = repeter_croisement(population,nb_generation,false);
	
	supprimer_population(population);
	return resultat;
}

Resultat tournee_genetique_dpx(MatriceDistance matrice, size_t nbIndividus, size_t nb_generation, double proba){
	Population population = population_creer(matrice,nbIndividus,proba);
	
	Resultat resultat = repeter_croisement(population,nb_generation,true);

	supprimer_population(population); 
	return tournee_2_optimisation(matrice,tournee_permutation(&resultat));
}