CC=gcc
CFLAGS=-Wall

undump: undump.o core.o elfcommon.o program.o

debug: CFLAGS += -ggdb3
debug: undump

clean:
	rm -f undump undump.o elfcommon.o program.o core.o

