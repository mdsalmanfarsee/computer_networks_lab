#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket, serverSocket;
    struct sockaddr_in serverAddr, clientAddr;

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    int size = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &size);

    char data[30];
    char mode;
    int countOne = 0;

    recv(clientSocket, data, sizeof(data), 0);

    int dataLen = strlen(data);
    for (int i = 0; i < dataLen; i++)
    {
        if (data[i] == '1')
            countOne += 1;
    }

    printf("Enter mode: (e for even parity, o for odd parity): ");
    scanf(" %c", &mode);

    int error = 0;

    if (mode == 'e')
    {
        error = (countOne % 2 == 0) ? 0 : 1;
    }
    else if (mode == 'o')
    {
        error = (countOne % 2 == 0) ? 1 : 0;
    }
    else
    {
        printf("Invalid mode.\n");
        exit(0);
    }

    if (error)
    {
        printf("Codeword has error!\n");
    }
    else
    {
        printf("No error!\n");
        data[strlen(data) - 1] = '\0';
        printf("Original data is: %s\n", data);
    }

    close(clientSocket);
    close(serverSocket);
}