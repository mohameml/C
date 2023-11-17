CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: contact

.PHONY: clean
clean:
	rm -f *~ *.o contact

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
