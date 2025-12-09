#
# affichage_interactif.py
#


import numpy as np
import re
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from enum import Enum


# Paramètres.

# Adresse du fichier.
nom_fichier = "./bin/donnees.txt"

# Nombre de générations ignorées entre deux générations.
intervalle_generations = 0

# Délai entre deux générations en millisecondes.
# Remarque : le traitement de chaque ligne n'est pas instantanné,
# ainsi il existe une valeur minimale tel que
# l'affichage ne peut pas être plus rapide que cette valeur.
delai_generations = 1


def traiter_coordonnees(ligne):
    coordonnees = re.findall(r"\d+\.\d+", ligne)
    coordonnees = [float(nombre) for nombre in coordonnees]

    return coordonnees


def traiter_points(fichier):
    ligne = fichier.readline()
    coordonnees_x = traiter_coordonnees(ligne)

    ligne = fichier.readline()
    coordonnees_y = traiter_coordonnees(ligne)

    return coordonnees_x, coordonnees_y


def traiter_permutation(ligne):
    permutation = re.findall(r"\d+", ligne)
    permutation = [int(nombre) - 1 for nombre in permutation]
    permutation.append(permutation[0])

    return permutation


def rearranger_coordonnees(coordonnees_x, coordonnees_y, permutation):
    permutation_x, permutation_y = [], []

    for i in permutation:
        permutation_x.append(coordonnees_x[i])
        permutation_y.append(coordonnees_y[i])

    permutation_x = np.array(permutation_x)
    permutation_y = np.array(permutation_y)

    return permutation_x, permutation_y


def ignorer_generation(fichier, intervalle_generations, nombre_individus):
    for i in range(intervalle_generations * nombre_individus):
        fichier.readline()

    return


def update_genetique(frame):
    ignorer_generation(fichier, intervalle_generations, nombre_individus)

    for i in range(nombre_individus):
        ligne = fichier.readline()
        if not ligne:
            return artists

        permutation = traiter_permutation(ligne)

        permutation_x, permutation_y = rearranger_coordonnees(
            coordonnees_x, coordonnees_y, permutation
        )

        ax = axs[i]
        ax.clear()

        fig.suptitle(f"Génétique\nGénération {frame * (intervalle_generations + 1)}")
        ax.set_title(f"Individu {i + 1}")

        (artists[i],) = ax.plot(permutation_x, permutation_y, marker="o")

    return artists


def update_2opt(frame):
    ignorer_generation(fichier, intervalle_generations, 1)

    ligne = fichier.readline()
    if not ligne:
        return

    permutation = traiter_permutation(ligne)

    permutation_x, permutation_y = rearranger_coordonnees(
        coordonnees_x, coordonnees_y, permutation
    )

    ax.clear()

    ax.set_title(f"2-optimisation\nGénération {frame * (intervalle_generations + 1)}")
    ax.plot(permutation_x, permutation_y, marker="o")

    return


class Methode(Enum):
    DEUXOPTIMISATION = 0
    GENETIQUE = 1


def gerer_methode(fichier):
    methode = fichier.readline()

    if methode.startswith("2-optimisation"):
        return Methode.DEUXOPTIMISATION

    elif methode.startswith("genetique"):
        return Methode.GENETIQUE

    return


def traiter_parametres_genetique(fichier):
    nombre_individus = int(fichier.readline())
    nombre_generations = int(fichier.readline()) + 2
    taux_mutation = float(fichier.readline())
    taille_tournoi = int(fichier.readline())

    return nombre_individus, nombre_generations, taux_mutation, taille_tournoi


# Main.

fichier = open(nom_fichier)

coordonnees_x, coordonnees_y = traiter_points(fichier)

methode = gerer_methode(fichier)


if methode == Methode.GENETIQUE:
    nombre_individus, nombre_generations, taux_mutation, taille_tournoi = (
        traiter_parametres_genetique(fichier)
    )

    nb_colonnes = min(5, nombre_individus)
    nb_lignes = (nombre_individus + nb_colonnes - 1) // nb_colonnes

    fig, axs = plt.subplots(
        nb_lignes, nb_colonnes, figsize=(5 * nb_colonnes, 4 * nb_lignes)
    )

    axs = np.array(axs).reshape(-1)  # Pour aplatir en liste

    artists = [None] * nombre_individus

    animation = FuncAnimation(
        fig,
        update_genetique,
        interval=delai_generations,
        blit=False,
    )

elif methode == Methode.DEUXOPTIMISATION:
    nombre_individus = 1

    fig, ax = plt.subplots()

    animation = FuncAnimation(fig, update_2opt, interval=delai_generations, blit=False)


plt.show()

fichier.close()
