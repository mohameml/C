CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: param

.PHONY: clean
clean:
	rm -f *~ *.o param

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
