CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: rationnels

.PHONY: clean
clean:
	rm -f *~ *.o rationnels

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
