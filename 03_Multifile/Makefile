GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so
SOURCES = $(wildcard *.c)
TRASH = $(SOURCES:.c=.o) *.output
CFLAGS += -fPIC

.PHONY: all clean test

all: test


prog: const.o fun.o prog.o
	cc $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $< -o $@ -L. -loutput_static

prog-so: prog.o liboutput.so
	cc $< -o $@ -L. -loutput


%_0.output: %
	LD_LIBRARY_PATH=`pwd` ./$^ > $@ 2>&1

%_1.output: %
	LD_LIBRARY_PATH=`pwd` ./$^ param1 > $@ 2>&1

%_3.output: %
	LD_LIBRARY_PATH=`pwd` ./$^ Linux Application Development > $@ 2>&1

test_%: prog_%.output prog-a_%.output prog-so_%.output
	cmp prog_$*.output prog-a_$*.output
	cmp prog_$*.output prog-so_$*.output

test: test_0 test_1 test_3


liboutput_static.a: fun.o const.o
	ar -rcs $@ $?

liboutput.so: fun.o const.o 
	cc $^ --shared -o $@


%.o: %.c
	cc $< -c $(CFLAGS) -o $@

fun.o: outlib.h
prog.o: outlib.h


clean:
	rm -rf $(TRASH) $(GENERATES)
