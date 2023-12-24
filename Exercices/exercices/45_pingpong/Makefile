CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: pingpong

.PHONY: clean
clean:
	rm -f *~ *.o pingpong

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
