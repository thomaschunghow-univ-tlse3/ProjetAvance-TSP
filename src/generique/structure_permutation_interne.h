/*
 * structure_permutation_interne.h
 */

#ifndef STRUCTURE_PERMUTATION_INTERNE_H
#define STRUCTURE_PERMUTATION_INTERNE_H

#include <stddef.h>

struct permutation
{
    size_t nombre_sommets;
    size_t *sommets;

    size_t taille_distance;
    char *longueur;
    /* On utilise le type char pour pouvoir faire de l'arithmétique de pointeurs,
     * car void n'a pas de taille. */
};

#endif // STRUCTURE_PERMUTATION_INTERNE_H
