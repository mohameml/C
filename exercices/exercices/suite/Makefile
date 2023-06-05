CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: suite

.PHONY: clean
clean:
	rm -f *~ *.o suite

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
