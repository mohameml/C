CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: bigbucks

salarie.o: salarie.c salarie.h

bigbucks: salarie.o bigbucks.o

.PHONY: clean
clean:
	rm -f *~ *.o bigbucks

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
