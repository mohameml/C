CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: somme-impairs

.PHONY: clean
clean:
	rm -f *~ *.o somme-impairs

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
