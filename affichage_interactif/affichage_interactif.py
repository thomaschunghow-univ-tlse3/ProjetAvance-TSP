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

    nouvelles_coordonnees_x = []
    nouvelles_coordonnees_y = []

    for i in permutation:
        nouvelles_coordonnees_x.append(coordonnees_x[i])
        nouvelles_coordonnees_y.append(coordonnees_y[i])

    return nouvelles_coordonnees_x, nouvelles_coordonnees_y


def afficher_permutation(coordonnees_x, coordonnees_y, permutation, temps_attente):

    plt.cla()

    coordonnees_x, coordonnees_y = rearranger_coordonnees(
        coordonnees_x, coordonnees_y, permutation)

    coordonnees_x = np.array(coordonnees_x)
    coordonnees_y = np.array(coordonnees_y)

    plt.plot(coordonnees_x, coordonnees_y)
    plt.draw()
    plt.pause(temps_attente)


def main():

    fichier = open(nom_fichier)

    coordonnees_x, coordonnees_y = traiter_points(fichier)

    i = 0
    for ligne in fichier:

        plt.subplot(1, nombre_individus, i + 1)

        permutation = traiter_permutation(ligne)
        afficher_permutation(coordonnees_x, coordonnees_y,
                             permutation, temps_attente)

        i = (i + 1) % nombre_individus

    plt.show()
    fichier.close()


nom_fichier = "./affichage_interactif/donnees.txt"

nombre_individus = 5
nombre_generations = 100

temps_attente = 0.00001

main()
