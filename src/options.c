/*
 * options.c
 */

#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>

void options_afficher_aide(char *nom_programme)
{
    printf("Usage : %s -f <fichier d'entrée> -m <méthode> [-o <fichier de sortie>] [-c]\n"
           "   -f <fichier>   Fichier d'entrée (obligatoire)\n"
           "   -m <méthode>   Méthode de calcul (obligatoire)\n"
           "                  Méthodes disponibles : bf, nn, rw, 2optnn, 2optrw, \n"
           "                                         ga, gadpx, all <nombre d'individus> <nombre de générations> <taux de mutation>\n"
           "   -o <fichier>   Fichier de sortie (optionnel)\n"
           "   -c             Tournée canonique (optionnel)\n",
           nom_programme);
}

MethodeCalcul options_traitement_methode_calcul(char *nom)
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
        return GENETIQUE_GENERIQUE;
    }
    if (strcmp(nom, "gadpx") == 0)
    {
        return GENETIQUE_DPX;
    }
    if (strcmp(nom, "all") == 0)
    {
        return TOUTES;
    }

    fprintf(stderr,
            "Erreur options_traitement_methode_calcul :\n"
            "Méthode de calcul non-reconnue.\n");
    exit(EXIT_FAILURE);
}

size_t options_convertir_chaine_en_size_t(char **argv)
{
    errno = false;
    char *fin;
    size_t valeur = strtoul(argv[optind], &fin, 10);

    if (fin == argv[optind] || errno)
    {
        fprintf(stderr,
                "Erreur options_convertir_chaine_en_size_t :\n"
                "Le nombre d'individus et le nombre de générations sont des nombres entiers positifs.\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    return valeur;
}

double options_convertir_chaine_en_double(char **argv)
{
    errno = false;
    char *fin;
    double valeur = strtod(argv[optind], &fin);

    if (fin == argv[optind] || errno || valeur < 0 || valeur > 1)
    {
        fprintf(stderr,
                "Erreur options_convertir_chaine_en_double :\n"
                "Le taux de mutation est un nombre réel compris entre 0 et 1.\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    return valeur;
}

Options options_traitement(int argc, char **argv)
{
    Options options;

    options.canonique = false;

    bool fichier_entree_fourni = false;
    bool fichier_sortie_fourni = false;
    bool methode_calcul_fourni = false;

    opterr = 0; /* Gestion des erreurs personnalisée. */

    int opt;

    while ((opt = getopt(argc, argv, "hf:o:m:c")) != -1)
    {
        switch (opt)
        {
        case 'h':
            options_afficher_aide(argv[0]);
            exit(EXIT_SUCCESS);

        case 'f':
            fichier_entree_fourni = true;
            strncpy(options.nom_fichier_entree, optarg, TAILLE_OPTIONS_MAX);
            options.nom_fichier_entree[TAILLE_OPTIONS_MAX - 1] = '\0';
            break;

        case 'o':
            fichier_sortie_fourni = true;
            strncpy(options.nom_fichier_sortie, optarg, TAILLE_OPTIONS_MAX);
            options.nom_fichier_sortie[TAILLE_OPTIONS_MAX - 1] = '\0';
            break;

        case 'm':
            methode_calcul_fourni = true;
            options.methode_calcul = options_traitement_methode_calcul(optarg);
            break;

        case 'c':
            options.canonique = true;
            break;

        default:
            fprintf(stderr,
                    "Erreur options_traitement :\n"
                    "Option non-reconnue.\n");
            options_afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (!fichier_entree_fourni || !methode_calcul_fourni)
    {
        fprintf(stderr,
                "Erreur options_traitement :\n"
                "Paramètres obligatoires manquants.\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (options.methode_calcul == GENETIQUE_GENERIQUE || options.methode_calcul == GENETIQUE_DPX || options.methode_calcul == TOUTES)
    {
        if (optind != argc - 3)
        {
            fprintf(stderr,
                    "Erreur options_traitement :\n"
                    "Trois arguments sont nécessaire pour la méthode génétique.\n");
            options_afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }

        options.arguments_genetique.nombre_individus = options_convertir_chaine_en_size_t(argv);
        optind++;
        options.arguments_genetique.nombre_generations = options_convertir_chaine_en_size_t(argv);
        optind++;
        options.arguments_genetique.taux_mutation = options_convertir_chaine_en_double(argv);
    }
    else if (optind < argc)
    {
        fprintf(stderr,
                "Erreur options_traitement :\n"
                "Trop d'arguments utilisés.\n");
        options_afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!fichier_sortie_fourni)
    {
        strcpy(options.nom_fichier_sortie, "");
    }

    return options;
}

FILE *ouverture_entree(Options options)
{
    FILE *entree = fopen(options.nom_fichier_entree, "r");
    if (entree == NULL)
    {
        fprintf(stderr,
                "Erreur ouverture_entree :\n"
                "Echec d'ouverture du fichier '%s'.\n",
                options.nom_fichier_entree);
        exit(EXIT_FAILURE);
    }
    return entree;
}

FILE *ouverture_sortie(Options options)
{
    FILE *sortie = stdout;

    if (strcmp(options.nom_fichier_sortie, "") != 0)
    {
        sortie = fopen(options.nom_fichier_sortie, "w");

        if (sortie == NULL)
        {
            fprintf(stderr,
                    "Erreur ouverture_sortie :\n"
                    "Echec d'ouverture du fichier '%s'.\n",
                    options.nom_fichier_sortie);
            exit(EXIT_FAILURE);
        }
    }

    return sortie;
}

void fermeture_entree(FILE *entree, Options options)
{
    if (fclose(entree) == EOF)
    {
        fprintf(stderr,
                "Erreur fermeture_entree :\n"
                "Echec de fermeture du fichier '%s'.\n",
                options.nom_fichier_entree);
        exit(EXIT_FAILURE);
    }
}
void fermeture_sortie(FILE *sortie, Options options)
{
    if (sortie == stdout)
    {
        return;
    }

    if (fclose(sortie) == EOF)
    {
        fprintf(stderr,
                "Erreur fermeture_sortie :\n"
                "Echec de fermeture du fichier '%s'.\n",
                options.nom_fichier_sortie);
        exit(EXIT_FAILURE);
    }
}
