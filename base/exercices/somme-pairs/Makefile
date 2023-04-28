CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: somme-pairs

.PHONY: clean
clean:
	rm -f *~ *.o somme-pairs

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
