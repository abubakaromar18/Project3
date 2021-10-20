all: server client

server: ServerC.c Shared.h
	cc -o server ServerG.c

client: Client.c Shared.h
	cc -o client Client.c