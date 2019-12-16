ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif
ifdef B
	BREAKPOINT = -ex "b $(B)"
else

endif
all: main.o parse_args.o execute.o
	$(CC) -o crash main.o parse_args.o execute.o
main.o: main.c parse_args.h execute.h
	$(CC) -c main.c
parse_args.o: parse_args.c 
	$(CC) -c parse_args.c
execute.o: execute.c
	$(CC) -c execute.c
clean:
	rm -f *.o
	rm -f *~
run:
	./crash
debug:
	make clean
	make DEBUG=true
	gdb -ex "set follow-fork-mode child" $(BREAKPOINT) crash
mem_check:
	make clean
	make
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./crash
