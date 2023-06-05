CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: bingo

.PHONY: clean
clean:
	rm -f *~ *.o bingo

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
