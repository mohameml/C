CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: do-while

.PHONY: clean
clean:
	rm -f *~ *.o do-while

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
