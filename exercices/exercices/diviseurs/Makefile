CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: diviseurs

.PHONY: clean

clean:
	rm -f *~ *.o diviseurs

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
