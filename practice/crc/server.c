#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket, serverSocket;
    struct sockaddr_in serverAddr, clientAddr;

    char buffer[60];
    char divisor[20];
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9995);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    int size = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &size);

    /*while (1)
    {
        recv(clientSocket, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit") == 0)
            break;
        printf("\nClient says %s: \n", buffer);

        printf("Enter a message: ");
        // scanf(" %[^\n]", buffer);
        scanf("%s", buffer);
        send(clientSocket, buffer, strlen(buffer) + 1, 0);
        if (strcmp(buffer, "exit") == 0)
            break;
    }*/

    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Recieved Codeword is : %s\n", buffer);
    printf("Enter Divisor: ");
    scanf("%s", divisor);
    int totalLen = strlen(buffer);
    int divLen = strlen(divisor);

    for (int i = 0; i < totalLen - divLen + 1; i++)
    {
        if (buffer[i] == '1')
        {
            for (int j = 0; j < divLen; j++)
            {
                if (buffer[i + j] == divisor[j])
                {
                    buffer[i + j] = '0';
                }
                else
                {
                    buffer[i + j] = '1';
                }
            }
        }
    }

    // check if all the buffer is like 0000000...
    int countOne = 0;
    for (int i = 0; i < totalLen; i++)
    {
        if (buffer[i] == '1')
        {
            countOne += 1;
            break;
        }
    }

    if (countOne)
    {
        printf("\nCodeword is correct.");
    }
    else
    {
        printf("\nCodeword has error.");
    }

    close(clientSocket);
    close(serverSocket);
}