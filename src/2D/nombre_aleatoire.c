/*
 * nombre_aleatoire.c
 */

#include "nombre_aleatoire.h"

#include <math.h>
#include <stdlib.h>

/* Donne un entier aléatoire compris entre borne_inf et borne_sup exclus.
 * borne_inf <= entier_aleatoire < borne_sup */
size_t donner_entier_aleatoire(size_t borne_inf, size_t borne_sup)
{
    return borne_inf + rand() % (borne_sup - borne_inf);
}

/* Donne un réel aléatoire compris entre borne_inf et borne_sup exclus.
 * borne_inf <= reel_aleatoire < borne_sup */
double donner_reel_aleatoire(double borne_inf, double borne_sup)
{
    return borne_inf + (double)rand() / (double)RAND_MAX * (borne_sup - borne_inf);
}

/* Utilisation de la méthode de Box-Muller.
 * On aimerait avoir un nombre aléatoire qui suit la loi binomiale de probabilité taux de mutation,
 * donc on l'approxime par une loi normale. */
double donner_reel_aleatoire_loi_normale(double probabilite, size_t nombre_tirages)
{
    double a = donner_reel_aleatoire(0, 1);
    double b = donner_reel_aleatoire(0, 1);

    double moyenne = nombre_tirages * probabilite;
    double ecart_type = sqrt(nombre_tirages * probabilite * (1 - probabilite));

    double nombre_aleatoire = sqrt(-2 * log(a)) * cos(2 * M_PI * b);

    return moyenne + ecart_type * nombre_aleatoire;
}
