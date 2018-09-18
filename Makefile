CC = gcc

all: server client

server: server.c
	gcc -o ruptimeServer server.c

client: client.c
	gcc -o ruptimeClient client.c

clean:
	$(RM) ruptimeServer ruptimeClient
