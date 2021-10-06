prog: const.o fun.o prog.o
	cc $^ -o prog

%.o: %.c
	cc $^ -c -o $@

clean:
	rm -f prog *.o
