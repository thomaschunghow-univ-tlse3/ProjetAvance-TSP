/*
 * tournee_genetique.c
 */

#include "tournee_genetique.h"

#include "nombre_aleatoire.h"
#include "structure_matrice.h"
#include "structure_morceau.h"
#include "structure_permutation.h"
#include "structure_tableau_permutation.h"
#include "tournee_2_optimisation.h"

#include <math.h>
#include <stdlib.h>

#ifdef AFFICHAGE_INTERACTIF_GA
#include "affichage.h"
#include "options.h"

#include <stdio.h>
#endif // AFFICHAGE_INTERACTIF_GA

/* DEBUG */
#include "affichage.h"

void tournee_genetique_mutation(TableauPermutation population, double taux_mutation)
{
    size_t nombre_individus = tableau_permutation_obtenir_nombre_permutations(population);

    /* On parcourt tous les individus de la population. */
    for (size_t indice_individu = 0; indice_individu < nombre_individus; indice_individu++)
    {
        Permutation individu = tableau_permutation_obtenir_permutation(population, indice_individu);

        size_t nombre_sommets = permutation_obtenir_nombre_sommets(individu);

        /* Au lieu de parcourir tous les sommets et à chaque sommet tirer une
         * probabilité aléatoire de muter, on tire dès le début le nombre de
         * points que l'on veut muter. En fait, on approxime la loi binomiale par
         * une loi normale. */
        double reel_aleatoire = donner_reel_aleatoire_loi_normale(taux_mutation, nombre_sommets);
        if (reel_aleatoire < 0)
        {
            reel_aleatoire = 0;
        }
        reel_aleatoire /= 2;
        size_t nombre_sommets_a_muter = (size_t)round(reel_aleatoire);
        nombre_sommets_a_muter %= nombre_sommets;

        for (size_t i = 0; i < nombre_sommets_a_muter; i++)
        {
            /* Comme quand on échange deux points, alors deux points sont mutés,
             * donc on doit bien diviser la probabilité par deux. */
            size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
            size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);

            permutation_echanger_sommets(individu, sommet_A, sommet_B);
        }
    }
}

void tournee_genetique_selection_par_tournoi(TableauPermutation population, TableauPermutation parents,
                                             size_t taille_tournoi, DistanceComparer distance_comparer)
{
    size_t nombre_individus = tableau_permutation_obtenir_nombre_permutations(parents);

    for (size_t parent = 0; parent < nombre_individus; parent++)
    {
        /* Sélection de taille_tournoi individus à chaque boucle, puis
         * mémorisation du meilleur du tournoi dans les parents. */
        size_t competiteur = donner_entier_aleatoire(0, nombre_individus);

        size_t gagnant = competiteur;

        for (size_t tournoi = 1; tournoi < taille_tournoi; tournoi++)
        {
            competiteur = donner_entier_aleatoire(0, nombre_individus);

            if (permutation_comparer_longueurs(tableau_permutation_obtenir_permutation(population, competiteur),
                                               tableau_permutation_obtenir_permutation(population, gagnant),
                                               distance_comparer) < 0)
            {
                gagnant = competiteur;
            }
        }

        Permutation tournee_gagnant = tableau_permutation_obtenir_permutation(population, gagnant);
        Permutation tournee_parent = tableau_permutation_obtenir_permutation(parents, parent);
        permutation_copier(tournee_parent, tournee_gagnant);
    }
}

void tournee_genetique_effectuer_croisement_ordonne(Permutation pere, Permutation mere, Permutation enfant,
                                                    Permutation inverse, size_t sommet_A, size_t sommet_B)
{
    size_t nombre_sommets = permutation_obtenir_nombre_sommets(pere);

    if (sommet_B < sommet_A)
    {
        size_t_echanger(&sommet_A, &sommet_B);
    }
    size_t nombre_sommets_pere_herite = sommet_B + 1 - sommet_A;

    /* Le segment copié du père est placé au début de l'enfant. */
    permutation_copier(enfant, pere);
    permutation_decaler(enfant, sommet_A);

    /* On utilise l'inverse (fonctionnel/mathématique, ie. on ne parle pas de
     * renversement de liste) pour avoir accès en O(1) à la position de chaque
     * sommet, en sachant la valeur du sommet de l'enfant. Sinon, il faudrait
     * parcourir la permutation pour retrouver la position d'un sommet, ce qui
     * coûte O(n). */
    permutation_inverser(enfant, inverse);

    /* On remplit le reste de l'enfant avec les sommets restants dans l'ordre de
     * la mère. */
    size_t indice_enfant = nombre_sommets_pere_herite;
    for (size_t indice_mere = 0; indice_mere < nombre_sommets; indice_mere++)
    {
        size_t sommet_mere = permutation_obtenir_sommet(mere, indice_mere);
        size_t indice_sommet_a_echanger = permutation_obtenir_sommet(inverse, sommet_mere);

        if (indice_sommet_a_echanger >= nombre_sommets_pere_herite)
        {
            permutation_echanger_sommets(enfant, indice_sommet_a_echanger, indice_enfant);
            permutation_echanger_sommets(inverse, permutation_obtenir_sommet(enfant, indice_sommet_a_echanger),
                                         permutation_obtenir_sommet(enfant, indice_enfant));
            indice_enfant++;
        }
    }
}

void size_t_incrementer(size_t *valeur, size_t intervalle)
{
    *valeur = (*valeur + 1) % intervalle;
}

void size_t_decrementer(size_t *valeur, size_t intervalle)
{
    *valeur = (*valeur + intervalle - 1) % intervalle;
}

void tournee_genetique_calculer_morceaux(Permutation permutation_A, Permutation permutation_B, Permutation inverse_B,
                                         TableauMorceau morceaux)
{
    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation_A);

    size_t nombre_morceaux = 0;

    size_t indice_morceau = 0;

    size_t morceau_nombre_sommets;

    for (size_t sommet = 0; sommet < nombre_sommets; sommet += morceau_nombre_sommets)
    {
        morceau_nombre_sommets = 1;

        size_t sommet_homologue =
            permutation_obtenir_sommet(inverse_B, permutation_obtenir_sommet(permutation_A, sommet));

        size_t sommet_suivant = sommet + 1;
        if (sommet_suivant >= nombre_sommets)
        {
            tableau_morceau_modifier_morceau(morceaux, indice_morceau, morceau_nombre_sommets, sommet,
                                             sommet + morceau_nombre_sommets - 1);
            indice_morceau++;
            nombre_morceaux++;
            break;
        }

        size_t voisin_droit_du_sommet_homologue = sommet_homologue;
        size_t_incrementer(&voisin_droit_du_sommet_homologue, nombre_sommets);

        size_t voisin_gauche_du_sommet_homologue = sommet_homologue;
        size_t_decrementer(&voisin_gauche_du_sommet_homologue, nombre_sommets);

        if (permutation_obtenir_sommet(permutation_A, sommet_suivant) ==
            permutation_obtenir_sommet(permutation_B, voisin_droit_du_sommet_homologue))
        {
            while (morceau_nombre_sommets < nombre_sommets &&
                   permutation_obtenir_sommet(permutation_A, sommet_suivant) ==
                       permutation_obtenir_sommet(permutation_B, voisin_droit_du_sommet_homologue))
            {
                morceau_nombre_sommets++;
                sommet_suivant++;
                if (sommet_suivant >= nombre_sommets)
                {
                    break;
                }

                size_t_incrementer(&voisin_droit_du_sommet_homologue, nombre_sommets);
            }
        }

        else if (permutation_obtenir_sommet(permutation_A, sommet_suivant) ==
                 permutation_obtenir_sommet(permutation_B, voisin_gauche_du_sommet_homologue))
        {
            while (morceau_nombre_sommets < nombre_sommets &&
                   permutation_obtenir_sommet(permutation_A, sommet_suivant) ==
                       permutation_obtenir_sommet(permutation_B, voisin_gauche_du_sommet_homologue))
            {
                morceau_nombre_sommets++;
                sommet_suivant++;
                if (sommet_suivant >= nombre_sommets)
                {
                    break;
                }

                size_t_decrementer(&voisin_gauche_du_sommet_homologue, nombre_sommets);
            }
        }

        tableau_morceau_modifier_morceau(morceaux, indice_morceau, morceau_nombre_sommets, sommet,
                                         sommet + morceau_nombre_sommets - 1);
        indice_morceau++;
        nombre_morceaux++;
    }

    tableau_morceau_modifier_nombre_morceaux(morceaux, nombre_morceaux);
}

void tournee_genetique_raccorder_morceaux(MatriceDistance matrice, Permutation permutation, TableauMorceau morceaux)
{
    size_t nombre_morceaux = tableau_morceau_obtenir_nombre_morceaux(morceaux);

    size_t nombre_sommets = permutation_obtenir_nombre_sommets(permutation);

    for (size_t indice_morceau = 0; indice_morceau < nombre_morceaux - 1; indice_morceau++)
    {
        size_t sommet_a_raccorder = tableau_morceau_obtenir_sommet_droit(morceaux, indice_morceau);

        size_t indice_morceau_plus_proche = indice_morceau + 1;
        size_t voisin_plus_proche = tableau_morceau_obtenir_sommet_gauche(morceaux, indice_morceau_plus_proche);
        Direction direction = GAUCHE;

        for (size_t indice_morceau_suivant = indice_morceau + 1; indice_morceau_suivant < nombre_morceaux;
             indice_morceau_suivant++)
        {
            size_t voisin = tableau_morceau_obtenir_sommet_droit(morceaux, indice_morceau_suivant);

            if (matrice_comparer_distances(matrice, permutation_obtenir_sommet(permutation, sommet_a_raccorder),
                                           permutation_obtenir_sommet(permutation, voisin),
                                           permutation_obtenir_sommet(permutation, sommet_a_raccorder),
                                           permutation_obtenir_sommet(permutation, voisin_plus_proche)) < 0)
            {
                voisin_plus_proche = voisin;
                indice_morceau_plus_proche = indice_morceau_suivant;
                direction = DROITE;
            }

            voisin = tableau_morceau_obtenir_sommet_gauche(morceaux, indice_morceau_suivant);

            if (matrice_comparer_distances(matrice, permutation_obtenir_sommet(permutation, sommet_a_raccorder),
                                           permutation_obtenir_sommet(permutation, voisin),
                                           permutation_obtenir_sommet(permutation, sommet_a_raccorder),
                                           permutation_obtenir_sommet(permutation, voisin_plus_proche)) < 0)
            {
                voisin_plus_proche = voisin;
                indice_morceau_plus_proche = indice_morceau_suivant;
                direction = GAUCHE;
            }
        }

        size_t nombre_decalages_gauches =
            tableau_morceau_obtenir_sommet_gauche(morceaux, indice_morceau_plus_proche) - (sommet_a_raccorder + 1);

        permutation_decaler_morceau(permutation, nombre_decalages_gauches, sommet_a_raccorder + 1, nombre_sommets - 1);

        tableau_morceau_decaler_morceau(morceaux, indice_morceau + 1, nombre_morceaux - 1, nombre_decalages_gauches,
                                        sommet_a_raccorder + 1, nombre_sommets - 1,
                                        indice_morceau_plus_proche - indice_morceau - 1);

        if (direction == DROITE)
        {
            size_t sommet_droit_morceau =
                sommet_a_raccorder + tableau_morceau_obtenir_nombre_sommets(morceaux, indice_morceau_plus_proche);

            permutation_renverser_morceau(permutation, sommet_a_raccorder + 1, sommet_droit_morceau);
        }
    }
}

void tournee_genetique_effectuer_croisement_dpx(Permutation pere, Permutation mere, Permutation enfant,
                                                Permutation inverse, MatriceDistance matrice, TableauMorceau morceaux)
{
    size_t nombre_sommets = permutation_obtenir_nombre_sommets(pere);

    permutation_copier(enfant, pere);

    permutation_inverser(mere, inverse);

    tableau_morceau_modifier_nombre_morceaux(morceaux, nombre_sommets + 1);

    /* Initialisation à zéro. */
    for (size_t i = 0; i < nombre_sommets; i++)
    {
        tableau_morceau_modifier_morceau(morceaux, i, 0, 0, 0);
    }

    tournee_genetique_calculer_morceaux(enfant, mere, inverse, morceaux);

    tournee_genetique_raccorder_morceaux(matrice, enfant, morceaux);

    /* Par souci d'optimisation, on passe l'inverse dans la 2-optimisation pour
     * éviter d'avoir à allouer de la mémoire puis de la libérer. Cela ne pose
     * pas de problème car l'inverse a terminé son rôle et sera recalculé à la
     * prochaine boucle. */
    // tournee_2_optimisation(matrice, inverse, enfant);
}

void tournee_genetique(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations,
                       double taux_mutation, size_t taille_tournoi, GenetiqueVariante variante,
                       TableauPermutation population, TableauPermutation enfants, TableauPermutation parents,
                       Permutation inverse, Permutation meilleur_individu_historique, TableauMorceau morceaux)
{
#ifdef AFFICHAGE_INTERACTIF_GA
    fprintf(sortie, "genetique\n%ld\n%ld\n%lf\n%ld\n", nombre_individus, nombre_generations, taux_mutation,
            taille_tournoi);
#endif // AFFICHAGE_INTERACTIF_GA

    size_t nombre_sommets = matrice_obtenir_nombre_points(matrice);

    DistanceComparer distance_comparer = matrice_obtenir_distance_comparer(matrice);

    /* Initialisation de la population initiale. */
    for (size_t i = 0; i < nombre_individus; i++)
    {
        Permutation individu = tableau_permutation_obtenir_permutation(population, i);
        permutation_melanger(individu);
        permutation_calculer_longueur(individu, matrice);
    }

    /* Initialisation du meilleur individu historique,
     * c'est-à-dire du meilleur individu parmi toutes les générations confondues.
     */

    size_t indice_meilleur_individu =
        tableau_permutation_trouver_meilleur_individu(population, matrice_obtenir_distance_comparer(matrice));
    Permutation meilleur_individu = tableau_permutation_obtenir_permutation(population, indice_meilleur_individu);
    permutation_copier(meilleur_individu_historique, meilleur_individu);
    permutation_calculer_longueur(meilleur_individu_historique, matrice);

#ifdef AFFICHAGE_INTERACTIF_GA
    for (size_t individu = 0; individu < nombre_individus; individu++)
    {
        Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
        afficher_permutation(sortie, permutation, 0);
        fprintf(sortie, "\n");
    }
#endif // AFFICHAGE_INTERACTIF_GA

    for (size_t generation = 0; generation < nombre_generations; generation++)
    {
        /* Détermination des parents grace à une sélection par tournoi. */
        tournee_genetique_selection_par_tournoi(population, parents, taille_tournoi, distance_comparer);

        switch (variante)
        {
        case LIGHT:
            for (size_t indice_enfant = 0; indice_enfant < nombre_individus / 2; indice_enfant++)
            {
                /* Remarque : si le nombre d'individus est impair, alors le
                 * dernier individu du tournoi ne se reproduit pas. */
                indice_enfant *= 2;
                size_t indice_pere = indice_enfant;
                size_t indice_mere = indice_pere + 1;
                size_t indice_frere = indice_pere;
                size_t indice_soeur = indice_mere;

                /* Sélection de deux parents... */
                Permutation pere = tableau_permutation_obtenir_permutation(parents, indice_pere);
                Permutation mere = tableau_permutation_obtenir_permutation(parents, indice_mere);

                /* ...qui se reproduisent pour créer deux enfants. */
                Permutation frere = tableau_permutation_obtenir_permutation(enfants, indice_frere);
                Permutation soeur = tableau_permutation_obtenir_permutation(enfants, indice_soeur);

                /* Croisements entre les deux parents. */
                size_t sommet_A = donner_entier_aleatoire(0, nombre_sommets);
                size_t sommet_B = donner_entier_aleatoire(0, nombre_sommets);
                tournee_genetique_effectuer_croisement_ordonne(pere, mere, frere, inverse, sommet_A, sommet_B);

                sommet_A = donner_entier_aleatoire(0, nombre_sommets);
                sommet_B = donner_entier_aleatoire(0, nombre_sommets);
                tournee_genetique_effectuer_croisement_ordonne(pere, mere, soeur, inverse, sommet_A, sommet_B);
            }
            break;

        case DPX:
            for (size_t indice_enfant = 0; indice_enfant < nombre_individus - 1; indice_enfant++)
            {
                /* Remarque : si le nombre d'individus est impair, alors le
                 * dernier individu du tournoi ne se reproduit pas. */
                size_t indice_pere = indice_enfant;
                size_t indice_mere = indice_pere + 1;

                /* Sélection de deux parents... */
                Permutation pere = tableau_permutation_obtenir_permutation(parents, indice_pere);
                Permutation mere = tableau_permutation_obtenir_permutation(parents, indice_mere);

                Permutation enfant = tableau_permutation_obtenir_permutation(enfants, indice_enfant);

                tournee_genetique_effectuer_croisement_dpx(pere, mere, enfant, inverse, matrice, morceaux);
            }
            break;
        }

        /* Mutation de tous les enfants. */
        tournee_genetique_mutation(enfants, taux_mutation);

        /* Les enfants sont nés de croisements et ont été mutés,
         * donc la longueur de leur tournée doit être recalculée. */
        for (size_t indice_enfant = 0; indice_enfant < nombre_individus; indice_enfant++)
        {
            Permutation enfant = tableau_permutation_obtenir_permutation(enfants, indice_enfant);
            permutation_calculer_longueur(enfant, matrice);
        }

        /* Tri des enfants. */
        tableau_permutation_trier(enfants, distance_comparer);

        /* Remplacement du pire individu de cette génération
         * par un nouvel individu créé par marche aléatoire. */
        size_t indice_pire_individu = nombre_individus - 1;
        Permutation pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_melanger(pire_individu);
        permutation_calculer_longueur(pire_individu, matrice);

        /* Comparaison du meilleur individu de cette génération au meilleur
         * individu historique. */
        indice_meilleur_individu = 0;
        meilleur_individu = tableau_permutation_obtenir_permutation(enfants, indice_meilleur_individu);

        if (permutation_comparer_longueurs(meilleur_individu, meilleur_individu_historique, distance_comparer) < 0)
        {
            /* Mise à jour du meilleur individu historique. */
            permutation_copier(meilleur_individu_historique, meilleur_individu);
        }

        /* Remplacement du second pire individu de cette génération par le
         * meilleur individu historique. */
        indice_pire_individu = nombre_individus - 2;
        pire_individu = tableau_permutation_obtenir_permutation(enfants, indice_pire_individu);
        permutation_copier(pire_individu, meilleur_individu_historique);

        /* Remplacement de la population par ses enfants. */
        tableau_permutation_echanger_tableaux(&population, &enfants);

#ifdef AFFICHAGE_INTERACTIF_GA
        tableau_permutation_trier(population, distance_comparer);
        for (size_t individu = 0; individu < nombre_individus; individu++)
        {
            Permutation permutation = tableau_permutation_obtenir_permutation(population, individu);
            afficher_permutation(sortie, permutation, 0);
            fprintf(sortie, "\n");
        }
#endif // AFFICHAGE_INTERACTIF_GA
    }
}

void tournee_genetique_light(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations,
                             double taux_mutation, size_t taille_tournoi, Permutation permutation_resultat,
                             TableauPermutation population, TableauPermutation enfants, TableauPermutation parents,
                             Permutation inverse)
{
    tournee_genetique(matrice, nombre_individus, nombre_generations, taux_mutation, taille_tournoi, LIGHT, population,
                      enfants, parents, inverse, permutation_resultat, NULL);
}

void tournee_genetique_dpx(MatriceDistance matrice, size_t nombre_individus, size_t nombre_generations,
                           double taux_mutation, size_t taille_tournoi, Permutation permutation_resultat,
                           TableauPermutation population, TableauPermutation enfants, TableauPermutation parents,
                           Permutation inverse, TableauMorceau morceaux)
{
    tournee_genetique(matrice, nombre_individus, nombre_generations, taux_mutation, taille_tournoi, DPX, population,
                      enfants, parents, inverse, permutation_resultat, morceaux);
}
