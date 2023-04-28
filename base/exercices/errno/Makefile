CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: errno

.PHONY: clean

clean:
	rm -f *~ *.o errno

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
