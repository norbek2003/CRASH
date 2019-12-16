ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif
ifdef B
	BREAKPOINT = -ex "b $(B)"
else

endif
all: main.o parse_args.o
	$(CC) -o my_shell main.o parse_args.o
main.o: main.c headers.h
	$(CC) -c main.c
parse_args.o: parse_args.c headers.h
	$(CC) -c parse_args.c
#linked_list.o: linked_list.c linked_list.h
#	$(CC) -c linked_list.c
clean:
	rm -f *.o
	rm -f *~
run:
	./my_shell
debug:
	make clean
	make DEBUG=true
	gdb -ex "set follow-fork-mode child" $(BREAKPOINT) my_shell
mem_check:
	make clean
	make
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./my_shell
