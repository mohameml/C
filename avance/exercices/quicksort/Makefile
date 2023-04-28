CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: quicksort

.PHONY: clean
clean:
	rm -f *~ *.o quicksort

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
