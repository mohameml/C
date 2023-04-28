CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: statphabet

.PHONY: clean
clean:
	rm -f *~ *.o statphabet

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
