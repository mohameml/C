CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pendu

.PHONY: clean
clean:
	rm -f *~ *.o pendu

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
