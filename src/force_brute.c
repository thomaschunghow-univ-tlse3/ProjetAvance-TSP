/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include  <signal.h>
#include "structures_de_donnees.h"
#include "force_brute.h"
#include "canonique.h"
int i;
void     INThandler(int);


TableauDistances force_brute(TableauPoints tableauPoint, calculer_distance calcul_distance){//
	//signal(SIGINT, INThandler);
	struct sigaction  sigAct;
	sigAct.sa_handler = INThandler;
	if(sigemptyset(&sigAct.sa_mask) == -1){
		perror("sigempty");
		exit(0);
	}
	sigAct.sa_flags = 0;
	
	
	if(sigaction(SIGINT,&sigAct,NULL) == -1){
		perror("sigaction");
		exit(1);
	}
	
	MatriceDistances matrice = creer_matrice(tableauPoint,calcul_distance);
	TableauDistances tournee = tournee_canonique(matrice);
	TableauDistances current = tournee;
	size_t nbPoint = taille_tableau_points(tableauPoint);
	distance dist = somme_tableau_distances(tournee);
	i=0;
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
			i++;
		}
	}
	return tournee;
}


void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     // actions...
     printf("arrêt avec i = %d\n",i);
     printf("OUCH, did you hit Ctrl-C?\n"
            "Do you really want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y'){
       // actions
       printf("sortie avec i = %d\n",i);
       exit(2);
     }
     else{
          printf("Je reprends avec i = %d\n",i);
          signal(SIGINT, INThandler);
        }

     getchar(); // Get new line character
}