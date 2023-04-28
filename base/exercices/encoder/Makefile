CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
TARGETS=encoder

all: $(TARGETS)


.PHONY: clean
clean:
	rm -f *~ *.o $(TARGETS)

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
