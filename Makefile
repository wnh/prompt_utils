
PROGS=  swd gitst

PREFIX= /usr/local

all: $(PROGS)

clean:
	rm $(PROGS) *.o

install:
	install $(PROGS) $(PREFIX)/bin
	

.PHONEY: all clean install

