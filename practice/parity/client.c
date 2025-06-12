#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    char data[30];
    char parity[2] = {'0', '\0'};
    char mode;
    int countOne = 0;

    printf("Enter data: ");
    scanf("%s", data);
    int dataLen = strlen(data);
    for (int i = 0; i < dataLen; i++)
    {
        if (data[i] == '1')
            countOne += 1;
    }

    printf("Enter mode: (e for even parity, o for odd parity): ");
    scanf(" %c", &mode);

    if (mode == 'e')
    {
        parity[0] = (countOne % 2 == 0) ? '0' : '1';
    }
    else if (mode == 'o')
    {
        parity[0] = (countOne % 2 == 0) ? '1' : '0';
    }
    else
    {
        printf("Invalid mode.\n");
        exit(0);
    }

    printf("parity bit : %c\n", parity[0]);
    strcat(data, parity);
    printf("codeword is : %s\n", data);

    send(clientSocket, data, strlen(data) + 1, 0);

    close(clientSocket);
}