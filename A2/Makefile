CFLAGS = -pg -Wall -Werror -Wpedantic -std=c++20 -O0 -g
CC = g++

OBJECTS = main.o bst.o

default: run-tests

run-tests: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cpp bst.h

bst.o: bst.cpp bst.h

clean:
	rm -f run-tests *.o *~
