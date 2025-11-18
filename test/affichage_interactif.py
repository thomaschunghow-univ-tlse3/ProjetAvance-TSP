#
# affichage_interactif.py
#


import numpy as np
import re
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


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
    nx, ny = [], []
    for i in permutation:
        nx.append(coordonnees_x[i])
        ny.append(coordonnees_y[i])
    return nx, ny


def update(frame):

    for i in range(nombre_individus):

        ligne = fichier.readline()

        if not ligne:
            return artists

        permutation = traiter_permutation(ligne)
        permutation_x, permutation_y = rearranger_coordonnees(
            coordonnees_x, coordonnees_y, permutation)

        ax = axs[i]

        ax.clear()

        fig.suptitle(f"Génération {frame+1}")
        ax.set_title(f"Individu {i+1}")
        artists[i], = ax.plot(permutation_x, permutation_y, marker='o')

    return artists


# Paramètres.

nom_fichier = "./test/donnees.txt"

nombre_individus = 10
nombre_generations = 10000


# Main.

fichier = open(nom_fichier)

fig, axs = plt.subplots(1, nombre_individus,
                        figsize=(25, 7))

coordonnees_x, coordonnees_y = traiter_points(fichier)

artists = [None] * nombre_individus

animation = FuncAnimation(fig, update, frames=nombre_generations*nombre_individus,
                          interval=1, blit=False)

plt.show()

fichier.close()
