# Utiliser le Makefile suivant dans un premier temps pour tester l'exécutable
# Compléter ensuite avec les options que vous jugerez utiles
CC=gcc
CFLAGS=-std=c99
LDFLAGS=
EXEC=debogage-exo9

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
