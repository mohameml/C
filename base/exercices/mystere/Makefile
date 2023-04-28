CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: mystere

.PHONY: clean
clean:
	rm -f *~ *.o mystere

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
