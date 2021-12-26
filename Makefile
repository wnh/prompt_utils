
PROGS=     swd \
           gitst

LIBS = lib/scanner.o \
       lib/proc.o

PREFIX=    $(HOME)
BINDIR=    $(PREFIX)/bin
CFLAGS=    -g

all: $(PROGS)

gitst: gitst.o $(LIBS)
	$(CC) $(CFLAGS) -o gitst gitst.o $(LIBS)

clean:
	-rm $(PROGS) $(LIBS)

install:
	install $(PROGS) $(BINDIR)

.PHONEY: all clean install

