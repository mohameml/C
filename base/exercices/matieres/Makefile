CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: matieres

.PHONY: clean
clean:
	rm -f *~ *.o matieres

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
