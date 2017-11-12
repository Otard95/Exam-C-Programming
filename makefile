CC=gcc
CFLAGS=-g -O0

DEPS=obj/main.o obj/tests.o obj/fof_node.o	obj/str_func.o obj/tree_func.o

obj/%.o: bin/%.c
	$(CC) -c $^ -o $@

obj/%.o: ./%.c
	$(CC) -c $^ -o $@

main: $(DEPS)
	$(CC) $^ $(CFLAGS) -o main

info: README.md
	cat README.md

help: help.txt
	cat help.txt

clean:
	rm **/*.o *.o main
