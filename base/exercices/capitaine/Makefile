CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: capitaine

.PHONY: clean
clean:
	rm -f *~ *.o capitaine

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
