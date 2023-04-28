CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: papous

.PHONY: clean
clean:
	rm -f *~ *.o papous

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
