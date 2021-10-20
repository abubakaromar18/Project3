#include "Shared.h"

int main()
{
    int m;
    int n;
    int round = 1;
    int client = 0, server = 0;

    srand(time(NULL));

    int err;
    char server_message[256] = "You have reached the server!";
    char client_response[256];

    //creating the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1)
    {
        printf("Socket: Creation failed \n");
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
        printf("Socket: bind failed \n");
        exit(2);
    }

    //listening to the network traffic
    err = listen(server_socket, 5);
    if(err == -1)
    {
        printf("Socket: listen failed \n");
        exit(3);
    }

    //accept the client socket
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if(client_socket == -1)
    {
        printf("Socket: accept failed \n");
        exit(4);
    }

    err = send(client_socket, server_message, sizeof(server_message), 0);
    if(err == -1)
    {
        printf("Socket: send failed \n");
        exit(5);
    }

    //Rock paper Scissor Program

    //Random generates n out of m rounds
    m = rand() % 10;
    
    if(m % 2 == 0)
    {
        m = m + 1;
        if(m >= 3)
        {
            n = m - 2;
        }
    }

    while(round < n)
    {

        //Randomly chooses a number
        int choice = (rand() % (3 - 1 + 1)) + 1;
        sprintf(server_message, "Choose a symbol Rock = 1, Paper = 2, Siccors = 3 : Current Round %d", round);
        err = send(client_socket, server_message, sizeof(server_message), 0);
        if(err == -1)
        {
            printf("Socket: send failed \n");
            exit(6);
        }

        err = recv(client_socket, &client_response, sizeof(client_response), 0);
        if(err == -1)
        {
            printf("Socket: read failed \n");
            exit(7);
        }
        sprintf(server_message, "server: %d", choice);
        err = send(client_socket, server_message, sizeof(server_message), 0);
        if(err == -1)
        {
            printf("Socket: send faild \n");
            exit(8);
        }


        if (atoi(client_response) == 1)
        {
            if (choice == 3)
            {
                client++;
                sprintf(server_message, "CLIENT WON: Client: %d Server: %d", client, server);
            }
            else if(choice == 2)
            {
                server++;
                sprintf(server_message, "SERVER WON: Client %d Server: %d", client, server);
            }
            else
            {
                sprintf(server_message, "DRAW : client: %d Server: %d", client, server);
            }
        }
        else if (atoi(client_response) == 2)
        {
            if (choice == 1)
            {
                client++;
                sprintf(server_message, "CLIENT WON: Client: %d Server: %d", client, server);
            }
            else if(choice == 3)
            {
                server++;
                sprintf(server_message, "SERVER WON: Client %d Server: %d", client, server);
            }
            else
            {
                sprintf(server_message, "DRAW : client: %d Server: %d", client, server);
            }
        }
        else
        {
            if (choice == 2)
            {
                client++;
                sprintf(server_message, "CLIENT WON: Client: %d Server: %d", client, server);
            }
            else if(choice == 1)
            {
                server++;
                sprintf(server_message, "SERVER WON: Client %d Server: %d", client, server);
            }
            else
            {
                sprintf(server_message, "DRAW : client: %d Server: %d", client, server);
            }
        }

        err = send(client_socket, server_message, sizeof(server_message), 0);
        if(err == -1)
        {
            printf("Socket: send faild \n");
            exit(8);
        }



        round++;
    }

    //send a message to the client socket

    sprintf(server_message, "Bye");
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