CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: palindrome

.PHONY: clean
clean:
	rm -f *~ *.o palindrome

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
