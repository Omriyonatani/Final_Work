CC = gcc
AR = ar -rcs
FLAGS = -Wall


all: check_pid

check_pid: check_pid.o
	$(CC) $(FLAGS) check_pid.o -o check_pid

check_pid.o: check_pid.c
	$(CC) $(FLAGS) -c check_pid.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so out check_pid all