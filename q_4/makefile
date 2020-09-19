CC = gcc
AR = ar -rcs
FLAGS = -Wall


all: dir_traversal

dir_traversal: dir_traversal.o
	$(CC) $(FLAGS) dir_traversal.o -o dir_traversal

dir_traversal.o: dir_traversal.c
	$(CC) $(FLAGS) -c dir_traversal.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so out dir_traversal all