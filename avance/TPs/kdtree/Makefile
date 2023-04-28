CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra
LDFLAGS = -g -lm -lz

OBJ_PROF =  obj_profs/array.o obj_profs/image.o obj_profs/kdtree.o obj_profs/NN.o
OBJ_recognize = recognize.o   # a completer
OBJ_perf =                    # a completer (optionnel)
OBJ_FILES = $(OBJ_perf) $(OBJ_recognize)
DATA_REP = data
EXEC = recognize #perf

all: $(EXEC) $(DATA_REP)

DATA_REP:
	ln -s /matieres/3MMPLC/prepa/kdtree/data data

recognize: $(OBJ_recognize) $(OBJ_PROF)
perf: $(OBJ_perf) $(OBJ_PROF)

% :
	$(CC) $(LDFLAGS) $^ -o $@


clean :
	rm -f $(OBJ_FILES) $(EXEC)

.PHONY: all clean

.PHONY: progress

progress:
	@../../../.progress/update $(shell basename "$(shell pwd)")
