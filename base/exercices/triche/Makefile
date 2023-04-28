CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: triche

.PHONY: clean
clean:
	rm -f *~ *.o triche

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
