#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main()
{
    int client_socket;
    int connection_status;

    char server_response[256];

    //create client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Socket Creation failed \n");
        exit(1);
    }

    //defining the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);


    //connecting the client socket to the server address
    connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection_status == -1)
    {
        printf("Socket connection failed \n");
        exit(2);
    }

    //receiving response from the server
    recv(client_socket, &server_response, sizeof(server_response), 0);

    //printing the response
    printf("The server sent the data: %s \n", server_response);
    
    //closing the client socket connection
    close(client_socket);

    return 0;
}