#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main()
{
    int err;
    char server_message[256] = "You have reaches the server!";

    //creating the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1)
    {
        printf("Socket Creation failed \n");
        exit(1);
    }

    //defining the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind the socket to our specified IP and Port
    err = bind (server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if(err == -1)
    {
        printf("Socket bind failed \n");
        exit(2);
    }

    //listening to the network traffic
    err = listen(server_socket, 5);
    if(err == -1)
    {
        printf("Socket listen failed \n");
        exit(3);
    }

    //accept the client socket
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == -1)
    {
        printf("Socket accept failed \n");
        exit(4);
    }

    //send a message to the client socket
    err = send(client_socket, server_message, sizeof(server_message), 0);
    if(err == -1)
    {
        printf("Socket send failed \n");
        exit(5);
    }

    //close the server_socket
    close(server_socket);


    return 0;
}