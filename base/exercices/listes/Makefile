CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: listes

.PHONY: clean
clean:
	rm -f *~ *.o listes
	rm -rf *.dSYM # mac-erie

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
