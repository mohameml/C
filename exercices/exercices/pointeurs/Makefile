CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pointeurs

.PHONY: clean
clean:
	rm -f *~ *.o pointeurs

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
