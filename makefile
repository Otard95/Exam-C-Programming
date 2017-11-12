CC=gcc
CFLAGS=-g -O0

DEPS=obj/main.o obj/fof_node.o	obj/str_func.o obj/tree_func.o

obj/%.o: bin/%.c
	$(CC) -c $^ -o $@

obj/%.o: ./%.c
	$(CC) -c $^ -o $@

main: $(DEPS)
	$(CC) $^ $(CFLAGS) -o main
