CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: preproc

.PHONY: clean
clean:
	rm -f *~ *.o preproc

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
