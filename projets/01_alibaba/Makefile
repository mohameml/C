CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS= -lcriterion

all: alibaba test_ldc

test_ldc: ldc.o test_ldc.o
	$(CC) $^ -o $@ $(LDFLAGS)

alibaba: alibaba.o ldc.o
	gcc $(CFLAGS) $^ -o $@

alibaba.o : alibaba.c
	gcc $(CFLAGS) -c $< -o $@

ldc.o : ldc.c ldc.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f alibaba.o ldc.o alibaba test_ldc


.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
