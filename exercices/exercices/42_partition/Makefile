CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: partition

.PHONY: clean
clean:
	rm -f *~ *.o partition

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
