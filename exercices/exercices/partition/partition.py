#!/usr/bin/env python3
"""
On s'interesse ici au probleme 2-partition.
On coupe un ensemble E d'entiers en deux sous-ensembles E1, E2, de meme valeur.
"""


def bits(nombre):
    """
    iterateur sur tous les bits d'un entier.
    """
    while nombre != 0:
        bit = nombre % 2
        nombre >>= 1
        yield bit


def calcul_nombre_partitions(entiers):
    """
    calcule le nombre de partitions valides en iteratif .
    """
    somme = sum(entiers)
    if somme % 2:
        return 0  # si la somme des entiers est impaire, ce n'est pas divisible.

    cible = somme // 2

    nombre_partitions = 0

    for combinaison in range(0, 1 << len(entiers)):
        valeur = sum(b * e for e, b in zip(entiers, bits(combinaison)))
        if valeur == cible:
            nombre_partitions += 1

    return nombre_partitions


def test():
    """
    on regarde combien de temps on met pour trouver que notre exemple n'a que
    deux facons d'etre coupes en deux parts egales.
    """
    entiers = [
        285762,
        1287946,
        260518,
        702569,
        183183,
        1180,
        909976,
        1261857,
        1665545,
        1888537,
        1741007,
        200924,
        1659988,
        359942,
        1009604,
        909891,
        1261628,
        317651,
        822956,
        843816,
        689772,
        1894228,
        648054,
        198750,
        1409020,
    ]

    print("nombre de partitions:", calcul_nombre_partitions(entiers))


if __name__ == "__main__":
    test()
