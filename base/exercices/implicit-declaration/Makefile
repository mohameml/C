CC=gcc
# -Werror = les avertissements (warnings) deviennent des erreurs!
CFLAGS=-Wall -Wextra -Werror -std=c99

all: compile-moi

.PHONY: clean

clean:
	rm -f compile-moi.o compile-moi

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
