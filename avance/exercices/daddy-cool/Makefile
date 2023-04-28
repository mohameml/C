CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: daddy-cool

.PHONY: clean
clean:
	rm -f *~ *.o daddy-cool


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
