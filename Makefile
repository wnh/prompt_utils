
PROGS=     swd gitst

PREFIX=    /usr/local
BINDIR=    $(PREFIX)/bin
CFLAGS=    -g

all: $(PROGS)

clean:
	-rm $(PROGS)

install:
	install $(PROGS) $(BINDIR)

.PHONEY: all clean install

