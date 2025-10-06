/*
 *
 */

#include "traitement_options.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void afficher_aide(char *nom_programme)
{
    printf("Usage: %s -f <fichier d'entrée> [-o <fichier de sortie>] -m <méthode> [-c]\n", nom_programme);
}

Options initialiser_options()
{
    Options options;
    options.fichier_entree_fourni = false;
    options.fichier_sortie_fourni = false;
    options.methode_calcul_fourni = false;
    options.tournee_canonique = false;
    return options;
}

MethodeCalcul traitement_methode_calcul(char *nom)
{
    if (strncmp(nom, "bf", 2) == 0)
    {
        return BF;
    }
    if (strncmp(nom, "nn", 2) == 0)
    {
        return NN;
    }
    else if (strncmp(nom, "rw", 2) == 0)
    {
        return RW;
    }
    else if (strncmp(nom, "2optnn", 6) == 0)
    {
        return NN2OPT;
    }
    else if (strncmp(nom, "2optrw", 6) == 0)
    {
        return RW2OPT;
    }
    else if (strncmp(nom, "ga", 2) == 0)
    {
        return GA;
    }
    else if (strncmp(nom, "gadpx", 5) == 0)
    {
        return GADPX;
    }
    else if (strncmp(nom, "all", 3) == 0)
    {
        return ALL;
    }
    fprintf(stderr,
            "Erreur traitement_methode_calcul :\n"
            "Méthode de calcul non-reconnue.\n");
    exit(EXIT_FAILURE);
}

Options traitement_options(int argc, char **argv)
{
    Options options = initialiser_options();
    opterr = 0; // Gestion des erreurs personalisée.
    int opt;
    while ((opt = getopt(argc, argv, "hf:m:o:c")) != -1)
    {
        switch (opt)
        {
        case 'h':
            afficher_aide(argv[0]);
            exit(EXIT_SUCCESS);
        case 'f':
            options.fichier_entree_fourni = true;
            strncpy(options.nom_fichier_sortie, optarg, TAILLE_OPTIONS_MAX);
            break;
        case 'o':
            options.fichier_entree_fourni = true;
            strncpy(options.nom_fichier_sortie, optarg, TAILLE_OPTIONS_MAX);
            break;
        case 'm':
            options.methode_calcul_fourni = true;
            options.methode_calcul = traitement_methode_calcul(optarg);
            break;
        case 'c':
            options.tournee_canonique = true;
            break;
        default:
            fprintf(stderr,
                    "Erreur traitement_options :\n"
                    "Option non-reconnue.\n");
            afficher_aide(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (!options.fichier_entree_fourni || !options.methode_calcul_fourni)
    {
        fprintf(stderr,
                "Erreur traitement_options :\n"
                "Paramètres obligatoires manquants.\n");
        afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }
    if (optind < argc)
    {
        fprintf(stderr,
                "Erreur traitement_options :\n"
                "Trop d'arguments utilisés.\n");
        afficher_aide(argv[0]);
        exit(EXIT_FAILURE);
    }
    return options;
}