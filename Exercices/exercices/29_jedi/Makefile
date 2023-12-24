CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: jedi

.PHONY: clean
clean:
	rm -f *~ *.o jedi

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
