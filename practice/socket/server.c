#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{

    int clientSocket, serverSocket;
    struct sockaddr_in clientAddr, serverAddr;

    char buffer[50];
    char msg[20] = "Thank You!";

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 10);

    int size = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &size);
    printf("server is listening: ");

    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("\nclient says: %s", buffer);

    send(clientSocket, msg, sizeof(msg), 0);

    close(clientSocket);
    close(serverSocket);
}