/*
 * options.c
 */

#include "options.h"

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void options_afficher_aide(char *nom_programme)
{
    printf(
        "Usage : %s -f <fichier d'entrée> -m <méthode> [-o <fichier de sortie>] [-c]\n"
        "   -f <fichier>   Fichier d'entrée (obligatoire)\n"
        "   -m <méthode>   Méthode de calcul (obligatoire)\n"
        "                  Méthodes disponibles : bf, nn, rw, 2optnn, 2optrw, \n"
        "                                         ga, gadpx, all <nombre d'individus> <nombre de générations> <taux de mutation>\n"
        "   -o <fichier>   Fichier de sortie (optionnel)\n"
        "   -c             Tournée canonique (optionnel)\n",
        nom_programme);
}

Methode options_traiter_methode(char *nom)
{
    if (strcmp(nom, "bf") == 0)
    {
        return FORCE_BRUTE;
    }
    if (strcmp(nom, "nn") == 0)
    {
        return PLUS_PROCHE_VOISIN;
    }
    if (strcmp(nom, "rw") == 0)
    {
        return MARCHE_ALEATOIRE;
    }
    if (strcmp(nom, "2optnn") == 0)
    {
        return PLUS_PROCHE_VOISIN_2_OPTIMISATION;
    }
    if (strcmp(nom, "2optrw") == 0)
    {
        return MARCHE_ALEATOIRE_2_OPTIMISATION;
    }
    if (strcmp(nom, "ga") == 0)
    {
        return GENETIQUE_LIGHT;
    }
    if (strcmp(nom, "gadpx") == 0)
    {
        return GENETIQUE_DPX;
    }
    if (strcmp(nom, "all") == 0)
    {
        return TOUTES;
    }

    fprintf(
        stderr,
        "Erreur options_traiter_methode :\n"
        "Méthode de calcul non-reconnue.\n");
    exit(EXIT_FAILURE);
}

size_t options_convertir_chaine_en_size_t(char **argv)
{
    char *fin;

    errno = false;
    size_t valeur = strtoul(argv[optind], &fin, 10);

    if (fin == argv[optind] || errno)
    {
        fprintf(
            stderr,
            "Erreur options_convertir_chaine_en_size_t :\n"
            "Le nombre d'individus et le nombre de générations sont des nombres entiers positifs.\n\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    return valeur;
}

double options_convertir_chaine_en_double(char **argv)
{
    char *fin;

    errno = false;
    double valeur = strtod(argv[optind], &fin);

    if (fin == argv[optind] || errno || valeur < 0 || valeur > 1)
    {
        fprintf(
            stderr,
            "Erreur options_convertir_chaine_en_double :\n"
            "Le taux de mutation est un nombre réel compris entre 0 et 1.\n\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    return valeur;
}

Arguments options_traiter_arguments(int argc, char **argv)
{
    Arguments options;

    options.canonique = false;

    bool fichier_entree_fourni = false;
    bool fichier_sortie_fourni = false;
    bool methode_calcul_fourni = false;

    opterr = 0; /* Gestion des erreurs personnalisée. */

    int option;

    while ((option = getopt(argc, argv, "hf:o:m:c")) != -1)
    {
        switch (option)
        {
        case 'h':
            options_afficher_aide(argv[0]);
            exit(EXIT_SUCCESS);

        case 'f':
            fichier_entree_fourni = true;
            strncpy(options.nom_fichier_entree, optarg, OPTIONS_TAILLE_MAX);
            options.nom_fichier_entree[OPTIONS_TAILLE_MAX - 1] = '\0';
            break;

        case 'o':
            fichier_sortie_fourni = true;
            strncpy(options.nom_fichier_sortie, optarg, OPTIONS_TAILLE_MAX);
            options.nom_fichier_sortie[OPTIONS_TAILLE_MAX - 1] = '\0';
            break;

        case 'm':
            methode_calcul_fourni = true;
            options.methode_calcul = options_traiter_methode(optarg);
            break;

        case 'c':
            options.canonique = true;
            break;

        default:
            fprintf(
                stderr,
                "Erreur options_traiter_arguments :\n"
                "Option non-reconnue.\n\n");
            options_afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (!fichier_entree_fourni || !methode_calcul_fourni)
    {
        fprintf(
            stderr,
            "Erreur options_traiter_arguments :\n"
            "Paramètres obligatoires manquants.\n\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (options.methode_calcul == GENETIQUE_LIGHT ||
        options.methode_calcul == GENETIQUE_DPX ||
        options.methode_calcul == TOUTES)
    {
        if (optind != argc - 3)
        {
            fprintf(
                stderr,
                "Erreur options_traiter_arguments :\n"
                "Trois arguments sont nécessaires pour la méthode génétique.\n\n");
            options_afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }

        options.arguments_genetique.nombre_individus = options_convertir_chaine_en_size_t(argv);
        optind++;
        options.arguments_genetique.nombre_generations = options_convertir_chaine_en_size_t(argv);
        optind++;
        options.arguments_genetique.taux_mutation = options_convertir_chaine_en_double(argv);

        if (options.arguments_genetique.nombre_individus < 3 ||
            options.arguments_genetique.taux_mutation < 0 ||
            options.arguments_genetique.taux_mutation > 1)
        {
            fprintf(
                stderr,
                "Erreur options_traiter_arguments :\n"
                "Il faut au moins trois individus, et le taux de mutation doit être compris entre 0 et 1.\n\n");
            options_afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (optind < argc)
    {
        fprintf(
            stderr,
            "Erreur options_traiter_arguments :\n"
            "Trop d'arguments utilisés.\n\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!fichier_sortie_fourni)
    {
        strcpy(options.nom_fichier_sortie, "");
    }

    return options;
}

FILE *entree;
FILE *sortie;

void fichier_ouvrir_entree(Arguments options)
{
    entree = fopen(options.nom_fichier_entree, "r");

    if (entree == NULL)
    {
        fprintf(
            stderr,
            "Erreur fichier_ouvrir_entree :\n"
            "Échec d'ouverture du fichier '%s'.\n",
            options.nom_fichier_entree);
        exit(EXIT_FAILURE);
    }
}

void fichier_ouvrir_sortie(Arguments options)
{
    sortie = stdout;

    if (strcmp(options.nom_fichier_sortie, "") != 0)
    {
        sortie = fopen(options.nom_fichier_sortie, "w");

        if (sortie == NULL)
        {
            fprintf(
                stderr,
                "Erreur fichier_ouvrir_sortie :\n"
                "Échec d'ouverture du fichier '%s'.\n",
                options.nom_fichier_sortie);
            exit(EXIT_FAILURE);
        }
    }
}

void fichier_fermer_entree(Arguments options)
{
    if (fclose(entree) == EOF)
    {
        fprintf(
            stderr,
            "Erreur fichier_fermer_entree :\n"
            "Échec de fermeture du fichier '%s'.\n",
            options.nom_fichier_entree);
        exit(EXIT_FAILURE);
    }
}
void fichier_fermer_sortie(Arguments options)
{
    if (sortie == stdout)
    {
        return;
    }

    if (fclose(sortie) == EOF)
    {
        fprintf(
            stderr,
            "Erreur fichier_fermer_sortie :\n"
            "Échec de fermeture du fichier '%s'.\n",
            options.nom_fichier_sortie);
        exit(EXIT_FAILURE);
    }
}
