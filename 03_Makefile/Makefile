GENERATES = prog
TRASH = *.o

.PHONY: all clean

all: prog

prog: const.o fun.o prog.o
	cc $^ -o prog

%.o: %.c
	cc $< -c -o $@

fun.o: outlib.h
prog.o: outlib.h

clean:
	rm -rf $(TRASH) $(GENERATES)
