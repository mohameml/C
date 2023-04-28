CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: safari

.PHONY: clean
clean:
	rm -f *~ *.o safari

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
