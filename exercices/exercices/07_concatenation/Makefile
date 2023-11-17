CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: concatenation

.PHONY: clean
clean:
	rm -f *~ *.o concatenation

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
