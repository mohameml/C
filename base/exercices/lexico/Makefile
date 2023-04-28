CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: lexico

.PHONY: clean
clean:
	rm -f *~ *.o lexico

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
