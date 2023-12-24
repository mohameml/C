CC = gcc
LD = gcc

CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=

# Enoncé : compléter ce Makefile avec les objectifs suivants
# Objectifs du Makefile :
# Générer la bibliothèque statique libmorseLS.a à partir du fichier objet morse.o fourni
# Générer la bibliothèque dynamique libmorseLD.so à partir du fichier objet morse.o fourni
# Générer le programme test_morse_LS à partir du code source test_morse.c fourni et de la bibliothèque statique créée libmorseLS.a
# Générer le programme test_morse_LD à partir du code source test_morse.c fourni et de la bibliothèque dynamique créée libmorseLD.so
# NOTA BENE :
#     * Ne pas générer directement test_morse_LS ou test_morse_LD à partir de test_morse.o et morse.o.
#     * L'objectif de l'exercice est de générer des bibliothèques statique (libmorseLS.a) et dynamique (libmorseLD.so)
#       et de les utiliser pour créer les programmes test_morse_LS test_morse_LD.


.PHONY  : clean

clean:
	rm -rf test_morse.o test_morse_LS test_morse_LD libmorseLS.a libmorseLD.so


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
