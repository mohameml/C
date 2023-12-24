CC=gcc
# std=gnu99 : gnu99 = c99 + gnu extensions. Utilisé ici pour avoir accès aux fonctions de temps réel avec une précision de nanoseconde (clock_gettime,...)
CFLAGS=-g -std=gnu99 -Wall -Wextra
# Le librairie nécessaire pour utiliser clock_gettime est : librt
LDFLAGS=-lrt

speed: speed.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean :
	rm -f *.o speed

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
