CC = gcc
LD = $(CC)
CFLAGS = -std=c99 -Wall -Wextra -g

all: test gribouille

motif.o: motif.c motif.h
biblio.o: biblio.c biblio.h motif.h
main.o: main.c biblio.h motif.h
%.o: %.c 
	$(CC) -c $(CFLAGS) $<

test: motif.o biblio.o main.o
	$(LD) -lm -o $@ $^ 
gribouille: motif.o biblio.o gribouille.o
	$(LD) -lm -o $@ $^ 

clean:
	rm test *.o gribouille
realclean: clean
	rm *.ppm

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
