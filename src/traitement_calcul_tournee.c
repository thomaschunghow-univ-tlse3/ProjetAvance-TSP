/*
 */

#include "traitement_calcul_tournee.h"
#include "affichage.h"
#include "tournee_canonique.h"
#include "tournee_force_brute.h"

#include <time.h>

FonctionTraitement liste_fonctions_traitement[] = {
    &calcul_tournee_canonique,   // TODO : Remplacer par les bonnes fonctions quand c'est implémenté.
    &calcul_tournee_force_brute, // &calcul_tournee_force_brute,
    &calcul_tournee_canonique,   // &calcul_tournee_plus_proche_voisin,
    &calcul_tournee_canonique,   // &calcul_tournee_marche_aleatoire,
    &calcul_tournee_canonique,   // &calcul_tournee_2_optimisation_plus_proche_voisin,
    &calcul_tournee_canonique,   // &calcul_tournee_2_optimisation_marche_aleatoire,
    &calcul_tournee_canonique,   // &calcul_tournee_genetique_generique,
    &calcul_tournee_canonique,   // &calcul_tournee_genetique_dpx,
};

void traitement(FILE *sortie, char *nom_fichier, MethodeCalcul methode, MatriceDistances matrice)
{
    clock_t temps = clock();

    FonctionTraitement fonction_traitement = liste_fonctions_traitement[methode];
    Resultat resultat = fonction_traitement(matrice);

    temps = clock() - temps;
    double temps_total = (double)temps;
    temps_total /= CLOCKS_PER_SEC;

    afficher_tournee(sortie, nom_fichier, methode, temps_total, resultat.distance, resultat.permutation);
}
