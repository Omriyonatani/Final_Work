CC = gcc
AR = ar -rcs
FLAGS = -Wall -pthread


all: set_policy

set_policy: set_policy.o
	$(CC) $(FLAGS) set_policy.o -o set_policy

set_policy.o: set_policy.c
	$(CC) $(FLAGS) -c set_policy.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so out set_policy all