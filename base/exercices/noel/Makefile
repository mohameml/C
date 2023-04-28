CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: noel

.PHONY: clean
clean:
	rm -f *~ *.o noel

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
