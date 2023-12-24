CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: divflot-simple divflot-double

divflot-simple: divflot-simple.o

divflot-simple.o: divflot.c
	$(CC) $(CFLAGS) -c divflot.c -o divflot-simple.o

divflot-double: divflot-double.o

divflot-double.o: divflot.c
	$(CC) $(CFLAGS) -DDOUBLE_PREC -c divflot.c -o divflot-double.o

.PHONY: clean
clean:
	rm -f *~ *.o divflot-simple divflot-double

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
