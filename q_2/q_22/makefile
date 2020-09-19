CC = gcc
AR = ar -rcs
FLAGS = -Wall


all: client server

client: client.o
	$(CC) $(FLAGS) client.o -o client

server: server.o
	$(CC) $(FLAGS) server.o -o server

client.o: client.c
	$(CC) $(FLAGS) -c client.c

server.o: server.c
	$(CC) $(FLAGS) -c server.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so out client server all