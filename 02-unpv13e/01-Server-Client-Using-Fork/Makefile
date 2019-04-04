CC=gcc

all: client server

client: tcpClient.c
	$(CC) -o client.o tcpClient.c

server: tcpServer.c
	$(CC) -o server.o tcpServer.c

.PHONY: clean
clean:
	rm client.o server.o
