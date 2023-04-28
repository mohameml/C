CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: euro2016

.PHONY: clean
clean:
	rm -f *~ *.o euro2016

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
