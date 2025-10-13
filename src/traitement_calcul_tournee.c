/*
 */

#include "traitement_calcul_tournee.h"
#include "affichage.h"

#include <time.h>

void traitement(FILE *sortie, FonctionTraitement fonction_traitement, Options options, MatriceDistances matrice)
{
    clock_t temps = clock();
    Resultat resultat = fonction_traitement(matrice);
    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;
    distance distance_totale = 0; // TODO
    afficher_tournee(sortie, options.nom_fichier_entree, options.methode_calcul, temps_total, distance_totale, resultat);
}
