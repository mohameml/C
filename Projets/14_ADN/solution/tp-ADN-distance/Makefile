# Makefile qui genere l'executable distanceEdition et fait des tests de verification
#
#
CC=gcc
LATEXC=pdflatex
DOCC=doxygen
CFLAGS=-g -Wall 

REFDIR=.
SRCDIR=$(REFDIR)/src
BINDIR=$(REFDIR)/bin
DOCDIR=$(REFDIR)/doc
TESTDIR=$(REFDIR)/tests
REPORTDIR=$(REFDIR)/report

LATEXSOURCE=$(wildcard $(REPORTDIR)/*.tex)
CSOURCE=$(wildcard $(SRCDIR)/*.c)
PDF=$(LATEXSOURCE:.tex=.pdf)

all: binary report doc 

binary: $(BINDIR)/distanceEdition

binary_debug: $(BINDIR)/distanceEditiondebug 

report: $(PDF) 

doc: $(DOCDIR)/index.html


$(BINDIR)/distanceEdition: $(SRCDIR)/distanceEdition.c $(BINDIR)/Needleman-Wunsch-recPD.o
	$(CC) $(OPT) -I$(SRCDIR) -o $(BINDIR)/distanceEdition $(BINDIR)/Needleman-Wunsch-recPD.o $(SRCDIR)/distanceEdition.c 

$(BINDIR)/Needleman-Wunsch-recPD.o: $(SRCDIR)/Needleman-Wunsch-recmemo.h $(SRCDIR)/Needleman-Wunsch-recPD.c $(SRCDIR)/characters_to_base.h $(SRCDIR)/Needleman-Wunsch-recPD.h
	$(CC) $(OPT) -I$(SRCDIR) -c  -o $(BINDIR)/Needleman-Wunsch-recPD.o $(SRCDIR)/Needleman-Wunsch-recPD.c
	
$(BINDIR)/extract-fasta-sequences-size: $(SRCDIR)/extract-fasta-sequences-size.c
	$(CC) $(OPT) -I$(SRCDIR) -o $(BINDIR)/extract-fasta-sequences-size $(SRCDIR)/extract-fasta-sequences-size.c

clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf 

#$(BINDIR)/distanceEdition: $(CSOURCE)
#	$(CC) $(CFLAGS)  $^ -o $@ 

$(BINDIR)/distanceEditiondebug: $(CSOURCE)
	$(CC) $(CFLAGS)  $^ -o $@ -DDEBUG

%.pdf: $(LATEXSOURCE)
	$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE)
	$(DOCC) $(SRCDIR)/Doxyfile


test: $(BINDIR)/distanceEdition $(TESTDIR)/Makefile-test
	cd $(TESTDIR) ; make -f Makefile-test all 
	
test-valgrind: $(BINDIR)/distanceEdition $(TESTDIR)/Makefile-test
	make -f $(TESTDIR)/Makefile-test all-valgrind
	
.PHONY: all doc bin report 

