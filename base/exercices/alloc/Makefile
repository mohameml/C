CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: alloc

.PHONY: clean
clean:
	rm -f *~ *.o alloc

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
