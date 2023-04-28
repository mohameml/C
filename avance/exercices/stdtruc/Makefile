CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: stdtruc

.PHONY: clean
clean:
	rm -f *~ *.o stdtruc out.txt err.txt

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
