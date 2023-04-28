CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
LDFLAGS=
EXEC=trace

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *~ *.o $(EXEC)


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
