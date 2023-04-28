CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: slab

.PHONY: clean
clean:
	rm -f *~ *.o slab

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
