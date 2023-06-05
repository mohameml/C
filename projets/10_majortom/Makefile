CC=gcc
# Compléter CFLAGS en incluant les PATH vers les fichiers entête .h de la lib SDL
# Les PATH vers ces fichiers sur les PC Ensimag physiques et virtuels sont : /usr/local/include , /usr/local/include/SDL , /usr/include/SDL
# Si vous travaillez sur votre ordinateur personnel, adaptez ces PATH à votre installation locale de SDL 1.2 et SDL_sound,
CFLAGS=-g -std=c99 -Wall -Wextra
# Compléter LDFLAGS en incluant les librairies SDL, SDL_sound et libm (math.h)
# Le PATH vers ces librairies sur les PC Ensimag est : /usr/local/lib
# Les librairies nécessaires sont : libSDL, libSDL_sound et libm
LDFLAGS=

DATA_FOLDER=data

$(DATA_FOLDER):
	ln -s /matieres/3MMPLC/prepa/majortom/data

# Ecrire un Makefile standard permettant de generer le programme test-sdlsound à partir de test-sdlsound.c, fonctions.c, sdlsound.o et $(DATA_FOLDER)
# Faire en sorte que la compilation s'effectue aussi à nouveau quand un fichier .h est modifié
# Pour la règle clean, attention de ne pas supprimer l'objet fourni sdlsound.o

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
