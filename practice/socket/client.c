#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{

    int clientSocket;
    struct sockaddr_in serverAddr;

    char buffer[50];
    char msg[20];

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("Enter a string: ");
    scanf("%[^\n]", buffer);

    send(clientSocket, buffer, sizeof(buffer), 0);

    recv(clientSocket, msg, sizeof(msg), 0);

    printf("\nServer says: %s", msg);

    close(clientSocket);
}