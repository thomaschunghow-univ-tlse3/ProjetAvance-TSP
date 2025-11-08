/*
 * affichage_interactif.c
 */

#ifdef AFFICHAGE_INTERACTIF

#include <stdlib.h>
#include <stdio.h>

FILE *sortie_interactive;

void ouverture_sortie_interactive()
{
    char *nom_sortie_interactive = "./affichage_interactif/donnees.txt";
    sortie_interactive = fopen(nom_sortie_interactive, "w");
    if (sortie_interactive == NULL)
    {
        fprintf(stderr,
                "Erreur ouverture_sortie :\n"
                "Echec d'ouverture du fichier '%s'.\n",
                nom_sortie_interactive);
        exit(EXIT_FAILURE);
    }
}

#endif // AFFICHAGE_INTERACTIF
