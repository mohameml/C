CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=-lm

all: portee

portee: portee.o point.o

.PHONY: clean
clean:
	rm -f *~ *.o portee

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
