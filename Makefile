
PROGS=     swd gitst

PREFIX=    /usr/local
BINDIR=    $(PREFIX)/bin

all: $(PROGS)

clean:
	rm $(PROGS)

install:
	install $(PROGS) $(BINDIR)

.PHONEY: all clean install

