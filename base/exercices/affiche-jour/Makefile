CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: affiche-jour

.PHONY: clean check

check:
	make -C tests/ check

clean:
	rm -f *~ *.o affiche-jour

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
