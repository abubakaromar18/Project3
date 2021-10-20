all: server client

server:
	cc -o server TCPserver.c

client:
	cc -o client TCPclient.c