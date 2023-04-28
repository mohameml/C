CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: profiler

.PHONY: clean
clean:
	rm -f *~ *.o profiler

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
