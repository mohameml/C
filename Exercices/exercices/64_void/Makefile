CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: void

.PHONY: clean
clean:
	rm -f *~ *.o void

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
