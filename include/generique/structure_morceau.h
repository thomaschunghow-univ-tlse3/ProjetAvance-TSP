/*
 * structure_morceau.h
 */

#ifndef STRUCTURE_MORCEAU_H
#define STRUCTURE_MORCEAU_H

#include <stddef.h>

typedef enum
{
    GAUCHE,
    DROITE
} Direction;

typedef struct tableau_morceau *TableauMorceau;

TableauMorceau tableau_morceau_creer(size_t nombre_morceaux);

void tableau_morceau_supprimer(TableauMorceau *);

size_t tableau_morceau_obtenir_nombre_morceaux(TableauMorceau);

size_t tableau_morceau_obtenir_nombre_sommets(TableauMorceau, size_t indice);

size_t tableau_morceau_obtenir_sommet_gauche(TableauMorceau, size_t indice);

size_t tableau_morceau_obtenir_sommet_droit(TableauMorceau, size_t indice);

void tableau_morceau_modifier_nombre_morceaux(TableauMorceau tableau, size_t nombre_morceaux);

void tableau_morceau_modifier_nombre_sommets(TableauMorceau, size_t indice, size_t nombre_sommets);

void tableau_morceau_modifier_sommet_gauche(TableauMorceau, size_t indice, size_t sommet_gauche);

void tableau_morceau_modifier_sommet_droit(TableauMorceau, size_t indice, size_t sommet_droit);

void tableau_morceau_modifier_morceau(TableauMorceau, size_t indice, size_t nombre_sommets, size_t sommet_gauche,
                                      size_t sommet_droit);

void tableau_morceau_echanger_sommets_gauche_et_droit(TableauMorceau, size_t indice);

void tableau_morceau_decaler_morceau(TableauMorceau tableau, size_t nombre_decalage_gauche, size_t sommet_A,
                                     size_t sommet_B);

void tableau_morceau_decaler_sommets_morceau(TableauMorceau morceaux, size_t indice_morceau_A, size_t indice_morceau_B,
                                             size_t nombre_decalage_gauche, size_t sommet_A, size_t sommet_B);

#endif // STRUCTURE_MORCEAU_H
