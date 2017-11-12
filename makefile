ifndef VERBOSE
.SILENT:
endif

CC=gcc
CFLAGS=-g -O0

DEPS=obj/main.o obj/tests.o obj/fof_node.o	obj/str_func.o obj/tree_func.o

obj/%.o: bin/%.c
	$(CC) -c $^ -o $@

obj/%.o: ./%.c
	$(CC) -c $^ -o $@

main: echoInfo $(DEPS)
	$(CC) $(DEPS) $(CFLAGS) -o main
	echo Done!

echoInfo:
	echo Making main ...

info: README.md
	cat README.md

help: help.txt
	cat help.txt

clean:
	echo Cleaning project directory ...
	rm -f **/*.o *.o main
	echo Done!
